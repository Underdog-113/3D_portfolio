#include "stdafx.h"
#include "ScoutShoot2Pattern.h"

#include "FSM_ScoutC.h"
#include "FSMDefine_Scout.h"
#include "MO_Scout.h"

#include "StateMachineC.h"
#include "Valkyrie.h" 
#include "DynamicMeshData.h"
#include "AniCtrl.h"
#include "PatternMachineC.h"
#include "AttackBox.h"
#include "StageControlTower.h"

CScoutShoot2Pattern::CScoutShoot2Pattern()
{
}

CScoutShoot2Pattern::~CScoutShoot2Pattern()
{
}

void CScoutShoot2Pattern::Pattern(Engine::CObject* pOwner)
{
	_float3 tPos = CStageControlTower::GetInstance()->GetCurrentActor()->GetTransform()->GetPosition(); // target pos
	_float3 mPos = pOwner->GetTransform()->GetPosition(); // monster pos
	_float len = D3DXVec3Length(&(tPos - mPos));
	SP(CFSM_ScoutC) fsm = pOwner->GetComponent<CFSM_ScoutC>();

	CoolTime(m_atkTime, m_atkCool, m_atkReady);
	CoolTime(m_walkTime, m_walkCool, m_walkReady);

	// 내가 shoot2 상태가 아니면 상대를 추적
	if (Name_SHOOT_2 != fsm->GetCurStateString())
	{
		static_cast<CMO_Scout*>(pOwner)->ChaseTarget(tPos);
	}

	/************************* Sound */
	// burst sound
// 	if (Name_Ganesha_Burst01 == fsm->GetCurStateString() &&
// 		0.3f <= fsm->GetDM()->GetAniTimeline() &&
// 		false == m_onSound)
// 	{
// 		PatternPlaySound(L"Ganesha_Laser.wav", pOwner);
// 		m_onSound = true;
// 	}
// 	// run start sound
// 	else if (Name_Ganesha_Run == fsm->GetCurStateString())
// 	{
// 		if (false == m_onRunStart)
// 		{
// 			PatternPlaySound(L"Ganesha_Run_Start.wav", pOwner);
// 			m_onRunStart = true;
// 		}
// 		else if (true == m_onRunStart && false == PatternSoundEnd(pOwner))
// 		{
// 			PatternRepeatSound(L"Ganesha_Run.wav", pOwner, 0.03f);
// 		}
// 	}

	/************************* Range */
	// 상대가 공격 범위 밖이고
	if (len > m_atkDis)
	{
		// 내가 shoot2 상태면
		if (Name_SHOOT_2 == fsm->GetCurStateString() && fsm->GetDM()->IsAnimationEnd())
		{
			fsm->ChangeState(Name_RUN_F);
		}
		// 내가 대기 상태면 이동 애니로 변경
		else if (Name_IDLE == fsm->GetCurStateString() && fsm->GetDM()->IsAnimationEnd())
		{
			fsm->ChangeState(Name_RUN_F);
		}
		// 내가 이동 중이라면

		else if (Name_RUN_F == fsm->GetCurStateString())
		{
			_float3 dir = tPos - mPos;

			mPos += *D3DXVec3Normalize(&dir, &dir) * GET_DT;
			pOwner->GetTransform()->SetPosition(mPos);
		}
		// 내가 뒤로 이동 중이라면
		else if (Name_RUN_B == fsm->GetCurStateString() && fsm->GetDM()->IsAnimationEnd() && false == m_walkReady)
		{
			_float3 dir = tPos - mPos;

			mPos -= *D3DXVec3Normalize(&dir, &dir) * GET_DT;
			pOwner->GetTransform()->SetPosition(mPos);
		}
		// 내가 뒤로 이동이 끝났다면
		else if (Name_RUN_B == fsm->GetCurStateString() && fsm->GetDM()->IsAnimationEnd() && true == m_walkReady)
		{
			//fsm->ChangeState(Name_RUN_F);
			fsm->ChangeState(Name_IDLE);
			pOwner->GetComponent<CPatternMachineC>()->SetOnSelect(false);
		}
	}
	// 상대가 공격 범위 안이고
	else if (len <= m_atkDis)
	{
		// 내가 이동, 대기 상태라면 공격
		if ((Name_RUN_F == fsm->GetCurStateString() ||
			Name_IDLE == fsm->GetCurStateString() ||
			Name_RUN_B == fsm->GetCurStateString()) &&
			fsm->GetDM()->IsAnimationEnd())
		{
			fsm->ChangeState(Name_SHOOT_2);
			PatternPlaySound(L"Scout_Laser.wav", pOwner);
		}
		// shoot2 상태라면 뒤로 이동 상태로 변경
		else if (Name_SHOOT_2 == fsm->GetCurStateString() && fsm->GetDM()->IsAnimationEnd())
		{
			fsm->ChangeState(Name_RUN_B);
		}
	}

 	/************************* AttackBox */
	// shoot2 상태가 완료되면 attackbox off
	if (Name_SHOOT_2 == fsm->GetCurStateString() && 
		0.6f <= fsm->GetDM()->GetAniTimeline())
	{
		m_onShoot2 = false;
		static_cast<CMO_Scout*>(pOwner)->UnActiveAttackBox();
	}
	// shoot2 상태라면
	if (Name_SHOOT_2 == fsm->GetCurStateString() &&
		0.55f <= fsm->GetDM()->GetAniTimeline() &&
		0.6f > fsm->GetDM()->GetAniTimeline() &&
		false == m_onShoot2)
	{
		m_onShoot2 = true;
		m_atkMat = pOwner->GetTransform()->GetWorldMatrix();
		CMO_Scout* pScout = static_cast<CMO_Scout*>(pOwner);
		_float3 size = { 2.f, 1.f, 10.f };
		_float3 offset = ZERO_VECTOR;

		_float3 mPos = pOwner->GetTransform()->GetPosition();
		_float3 pPos = CStageControlTower::GetInstance()->GetCurrentActor()->GetTransform()->GetPosition();
		_float3 beamDir = pPos - mPos;
		beamDir.y = 0.f;
		D3DXVec3Normalize(&beamDir, &beamDir);
		pScout->GetAttackBox()->GetTransform()->SetForward(beamDir);
		pScout->GetAttackBox()->GetTransform()->SetPosition(mPos);

		offset = _float3(0, 0, 5);

		pScout->ActiveAttackBox(1.f, HitInfo::Str_Low, HitInfo::CC_None, &m_atkMat, size, offset, ZERO_VECTOR);
	}
}

SP(CScoutShoot2Pattern) CScoutShoot2Pattern::Create()
{
	SP(CScoutShoot2Pattern) spInstance(new CScoutShoot2Pattern, Engine::SmartDeleter<CScoutShoot2Pattern>);

	return spInstance;
}