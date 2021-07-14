#include "stdafx.h"
#include "GaneshaBurst01Pattern.h"

#include "FSM_GaneshaC.h"
#include "FSMDefine_Ganesha.h"
#include "MB_Ganesha.h"

#include "StateMachineC.h"
#include "Valkyrie.h" 
#include "DynamicMeshData.h"
#include "AniCtrl.h"
#include "PatternMachineC.h"
#include "AttackBox.h"
#include "StageControlTower.h"

CGaneshaBurst01Pattern::CGaneshaBurst01Pattern()
{
}

CGaneshaBurst01Pattern::~CGaneshaBurst01Pattern()
{
}

void CGaneshaBurst01Pattern::Pattern(Engine::CObject* pOwner)
{
	_float3 tPos = CStageControlTower::GetInstance()->GetCurrentActor()->GetTransform()->GetPosition(); // target pos
	_float3 mPos = pOwner->GetTransform()->GetPosition(); // monster pos
	_float len = D3DXVec3Length(&(tPos - mPos));
	SP(CFSM_GaneshaC) fsm = pOwner->GetComponent<CFSM_GaneshaC>();

	CoolTime(m_atkTime, m_atkCool, m_atkReady);
	CoolTime(m_walkTime, m_walkCool, m_walkReady);

	// 내가 burst1 상태가 아니면 상대를 추적
	if (Name_Ganesha_Burst01 != fsm->GetCurStateString())
	{
		static_cast<CMB_Ganesha*>(pOwner)->ChaseTarget(tPos);
	}

	/************************* Sound */
	// burst sound
	if (Name_Ganesha_Burst01 == fsm->GetCurStateString() &&
		0.3f <= fsm->GetDM()->GetAniTimeline() &&
		false == m_onSound)
	{
		PatternPlaySound(L"Ganesha_Laser.wav", pOwner);
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
	// 상대가 burst1 범위 밖이고
	if (len > m_atkDis)
	{
		// 내가 burst1 상태가 끝났다면
		if (Name_Ganesha_Burst01 == fsm->GetCurStateString() &&
			fsm->GetDM()->IsAnimationEnd())
		{
			fsm->ChangeState(Name_Ganesha_Jump_Back);
			PatternPlaySound(L"Ganesha_JumpBack.wav", pOwner);
			m_onSound = false;
			m_onRunStart = false;
		}
		// 내가 대기 상태가 끝났다면
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
	// 상대가 burst1 범위 안이고
	else if (len <= m_atkDis)
	{
		// 내가 이동 상태가 끝났다면
		if (Name_Ganesha_StandBy == fsm->GetCurStateString() &&
			fsm->GetDM()->IsAnimationEnd())
		{
			fsm->ChangeState(Name_Ganesha_Burst01);

			// burst 위치 잡기
			CMB_Ganesha* pGanesha = static_cast<CMB_Ganesha*>(pOwner);
			_float3 mPos = pOwner->GetTransform()->GetPosition();
			_float3 pPos = CStageControlTower::GetInstance()->GetCurrentActor()->GetTransform()->GetPosition();
			m_burstDir = pPos - mPos;
			m_burstDir.y = 0.f;

			D3DXVec3Normalize(&m_burstDir, &m_burstDir);
			m_burstPos = mPos + m_burstDir * 5;

			pGanesha->GetAttackBox()->GetTransform()->SetPosition(m_burstPos);
			pGanesha->GetAttackBox()->GetTransform()->SetRotation(pGanesha->GetTransform()->GetRotation());
		}
	}

	/************************* JumpBack */
	// 내가 burst1 상태가 끝났다면
	if (Name_Ganesha_Burst01 == fsm->GetCurStateString() &&
		fsm->GetDM()->IsAnimationEnd())
	{
		fsm->ChangeState(Name_Ganesha_Jump_Back);
		PatternPlaySound(L"Ganesha_JumpBack.wav", pOwner);
		m_spEffect->SetDeleteThis(true);
		m_walkReady = false;
		m_onSound = false;
		m_onRunStart = false;
	}
	// 내가 뒤로 이동 중이라면
	else if (Name_Ganesha_Jump_Back == fsm->GetCurStateString() &&
		0.9f <= fsm->GetDM()->GetAniTimeline() &&
		false == m_walkReady)
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
			PatternStopSound(pOwner);
			m_jumpCnt = 0;
			pOwner->GetComponent<CPatternMachineC>()->SetOnSelect(false);
		}
	}

	/************************* AttackBox */
	// burst1 상태가 완료되면 attackbox off
	if (Name_Ganesha_Burst01 == fsm->GetCurStateString() &&
		0.59f <= fsm->GetDM()->GetAniTimeline())
	{
		m_onBurst = false;
		static_cast<CMB_Ganesha*>(pOwner)->UnActiveAttackBox();
	}
	// burst1 상태라면
	if (Name_Ganesha_Burst01 == fsm->GetCurStateString() &&
		0.47f <= fsm->GetDM()->GetAniTimeline() &&
		0.59f > fsm->GetDM()->GetAniTimeline() &&
		false == m_onBurst)
	{
		m_onBurst = true;
		m_atkMat = pOwner->GetTransform()->GetWorldMatrix();
		CMB_Ganesha* pGanesha = static_cast<CMB_Ganesha*>(pOwner);
		_float3 size = { 1.1f, 2.f, 15.f };
		_float3 offset = ZERO_VECTOR; 
		
		pGanesha->ActiveAttackBox(1.f, HitInfo::Str_High, HitInfo::CC_None, &m_atkMat, size, offset, ZERO_VECTOR);

		// effect
		m_burstPos = mPos + m_burstDir * 2.f;

		m_spEffect = Engine::GET_CUR_SCENE->GetObjectFactory()->AddClone(L"Ganesha_LaserEff", true);
		m_spEffect->GetTransform()->SetPosition(_float3(m_burstPos.x, m_burstPos.y + 0.3f, m_burstPos.z));
		m_spEffect->GetTransform()->SetRotation(pGanesha->GetTransform()->GetRotation());
		m_spEffect->GetTransform()->AddRotationY(D3DXToRadian(180));
		m_spEffect->GetTransform()->SetSize(_float3(8.f, 12.f, 10.f));
	}
}

SP(CGaneshaBurst01Pattern) CGaneshaBurst01Pattern::Create()
{
	SP(CGaneshaBurst01Pattern) spInstance(new CGaneshaBurst01Pattern, Engine::SmartDeleter<CGaneshaBurst01Pattern>);

	return spInstance;
}