#include "stdafx.h"
#include "GaneshaBurst02Pattern.h"

#include "FSM_GaneshaC.h"
#include "FSMDefine_Ganesha.h"
#include "MB_Ganesha.h"

#include "StateMachineC.h"
#include "Valkyrie.h" 
#include "DynamicMeshData.h"
#include "AniCtrl.h"
#include "PatternMachineC.h"
#include "AttackBall.h"
#include "Ganesha_Dome_Impact.h"

CGaneshaBurst02Pattern::CGaneshaBurst02Pattern()
{
}

CGaneshaBurst02Pattern::~CGaneshaBurst02Pattern()
{
}

void CGaneshaBurst02Pattern::Pattern(Engine::CObject* pOwner)
{
	_float3 tPos = CStageControlTower::GetInstance()->GetCurrentActor()->GetTransform()->GetPosition(); // target pos
	_float3 mPos = pOwner->GetTransform()->GetPosition(); // monster pos
	_float len = D3DXVec3Length(&(tPos - mPos));
	SP(CFSM_GaneshaC) fsm = pOwner->GetComponent<CFSM_GaneshaC>();

	CoolTime(m_atkTime, m_atkCool, m_atkReady);
	CoolTime(m_walkTime, m_walkCool, m_walkReady);

	// 내가 burst2 상태가 아니면 상대를 추적
	if (Name_Ganesha_Burst02 != fsm->GetCurStateString())
	{
		static_cast<CMB_Ganesha*>(pOwner)->ChaseTarget(tPos);
	}

	/************************* Sound */
	// burst sound
	if (Name_Ganesha_Burst02 == fsm->GetCurStateString() &&
		0.f <= fsm->GetDM()->GetAniTimeline() &&
		false == m_onSound)
	{
		PatternPlaySound(L"Ganesha_Burst02.wav", pOwner);
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
	// 상대가 burst2 범위 밖이고
	if (len > m_atkDis)
	{
		// 내가 burst2 상태면
		if (Name_Ganesha_Burst02 == fsm->GetCurStateString() && fsm->GetDM()->IsAnimationEnd())
		{
			fsm->ChangeState(Name_Ganesha_Jump_Back);
			PatternPlaySound(L"Ganesha_JumpBack.wav", pOwner);
			static_cast<CMonster*>(pOwner)->GetStat()->SetOnPatternShield(false);
			m_onSound = false;
			m_onRunStart = false;
		}
		// 내가 대기 상태면 이동 애니로 변경
		else if (Name_Ganesha_StandBy == fsm->GetCurStateString() && fsm->GetDM()->IsAnimationEnd())
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
	// 상대가 burst2 범위 안이고
	else if (len <= m_atkDis)
	{
		// 내가 이동 상태라면 burst2
		if (Name_Ganesha_StandBy == fsm->GetCurStateString() && fsm->GetDM()->IsAnimationEnd())
		{
			fsm->ChangeState(Name_Ganesha_Burst02);
			static_cast<CMonster*>(pOwner)->GetStat()->SetOnPatternShield(true);
			m_onBurstReadyEff = true;
		}
	}

	/************************* JumpBack */
	// 내가 burst2 상태라면 뒤로 이동
	if (Name_Ganesha_Burst02 == fsm->GetCurStateString() && fsm->GetDM()->IsAnimationEnd())
	{
		fsm->ChangeState(Name_Ganesha_Jump_Back);
		PatternPlaySound(L"Ganesha_JumpBack.wav", pOwner);
		m_walkReady = false;
		m_onSound = false;
		m_onRunStart = false;
		std::dynamic_pointer_cast<CGanesha_Dome_Impact>(m_spBurstEff)->GetDomeObject()->SetDeleteThis(true);
		m_spBurstEff->SetDeleteThis(true);
		static_cast<CMonster*>(pOwner)->GetStat()->SetOnPatternShield(false);
	}
	// 내가 뒤로 이동 중이라면
	else if (Name_Ganesha_Jump_Back == fsm->GetCurStateString() && 0.9f <= fsm->GetDM()->GetAniTimeline() && false == m_walkReady)
	{
		_float3 dir = tPos - mPos;

		mPos -= *D3DXVec3Normalize(&dir, &dir) * GET_DT;
		pOwner->GetTransform()->SetPosition(mPos);
	}
	// 내가 뒤로 이동이 끝났다면
	else if (Name_Ganesha_Jump_Back == fsm->GetCurStateString() && 0.9f <= fsm->GetDM()->GetAniTimeline() && true == m_walkReady)
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
	// 내가 burst 상태고, 적절할 때 어택볼 숨기기
	if (Name_Ganesha_Burst02 == fsm->GetCurStateString() &&
		0.65f <= fsm->GetDM()->GetAniTimeline())
	{
		static_cast<CMB_Ganesha*>(pOwner)->UnActiveAttackBall();
	}
	// 내가 burst 상태고, 적절할 때 어택볼 생성
	else if (Name_Ganesha_Burst02 == fsm->GetCurStateString() &&
		0.55f <= fsm->GetDM()->GetAniTimeline())
	{
		m_spBurstReadyEff->SetDeleteThis(true);

		m_atkMat = pOwner->GetTransform()->GetWorldMatrix();
		static_cast<CMB_Ganesha*>(pOwner)->ActiveAttackBall(1.f, HitInfo::Str_High, HitInfo::CC_None, &m_atkMat, 3.4f);
	}

	/************************* Effect */
	if (Name_Ganesha_Burst02 == fsm->GetCurStateString() &&
		0.1f > fsm->GetDM()->GetAniTimeline() &&
		true == m_onBurstReadyEff)
	{
		m_onBurstReadyEff = false;
		m_onBurstEff = true;
		m_spBurstReadyEff = Engine::GET_CUR_SCENE->GetObjectFactory()->AddClone(L"Ganesha_Charge_Eff", true);
		m_spBurstReadyEff->GetTransform()->SetPosition(mPos);
	}
	else if (Name_Ganesha_Burst02 == fsm->GetCurStateString() &&
		0.45f <= fsm->GetDM()->GetAniTimeline() &&
		true == m_onBurstEff)
	{
		m_onBurstEff = false;
		m_spBurstEff = Engine::GET_CUR_SCENE->GetObjectFactory()->AddClone(L"Ganesha_Dome_Impact", true);
		m_spBurstEff->GetTransform()->SetPosition(mPos);
	}
}

SP(CGaneshaBurst02Pattern) CGaneshaBurst02Pattern::Create()
{
	SP(CGaneshaBurst02Pattern) spInstance(new CGaneshaBurst02Pattern, Engine::SmartDeleter<CGaneshaBurst02Pattern>);

	return spInstance;
}