#include "stdafx.h"
#include "RobotAttack1Pattern.h"

#include "FSM_RobotC.h"
#include "FSMDefine_Robot.h"
#include "MO_Robot.h"

#include "StateMachineC.h"
#include "Valkyrie.h" 
#include "DynamicMeshData.h"
#include "AniCtrl.h"
#include "PatternMachineC.h"
#include "AttackBox.h"
#include "StageControlTower.h"

CRobotAttack1Pattern::CRobotAttack1Pattern()
{
}

CRobotAttack1Pattern::~CRobotAttack1Pattern()
{
}

void CRobotAttack1Pattern::Pattern(Engine::CObject* pOwner)
{
	_float3 tPos = CStageControlTower::GetInstance()->GetCurrentActor()->GetTransform()->GetPosition(); // target pos
	_float3 mPos = pOwner->GetTransform()->GetPosition(); // monster pos
	_float len = D3DXVec3Length(&(tPos - mPos));
	SP(CFSM_RobotC) fsm = pOwner->GetComponent<CFSM_RobotC>();

	CoolTime(m_walkTime, m_walkCool, m_walkReady);

	// 내가 상대를 추적
	if (Name_Attack_1_Left != fsm->GetCurStateString())
	{
		static_cast<CMO_Robot*>(pOwner)->ChaseTarget(tPos);
	}

	/************************* Sound */
	//// run start sound
	//if ((Name_WALK_FORWARD == fsm->GetCurStateString() ||
	//	 Name_RUN_B == fsm->GetCurStateString()) &&
	//	 true == m_onWalk)
	//{
	//	PatternRepeatSound(m_curMoveSound, pOwner, 0.4f);
	//}
	//else if ((Name_RUN_F == fsm->GetCurStateString() ||
	//		  Name_RUN_B == fsm->GetCurStateString()) &&
	//		  false == m_onWalk)
	//{
	//	PatternStopSound(pOwner);
	//}

	/************************* Range */
	// 상대가 공격 범위 밖이고
	if (len > m_atkDis)
	{
		// 내가 Attack_1_Left 상태면
		if (Name_Attack_1_Left == fsm->GetCurStateString() &&
			fsm->GetDM()->IsAnimationEnd())
		{
			fsm->ChangeState(Name_Walk_Backward);
		}
		// 내가 대기 상태면 이동 애니로 변경
		else if (Name_StandBy == fsm->GetCurStateString() &&
			fsm->GetDM()->IsAnimationEnd())
		{
			fsm->ChangeState(Name_Walk_Forward);
		}
	}
	// 상대가 공격 범위 안이고
	else if (len <= m_atkDis)
	{
		// 내가 이동, 대기 상태가 끝났다면
		if ((Name_Walk_Forward == fsm->GetCurStateString() ||
			Name_StandBy == fsm->GetCurStateString()) &&
			fsm->GetDM()->IsAnimationEnd())
		{
			fsm->ChangeState(Name_Attack_1_Left);
		}
		// 내가 Attack_1 상태가 끝났다면
		else if (Name_Attack_1_Left == fsm->GetCurStateString() &&
			fsm->GetDM()->IsAnimationEnd() &&
			true == m_walkReady)
		{
			fsm->ChangeState(Name_Walk_Backward);
			m_walkReady = false;
		}
	}

	/************************* Walk */
	// 내가 이동 중이라면
	if (Name_Walk_Forward == fsm->GetCurStateString() &&
		fsm->GetDM()->IsAnimationEnd())
	{
		_float3 dir = tPos - mPos;

		mPos += *D3DXVec3Normalize(&dir, &dir) * GET_DT;
		pOwner->GetTransform()->SetPosition(mPos);
	}
	// 내가 뒤로 이동 중이라면
	else if (Name_Walk_Backward == fsm->GetCurStateString() &&
		fsm->GetDM()->IsAnimationEnd() &&
		false == m_walkReady)
	{
		_float3 dir = tPos - mPos;

		mPos -= *D3DXVec3Normalize(&dir, &dir) * GET_DT;
		pOwner->GetTransform()->SetPosition(mPos);
	}
	// 내가 뒤로 이동이 끝났다면
	else if (Name_Walk_Backward == fsm->GetCurStateString() &&
		fsm->GetDM()->IsAnimationEnd() &&
		true == m_walkReady)
	{
		fsm->ChangeState(Name_StandBy);
		pOwner->GetComponent<CPatternMachineC>()->SetOnSelect(false);
	}


 	/************************* AttackBox */
	// shoot2 상태가 완료되면 attackbox off
	//if (Name_SHOOT_2 == fsm->GetCurStateString() && 
	//	0.7f <= fsm->GetDM()->GetAniTimeline())
	//{
	//	m_onShoot2 = false;
	//	static_cast<CMO_Scout*>(pOwner)->UnActiveAttackBox();
	//}
	//// shoot2 상태라면
	//else if (Name_SHOOT_2 == fsm->GetCurStateString() &&
	//	0.65f <= fsm->GetDM()->GetAniTimeline() &&
	//	0.7f > fsm->GetDM()->GetAniTimeline() &&
	//	false == m_onShoot2)
	//{
	//	m_onShoot2 = true;
	//	m_atkMat = pOwner->GetTransform()->GetWorldMatrix();
	//	CMO_Scout* pScout = static_cast<CMO_Scout*>(pOwner);
	//	_float3 size = { 2.f, 1.f, 10.f };
	//	_float3 offset = ZERO_VECTOR;
	//	_float3 mPos = pOwner->GetTransform()->GetPosition();
	//	
	//	pScout->GetAttackBox()->GetTransform()->SetRotation(pScout->GetTransform()->GetRotation());
	//	pScout->GetAttackBox()->GetTransform()->SetPosition(mPos);

	//	offset = _float3(0, 0, 5);

	//	pScout->ActiveAttackBox(1.f, HitInfo::Str_Low, HitInfo::CC_None, &m_atkMat, size, offset, ZERO_VECTOR);
	//}
}

SP(CRobotAttack1Pattern) CRobotAttack1Pattern::Create()
{
	SP(CRobotAttack1Pattern) spInstance(new CRobotAttack1Pattern, Engine::SmartDeleter<CRobotAttack1Pattern>);

	return spInstance;
}
