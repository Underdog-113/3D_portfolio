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
#include "AttackBall.h"
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
	// run start sound
	if (Name_Attack_Run_Loop == fsm->GetCurStateString())
	{
		PatternRepeatSound(L"Robot_Run.wav", pOwner, 0.3f);
	}
	//else if (Name_Attack_Run_Loop != fsm->GetCurStateString())
	//{
	//	PatternStopSound(pOwner);
	//}

	/************************* Run Acc Time */
	if (true == m_aniSpeedDown && m_accTime < m_maxTime)
	{
		m_accTime += GET_DT;
	}
	else if (m_accTime >= m_maxTime)
	{
		m_accTime = 0.f;
	}

	/************************* Range */
	// ��밡 �ʹ� ������
	if (len < m_minDis && false == m_onRun)
	{
		auto& comp = pOwner->GetComponent<CPatternMachineC>();

		// ���� �ѱ��
		_float curCost = comp->GetCurCost();
		comp->SetCurCost(curCost + m_cost);
		comp->SetOnSelect(false);
		return;
	}
	// ��밡 �ּ� �Ÿ����� �ָ�
	else if (len >= m_minDis)
	{
		// ���� �̵�, ��� ���°� �����ٸ�
		if ((Name_StandBy == fsm->GetCurStateString() ||
			Name_Walk_Forward == fsm->GetCurStateString()) &&
			fsm->GetDM()->IsAnimationEnd() &&
			false == m_atkEnd &&
			false == m_onRun)
		{
			fsm->ChangeState(Name_Run_Attack_BS);
			m_onRun = true;
		}
	}

	/************************* Run Attack */
	// ���� BS ���°� �����ٸ�
	if (Name_Run_Attack_BS == fsm->GetCurStateString() &&
		fsm->GetDM()->IsAnimationEnd() &&
		false == m_atkEnd)
	{
		fsm->ChangeState(Name_Attack_Run_Loop);
		PatternPlaySound(L"Robot_Run.wav", pOwner);

		_float3 dir = tPos - mPos;
		dir.y = 0;
		D3DXVec3Normalize(&dir, &dir);

		m_tPos = tPos - dir;
		pOwner->GetTransform()->SetLerpOn(true);
		pOwner->GetTransform()->SetGoalPosition(m_tPos);
	}
	// Attack Run Loop ���¶��
	else if (Name_Attack_Run_Loop == fsm->GetCurStateString() &&
		false == m_aniSpeedDown)
	{
		fsm->GetDM()->GetAniCtrl()->SetSpeed(0.7f);
		m_aniSpeedDown = true;
	}
	//// Attack Run Loop ���°� �����ٸ�
	//else if (Name_Attack_Run_Loop == fsm->GetCurStateString() &&
	//	fsm->GetDM()->IsAnimationEnd() &&
	//	mPos == m_tPos &&
	//	false == m_atkEnd)
	//{
	//	fsm->ChangeState(Name_Run_Attack);
	//	fsm->GetDM()->GetAniCtrl()->SetSpeed(1.f);
	//	m_aniSpeedDown = false;
	//}
	// Attack Run Loop ���� �� ĳ���Ϳ� �浹�Ǿ��ٸ�
	else if (Name_Attack_Run_Loop == fsm->GetCurStateString() &&
		true == static_cast<CMO_Robot*>(pOwner)->GetCheckCol() &&
		true == m_aniSpeedDown)
	{
		fsm->ChangeState(Name_Run_Attack);
		fsm->GetDM()->GetAniCtrl()->SetSpeed(1.f);
		m_aniSpeedDown = false;
	}
	// Attack Run Loop ���� �� �ð��� �� �Ǿ��ٸ�
	else if (Name_Attack_Run_Loop == fsm->GetCurStateString() &&
		fsm->GetDM()->IsAnimationEnd() &&
		m_accTime >= m_maxTime &&
		true == m_aniSpeedDown)
	{
		fsm->ChangeState(Name_Run_Attack);
		fsm->GetDM()->GetAniCtrl()->SetSpeed(1.f);
		m_aniSpeedDown = false;

		PatternPlaySound(L"Robot_Run_Attack.wav", pOwner);
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
		m_onRun = false;
		m_onSound = false;
	}

 	/************************* AttackBox */
	// run attack ���°� �Ϸ�Ǹ� attackbox off
	if (Name_Run_Attack == fsm->GetCurStateString() && 
		0.6f <= fsm->GetDM()->GetAniTimeline() &&
		true == m_onAtkBall)
	{
		static_cast<CMO_Robot*>(pOwner)->UnActiveAttackBall();
		m_onAtkBall = false;
	}
	// run attack ���¶��
	else if (Name_Run_Attack == fsm->GetCurStateString() &&
		0.5f <= fsm->GetDM()->GetAniTimeline() &&
		0.6f > fsm->GetDM()->GetAniTimeline() &&
		false == m_onAtkBall)
	{
		m_onAtkBall = true;
		
		m_atkMat = pOwner->GetTransform()->GetWorldMatrix();

		_float3 look = _float3(m_atkMat._31, m_atkMat._32, m_atkMat._33);
		D3DXVec3Normalize(&look, &look);

		m_atkMat._42 += pOwner->GetComponent<Engine::CMeshC>()->GetHalfYOffset();
		m_atkMat._41 += (m_atkDis * look.x / 1.7f);
		m_atkMat._43 += (m_atkDis * look.z / 1.7f);

		static_cast<CMO_Robot*>(pOwner)->ActiveAttackBall(1.f, HitInfo::Str_Low, HitInfo::CC_None, &m_atkMat, 0.42f);
	}
}

SP(CRobotRunAttackPattern) CRobotRunAttackPattern::Create()
{
	SP(CRobotRunAttackPattern) spInstance(new CRobotRunAttackPattern, Engine::SmartDeleter<CRobotRunAttackPattern>);

	return spInstance;
}
