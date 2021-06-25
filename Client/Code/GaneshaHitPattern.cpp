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

	// ���� weak ���¶�� �ð� ī��Ʈ
	if (true == m_onWeak && Name_Ganesha_Weak_End != fsm->GetCurStateString())
	{
		m_curBreakTime += GET_DT;
	}

	// ���� weak ���°� �ƴ϶��
	if (false == m_onWeak && 
		0.f >= static_cast<CMonster*>(pOwner)->GetStat()->GetbreakGauge())
	{
		fsm->ChangeState(Name_Ganesha_Weak_Start);
	}
	// ���� weak_start ���¶��
	else if (Name_Ganesha_Weak_Start == fsm->GetCurStateString() && fsm->GetDM()->IsAnimationEnd())
	{
		fsm->ChangeState(Name_Ganesha_Weak_Loop);
	}
	// ���� weak_loop ���¸鼭 4�ʰ� �����ٸ�
	else if (Name_Ganesha_Weak_Loop == fsm->GetCurStateString() &&
			fsm->GetDM()->IsAnimationEnd() &&
			m_maxBreakTime < m_curBreakTime)
	{
		fsm->ChangeState(Name_Ganesha_Weak_End);
		m_curBreakTime = 0.f;
	}
	// ���� weak_loop or weak_hit ���� �� hit ���ߴٸ�
	else if ((Name_Ganesha_Weak_Loop == fsm->GetCurStateString() || 
			Name_Ganesha_Weak_Hit == fsm->GetCurStateString()) &&
			true == m_onHit)
	{
		fsm->ChangeState(Name_Ganesha_Weak_Hit);
		m_onHit = false;
	}
	// ���� weak_hit ���¸�
	else if (Name_Ganesha_Weak_Hit == fsm->GetCurStateString() && fsm->GetDM()->IsAnimationEnd())
	{
		fsm->ChangeState(Name_Ganesha_Weak_Loop);
	}
	// ���� weak_end ���¸�
	else if (Name_Ganesha_Weak_End == fsm->GetCurStateString() && fsm->GetDM()->IsAnimationEnd())
	{
		m_onWeak = false;
		fsm->ChangeState(Name_Ganesha_Jump_Back);
		m_walkReady = false;
	}
	// ���� �ڷ� �̵� ���̶��
	else if (Name_Ganesha_Jump_Back == fsm->GetCurStateString() && 0.9f <= fsm->GetDM()->GetAniTimeline() && false == m_walkReady)
	{
		_float3 tPos = CStageControlTower::GetInstance()->GetCurrentActor()->GetTransform()->GetPosition(); // target pos
		_float3 mPos = pOwner->GetTransform()->GetPosition(); // monster pos
		_float3 dir = tPos - mPos;

		mPos -= *D3DXVec3Normalize(&dir, &dir) * GET_DT;
		pOwner->GetTransform()->SetPosition(mPos);
	}
	// ���� �ڷ� �̵��� �����ٸ�
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