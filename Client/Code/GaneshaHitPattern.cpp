#include "stdafx.h"
#include "GaneshaHitPattern.h"

#include "FSM_GaneshaC.h"
#include "FSMDefine_Ganesha.h"
#include "MB_Ganesha.h"

#include "StateMachineC.h"
#include "Valkyrie.h" 
#include "DynamicMeshData.h"
#include "AniCtrl.h"
#include "PatternMachineC.h"

CGaneshaHitPattern::CGaneshaHitPattern()
{
}

CGaneshaHitPattern::~CGaneshaHitPattern()
{
}

void CGaneshaHitPattern::Pattern(Engine::CObject* pOwner)
{
	SP(CFSM_GaneshaC) fsm = pOwner->GetComponent<CFSM_GaneshaC>();

	// 내가 weak 상태라면 시간 카운트
	if (true == m_onWeak && Name_Ganesha_Weak_End != fsm->GetCurStateString())
	{
		m_curBreakTime += GET_DT;
	}

	// 내가 weak 상태가 아니라면
	if (false == m_onWeak && 
		0.f >= static_cast<CMonster*>(pOwner)->GetStat()->GetbreakGauge())
	{
		fsm->ChangeState(Name_Ganesha_Weak_Start);
	}
	// 내가 weak_start 상태라면
	else if (Name_Ganesha_Weak_Start == fsm->GetCurStateString() && fsm->GetDM()->IsAnimationEnd())
	{
		fsm->ChangeState(Name_Ganesha_Weak_Loop);
	}
	// 내가 weak_loop 상태면서 4초가 지났다면
	else if (Name_Ganesha_Weak_Loop == fsm->GetCurStateString() &&
			fsm->GetDM()->IsAnimationEnd() &&
			m_maxBreakTime < m_curBreakTime)
	{
		fsm->ChangeState(Name_Ganesha_Weak_End);
		m_curBreakTime = 0.f;
	}
	// 내가 weak_loop or weak_hit 상태 중 hit 당했다면
	else if ((Name_Ganesha_Weak_Loop == fsm->GetCurStateString() || 
			Name_Ganesha_Weak_Hit == fsm->GetCurStateString()) &&
			true == m_onHit)
	{
		fsm->ChangeState(Name_Ganesha_Weak_Hit);
		m_onHit = false;
	}
	// 내가 weak_hit 상태면
	else if (Name_Ganesha_Weak_Hit == fsm->GetCurStateString() && fsm->GetDM()->IsAnimationEnd())
	{
		fsm->ChangeState(Name_Ganesha_Weak_Loop);
	}
	// 내가 weak_end 상태면
	else if (Name_Ganesha_Weak_End == fsm->GetCurStateString() && fsm->GetDM()->IsAnimationEnd())
	{
		m_onWeak = false;
		fsm->ChangeState(Name_Ganesha_Jump_Back);
		m_walkReady = false;
	}
	// 내가 뒤로 이동 중이라면
	else if (Name_Ganesha_Jump_Back == fsm->GetCurStateString() && 0.9f <= fsm->GetDM()->GetAniTimeline() && false == m_walkReady)
	{
		_float3 tPos = CStageControlTower::GetInstance()->GetCurrentActor()->GetTransform()->GetPosition(); // target pos
		_float3 mPos = pOwner->GetTransform()->GetPosition(); // monster pos
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
			pOwner->GetComponent<CPatternMachineC>()->SetOnBase(false);
		}
	}
}

SP(CGaneshaHitPattern) CGaneshaHitPattern::Create()
{
	SP(CGaneshaHitPattern) spInstance(new CGaneshaHitPattern, Engine::SmartDeleter<CGaneshaHitPattern>);

	return spInstance;
}