#include "stdafx.h"
#include "GaneshaRoll01Pattern.h"

#include "FSM_GaneshaC.h"
#include "FSMDefine_Ganesha.h"
#include "MB_Ganesha.h"

#include "StateMachineC.h"
#include "Valkyrie.h" 
#include "DynamicMeshData.h"
#include "AniCtrl.h"
#include "PatternMachineC.h"
#include "AttackBall.h"

CGaneshaRoll01Pattern::CGaneshaRoll01Pattern()
{
}

CGaneshaRoll01Pattern::~CGaneshaRoll01Pattern()
{
}

void CGaneshaRoll01Pattern::Pattern(Engine::CObject* pOwner)
{
	_float3 tPos = CStageControlTower::GetInstance()->GetCurrentActor()->GetTransform()->GetPosition(); // target pos
	_float3 mPos = pOwner->GetTransform()->GetPosition(); // monster pos
	_float len = D3DXVec3Length(&(tPos - mPos));
	SP(CFSM_GaneshaC) fsm = pOwner->GetComponent<CFSM_GaneshaC>();

	CoolTime(m_atkTime, m_atkCool, m_atkReady);
	CoolTime(m_walkTime, m_walkCool, m_walkReady);

	// 내가 roll1 상태가 아니면 상대를 추적
	if (Name_Ganesha_Roll01 != fsm->GetCurStateString())
	{
		static_cast<CMB_Ganesha*>(pOwner)->ChaseTarget(tPos);
	}

	/************************* Sound */
	// roll sound
	if (Name_Ganesha_Roll01 == fsm->GetCurStateString() &&
		0.0f <= fsm->GetDM()->GetAniTimeline() &&
		false == m_onSound)
	{
		PatternPlaySound(L"Ganesha_Roll.wav", pOwner);
		m_onSound = true;
	}
	// run start sound
	else if (Name_Ganesha_Run == fsm->GetCurStateString())
	{
		if (false == m_onRunStart)
		{
			PatternPlaySound(L"Ganesha_Run_Start.wav", pOwner);
			m_onRunStart = true;
		}
		else if (true == m_onRunStart && false == PatternSoundEnd(pOwner))
		{
			PatternRepeatSound(L"Ganesha_Run.wav", pOwner, 0.03f);
		}
	}

	/************************* Range */
	// 상대가 roll1 범위 밖이고
	if (len > m_atkDis)
	{
		// 내가 roll1 상태면
		if (Name_Ganesha_Roll01 == fsm->GetCurStateString() &&
			fsm->GetDM()->IsAnimationEnd())
		{
			fsm->ChangeState(Name_Ganesha_Jump_Back);
			fsm->GetDM()->GetAniCtrl()->SetSpeed(1.f);
			PatternPlaySound(L"Ganesha_JumpBack.wav", pOwner);
			m_onSound = false;
			m_onRunStart = false;
			static_cast<CMonster*>(pOwner)->GetStat()->SetOnPatternShield(false);

		}
		// 내가 대기 상태면 이동 애니로 변경
		else if (Name_Ganesha_StandBy == fsm->GetCurStateString() &&
			fsm->GetDM()->IsAnimationEnd())
		{
			fsm->ChangeState(Name_Ganesha_Run);
		}
		// 내가 이동 중이라면
		else if (Name_Ganesha_Run == fsm->GetCurStateString())
		{
			_float3 dir = tPos - mPos;

			mPos += *D3DXVec3Normalize(&dir, &dir) * GET_DT;
			pOwner->GetTransform()->SetPosition(mPos);
		}
	}
	// 상대가 roll1 범위 안이고
	else if (len <= m_atkDis)
	{
		// 내가 이동,대기 상태라면 roll1
		if ((Name_Ganesha_Run == fsm->GetCurStateString() ||
			Name_Ganesha_StandBy == fsm->GetCurStateString()) &&
			fsm->GetDM()->IsAnimationEnd())
		{
			m_onEffect = true;
			fsm->ChangeState(Name_Ganesha_Roll01);
			fsm->GetDM()->GetAniCtrl()->SetSpeed(0.9f);
			static_cast<CMonster*>(pOwner)->GetStat()->SetOnPatternShield(true);

			return;
		}
	}

	/************************* JumpBack */
	// 내가 roll1 상태라면 뒤로 이동
	if (Name_Ganesha_Roll01 == fsm->GetCurStateString() &&
		fsm->GetDM()->IsAnimationEnd())
	{
		fsm->ChangeState(Name_Ganesha_Jump_Back);
		fsm->GetDM()->GetAniCtrl()->SetSpeed(1.f);
		PatternPlaySound(L"Ganesha_JumpBack.wav", pOwner);
		m_walkReady = false;
		m_onSound = false;
		m_onRunStart = false;
	}
	// 내가 뒤로 이동 중이라면
	else if (Name_Ganesha_Jump_Back == fsm->GetCurStateString() &&
		0.9f <= fsm->GetDM()->GetAniTimeline() && false == m_walkReady)
	{
		_float3 dir = tPos - mPos;

		mPos -= *D3DXVec3Normalize(&dir, &dir) * GET_DT;
		pOwner->GetTransform()->SetPosition(mPos);
	}
	// 내가 뒤로 이동이 끝났다면
	else if (Name_Ganesha_Jump_Back == fsm->GetCurStateString() &&
		0.9f <= fsm->GetDM()->GetAniTimeline() &&
		true == m_walkReady)
	{
		++m_jumpCnt;

		if (2 != m_jumpCnt)
		{
			m_walkReady = false;
		}
		else
		{
			fsm->ChangeState(Name_Ganesha_StandBy);
			m_jumpCnt = 0;
			pOwner->GetComponent<CPatternMachineC>()->SetOnSelect(false);
		}

		// effect
		_float fX = 0;
		for (_int i = 0; i < 8; ++i)
		{
			SP(Engine::CObject) spObj = Engine::GET_CUR_SCENE->GetObjectFactory()->AddClone(L"Ganesha_SmokeEff", true);

			// Ganesha Pos X + fX 
			spObj->GetTransform()->SetPositionX(mPos.x + fX - 1.3f);
			spObj->GetTransform()->SetPositionY(mPos.y + 0.1f);
			spObj->GetTransform()->SetPositionZ(mPos.z + (rand() % 2) - 1.f);
			fX += 0.5f;
		}
	}

	/************************* AttackBall */
	// roll 상태가 완료되면 attackball off
	if (Name_Ganesha_Roll01 == fsm->GetCurStateString() &&
		0.5f <= fsm->GetDM()->GetAniTimeline())
	{
		static_cast<CMB_Ganesha*>(pOwner)->UnActiveAttackBall();
	}
	// roll 상태라면
	else if (Name_Ganesha_Roll01 == fsm->GetCurStateString() &&
		0.345f <= fsm->GetDM()->GetAniTimeline())
	{
		m_atkMat = pOwner->GetTransform()->GetWorldMatrix();
		static_cast<CMB_Ganesha*>(pOwner)->ActiveAttackBall(1.f, HitInfo::Str_High, HitInfo::CC_None, &m_atkMat, 1.5f);
		// roll 범위의 콜라이더 크기 정함
		static_cast<Engine::CSphereCollider*>(static_cast<CMB_Ganesha*>(pOwner)->GetAttackBall()->GetCollision()->GetColliders()[0].get())->SetOffset(_float3(0.7f, 0.6f, 0.f));
	}

	/************************* Effect */
	if (Name_Ganesha_Roll01 == fsm->GetCurStateString() &&
		0.44f <= fsm->GetDM()->GetAniTimeline() &&
		true == m_onEffect)
	{
		m_onEffect = false;
		m_spEffect = Engine::GET_CUR_SCENE->GetObjectFactory()->AddClone(L"Ganesha_Impact_Eff", true);
		m_spEffect->GetTransform()->SetPosition(mPos);
		m_spEffect->GetTransform()->SetSize(3.f, 3.f, 3.f);
	}
}

SP(CGaneshaRoll01Pattern) CGaneshaRoll01Pattern::Create()
{
	SP(CGaneshaRoll01Pattern) spInstance(new CGaneshaRoll01Pattern, Engine::SmartDeleter<CGaneshaRoll01Pattern>);

	return spInstance;
}