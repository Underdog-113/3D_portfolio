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
	// 상대가 너무 가까우면
	if (len < m_minDis && false == m_onRun)
	{
		auto& comp = pOwner->GetComponent<CPatternMachineC>();

		// 패턴 넘기기
		_float curCost = comp->GetCurCost();
		comp->SetCurCost(curCost + m_cost);
		comp->SetOnSelect(false);
		return;
	}
	// 상대가 최소 거리보다 멀면
	else if (len >= m_minDis)
	{
		// 내가 이동, 대기 상태가 끝났다면
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
	// 내가 BS 상태가 끝났다면
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
	// Attack Run Loop 상태라면
	else if (Name_Attack_Run_Loop == fsm->GetCurStateString() &&
		false == m_aniSpeedDown)
	{
		fsm->GetDM()->GetAniCtrl()->SetSpeed(0.7f);
		m_aniSpeedDown = true;
	}
	//// Attack Run Loop 상태가 끝났다면
	//else if (Name_Attack_Run_Loop == fsm->GetCurStateString() &&
	//	fsm->GetDM()->IsAnimationEnd() &&
	//	mPos == m_tPos &&
	//	false == m_atkEnd)
	//{
	//	fsm->ChangeState(Name_Run_Attack);
	//	fsm->GetDM()->GetAniCtrl()->SetSpeed(1.f);
	//	m_aniSpeedDown = false;
	//}
	// Attack Run Loop 상태 중 캐릭터와 충돌되었다면
	else if (Name_Attack_Run_Loop == fsm->GetCurStateString() &&
		true == static_cast<CMO_Robot*>(pOwner)->GetCheckCol() &&
		true == m_aniSpeedDown)
	{
		fsm->ChangeState(Name_Run_Attack);
		fsm->GetDM()->GetAniCtrl()->SetSpeed(1.f);
		m_aniSpeedDown = false;
	}
	// Attack Run Loop 상태 중 시간이 다 되었다면
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
	// 내가 Run Attack 상태가 끝났다면
	else if (Name_Run_Attack == fsm->GetCurStateString() &&
		fsm->GetDM()->IsAnimationEnd() &&
		false == m_atkEnd)
	{
		fsm->ChangeState(Name_Run_AS);
		m_atkEnd = true;
	}
	// 내가 Run AS 상태가 끝났다면
	else if (Name_Run_AS == fsm->GetCurStateString() &&
		fsm->GetDM()->IsAnimationEnd() &&
		true == m_atkEnd)
	{
		fsm->ChangeState(Name_Walk_Backward);
		m_atkEnd = false;
		m_walkReady = false;
		//m_tPos = tPos;
	}
// 	// 내가 Walk Backward 상태라면 
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
	// 내가 Walk Backward 상태가 끝났다면
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
	// run attack 상태가 완료되면 attackbox off
	if (Name_Run_Attack == fsm->GetCurStateString() && 
		0.6f <= fsm->GetDM()->GetAniTimeline() &&
		true == m_onAtkBall)
	{
		static_cast<CMO_Robot*>(pOwner)->UnActiveAttackBall();
		m_onAtkBall = false;
	}
	// run attack 상태라면
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
