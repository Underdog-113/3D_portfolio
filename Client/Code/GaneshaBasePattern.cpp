#include "stdafx.h"
#include "GaneshaBasePattern.h"

#include "FSM_GaneshaC.h"
#include "FSMDefine_Ganesha.h"
#include "MB_Ganesha.h"

#include "StateMachine.h"
#include "Valkyrie.h" 
#include "DynamicMeshData.h"
#include "AniCtrl.h"
#include "PatternMachineC.h"

CGaneshaBasePattern::CGaneshaBasePattern()
{
}

CGaneshaBasePattern::~CGaneshaBasePattern()
{
}

void CGaneshaBasePattern::Pattern(Engine::CObject* pOwner)
{
	_float3 tPos = CStageControlTower::GetInstance()->GetCurrentActor()->GetTransform()->GetPosition(); // target pos
	_float3 mPos = pOwner->GetTransform()->GetPosition(); // monster pos
	_float len = D3DXVec3Length(&(tPos - mPos));
	SP(CFSM_GaneshaC) fsm = pOwner->GetComponent<CFSM_GaneshaC>();

	CoolTime(m_atkTime, m_atkCool, m_atkReady);
	CoolTime(m_walkTime, m_walkCool, m_walkReady);

	static_cast<CMB_Ganesha*>(pOwner)->ChaseTarget(tPos);

	// 상대가 공격 범위 밖이고
	if (len > m_atkDis)
	{
		// 내가 공격1 상태면
		if (Name_Ganesha_Attack01 == fsm->GetCurStateString() && fsm->GetDM()->IsAnimationEnd())
		{
			fsm->ChangeState(Name_Ganesha_Jump_Back);
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
	// 상대가 공격 범위 안이고
	else if (len <= m_atkDis)
	{
		// 내가 이동 상태라면 공격
		if (Name_Ganesha_Run == fsm->GetCurStateString() && fsm->GetDM()->IsAnimationEnd())
		{
			fsm->ChangeState(Name_Ganesha_Attack01);
		}
	}

	// 내가 공격1 상태라면 뒤로 이동 상태로 변경
	if (Name_Ganesha_Attack01 == fsm->GetCurStateString() && fsm->GetDM()->IsAnimationEnd())
	{
		fsm->ChangeState(Name_Ganesha_Jump_Back);
		m_walkReady = false;
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
			pOwner->GetComponent<CPatternMachineC>()->SetOnBase(false);
		}
	}
}

SP(CGaneshaBasePattern) CGaneshaBasePattern::Create()
{
	SP(CGaneshaBasePattern) spInstance(new CGaneshaBasePattern, Engine::SmartDeleter<CGaneshaBasePattern>);

	return spInstance;
}