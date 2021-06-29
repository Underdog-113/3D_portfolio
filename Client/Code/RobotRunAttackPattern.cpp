#include "stdafx.h"
#include "RobotRunAttackPattern.h"

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

CRobotRunAttackPattern::CRobotRunAttackPattern()
{
}

CRobotRunAttackPattern::~CRobotRunAttackPattern()
{
}

void CRobotRunAttackPattern::Pattern(Engine::CObject* pOwner)
{
	_float3 tPos = CStageControlTower::GetInstance()->GetCurrentActor()->GetTransform()->GetPosition(); // target pos
	_float3 mPos = pOwner->GetTransform()->GetPosition(); // monster pos
	_float len = D3DXVec3Length(&(tPos - mPos));
	SP(CFSM_RobotC) fsm = pOwner->GetComponent<CFSM_RobotC>();

	CoolTime(m_walkTime, m_walkCool, m_walkReady);

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
	// ��밡 �ʹ� ������
	if (len <= 2.5f)
	{
		// ���� �ѱ��
		_float curCost = pOwner->GetComponent<CPatternMachineC>()->GetCurCost();
		pOwner->GetComponent<CPatternMachineC>()->SetCurCost(curCost + m_cost);

		pOwner->GetComponent<CPatternMachineC>()->SetOnSelect(false);
		return;
	}
	// ��밡 �̵� ���� ���̰�
	else if (len <= m_runDis)
	{
		// ���� �̵�, ��� ���°� �����ٸ�
		if ((Name_StandBy == fsm->GetCurStateString() ||
			Name_Walk_Forward == fsm->GetCurStateString()) &&
			fsm->GetDM()->IsAnimationEnd() &&
			false == m_atkEnd)
		{
			fsm->ChangeState(Name_Run_Attack_BS);
		}
	}

	/************************* Run Attack */
	// ���� BS ���°� �����ٸ�
	if (Name_Run_Attack_BS == fsm->GetCurStateString() &&
		fsm->GetDM()->IsAnimationEnd() &&
		false == m_atkEnd)
	{
		fsm->ChangeState(Name_Attack_Run_Loop);

		_float3 dir = tPos - mPos;
		dir.y = 0;
		D3DXVec3Normalize(&dir, &dir);

		m_tPos = tPos - dir;
		pOwner->GetTransform()->SetLerpOn(true);
		pOwner->GetTransform()->SetGoalPosition(m_tPos);
	}
	// Attack Run Loop ���°� �����ٸ�
	else if (Name_Attack_Run_Loop == fsm->GetCurStateString() &&
		fsm->GetDM()->IsAnimationEnd() &&
		mPos == m_tPos &&
		false == m_atkEnd)
	{
		fsm->ChangeState(Name_Run_Attack);
	}
	// ���� Run Attack ���°� �����ٸ�
	else if (Name_Run_Attack == fsm->GetCurStateString() &&
		fsm->GetDM()->IsAnimationEnd() &&
		false == m_atkEnd)
	{
		fsm->ChangeState(Name_Run_AS);
		m_atkEnd = true;
	}
	// ���� Run AS ���°� �����ٸ�
	else if (Name_Run_AS == fsm->GetCurStateString() &&
		fsm->GetDM()->IsAnimationEnd() &&
		true == m_atkEnd)
	{
		fsm->ChangeState(Name_Walk_Backward);
		m_atkEnd = false;
		m_walkReady = false;
		//m_tPos = tPos;
	}
// 	// ���� Walk Backward ���¶�� 
// 	else if (Name_Walk_Backward == fsm->GetCurStateString() &&
// 		false == m_walkReady)
// 	{
// 		_float3 dir = tPos - mPos;
// 		dir.y = 0;
// 		D3DXVec3Normalize(&dir, &dir);
// 
// 		pOwner->GetTransform()->SetSlerpOn(true);
// 		pOwner->GetTransform()->SetGoalForward(dir);
// 	}
	// ���� Walk Backward ���°� �����ٸ�
	else if (Name_Walk_Backward == fsm->GetCurStateString() &&
		fsm->GetDM()->IsAnimationEnd() &&
		true == m_walkReady)
	{
		fsm->ChangeState(Name_StandBy);
		pOwner->GetComponent<CPatternMachineC>()->SetOnSelect(false);
	}

	



 	/************************* AttackBox */
	// shoot2 ���°� �Ϸ�Ǹ� attackbox off
	//if (Name_SHOOT_2 == fsm->GetCurStateString() && 
	//	0.7f <= fsm->GetDM()->GetAniTimeline())
	//{
	//	m_onShoot2 = false;
	//	static_cast<CMO_Scout*>(pOwner)->UnActiveAttackBox();
	//}
	//// shoot2 ���¶��
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

SP(CRobotRunAttackPattern) CRobotRunAttackPattern::Create()
{
	SP(CRobotRunAttackPattern) spInstance(new CRobotRunAttackPattern, Engine::SmartDeleter<CRobotRunAttackPattern>);

	return spInstance;
}
