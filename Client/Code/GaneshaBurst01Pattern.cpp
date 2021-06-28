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
		// 내가 burst1 상태면
		if (Name_Ganesha_Burst01 == fsm->GetCurStateString() && fsm->GetDM()->IsAnimationEnd())
		{
			fsm->ChangeState(Name_Ganesha_Jump_Back);
			PatternPlaySound(L"Ganesha_JumpBack.wav", pOwner);
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
	// 상대가 burst1 범위 안이고
	else if (len <= m_atkDis)
	{
		// 내가 이동 상태라면 burst1
		if ((Name_Ganesha_StandBy == fsm->GetCurStateString() ||
			Name_Ganesha_StandBy == fsm->GetCurStateString()) &&
			fsm->GetDM()->IsAnimationEnd())
		{
			fsm->ChangeState(Name_Ganesha_Burst01);
		}
	}

	/************************* JumpBack */
	// 내가 burst1 상태라면 뒤로 이동
	if (Name_Ganesha_Burst01 == fsm->GetCurStateString() && fsm->GetDM()->IsAnimationEnd())
	{
		fsm->ChangeState(Name_Ganesha_Jump_Back);
		PatternPlaySound(L"Ganesha_JumpBack.wav", pOwner);
		m_walkReady = false;
		m_onSound = false;
		m_onRunStart = false;
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
			PatternStopSound(pOwner);
			m_jumpCnt = 0;
			pOwner->GetComponent<CPatternMachineC>()->SetOnSelect(false);
		}
	}

	/************************* AttackBall */
	// burst 상태가 완료되면 attackball off
	if (Name_Ganesha_Burst01 == fsm->GetCurStateString() && 0.5f <= fsm->GetDM()->GetAniTimeline())
	{
		m_onBurst = false;
		static_cast<CMB_Ganesha*>(pOwner)->UnActiveAttackBall();
	}
	// burst 상태라면
	if (Name_Ganesha_Burst01 == fsm->GetCurStateString() &&
		0.4f <= fsm->GetDM()->GetAniTimeline() &&
		0.5f > fsm->GetDM()->GetAniTimeline() &&
		false == m_onBurst)
	{
		m_onBurst = true;
		m_atkMat = pOwner->GetTransform()->GetWorldMatrix();
		CMB_Ganesha* pGanesha = static_cast<CMB_Ganesha*>(pOwner);
		_float3 size = { 2.f, 2.f, 10.f };
		_float3 offset = { 0.f, 0.f, 0.f }; 

		_float3 mPos = pOwner->GetTransform()->GetPosition();
		_float3 pPos = CStageControlTower::GetInstance()->GetCurrentActor()->GetTransform()->GetPosition();
		_float3 beamDir = pPos - mPos;
		beamDir.y = 0.f;
		D3DXVec3Normalize(&beamDir, &beamDir);
/*
		_mat rotMat;
		D3DXMatrixRotationYawPitchRoll(&rotMat,
			pGanesha->GetTransform()->GetRotation().y,
			pGanesha->GetTransform()->GetRotation().x,
			pGanesha->GetTransform()->GetRotation().z);*/
		pGanesha->GetAttackBox()->GetTransform()->SetPosition(mPos);
		pGanesha->GetAttackBox()->GetTransform()->SetRotation(pGanesha->GetTransform()->GetRotation());

		offset.z = 5;
		
		pGanesha->ActiveAttackBox(1.f, HitInfo::Str_High, HitInfo::CC_None, &m_atkMat, size, offset, ZERO_VECTOR);
	}
}

SP(CGaneshaBurst01Pattern) CGaneshaBurst01Pattern::Create()
{
	SP(CGaneshaBurst01Pattern) spInstance(new CGaneshaBurst01Pattern, Engine::SmartDeleter<CGaneshaBurst01Pattern>);

	return spInstance;
}