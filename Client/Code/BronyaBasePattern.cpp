#include "stdafx.h"
#include "BronyaBasePattern.h"

#include "FSM_BronyaC.h"
#include "FSMDefine_Bronya.h"
#include "MB_Bronya.h"

#include "Valkyrie.h"

CBronyaBasePattern::CBronyaBasePattern()
{
}

CBronyaBasePattern::~CBronyaBasePattern()
{
}

void CBronyaBasePattern::Pattern(Engine::CObject* pOwner)
{
	//_float3 tPos = CStageControlTower::GetInstance()->GetCurrentActor()->GetTransform()->GetPosition(); // target pos
	//_float3 mPos = pOwner->GetTransform()->GetPosition(); // monster pos
	//_float len = D3DXVec3Length(&(tPos - mPos));
	//SP(CFSM_BronyaC) fsm = pOwner->GetComponent<CFSM_BronyaC>();

	//CoolTime(m_walkTime, m_walkCool, m_walkReady);

	///************************* Chase Target */
	//if (Name_Evade_Left != fsm->GetCurStateString() &&
	//	Name_Evade_Right != fsm->GetCurStateString())
	//{
	//	static_cast<CMB_Bronya*>(pOwner)->ChaseTarget(tPos);
	//}

	//// 이동 상태가 비었다면
	//if (L"" == m_curState)
	//{
	//	m_curState = Name_Run;
	//}

	///************************* Choose Move Dir */
	//// 내가 대기 상태가 끝났다면
	//if (Name_IDLE == fsm->GetCurStateString() &&
	//	fsm->GetDM()->IsAnimationEnd() &&
	//	true == m_walkReady)
	//{
	//	_int index = GetRandRange(0, 3);

	//	switch (index)
	//	{
	//	case 0:
	//		m_curState = Name_Run;
	//		break;
	//	case 1:
	//		m_curState = Name_DashBack;
	//		break;
	//	case 2:
	//		m_curState = Name_Evade_Left;
	//		break;
	//	case 3:
	//		m_curState = Name_Evade_Right;
	//		break;
	//	}

	//	// 이동 상태로 변경
	//	fsm->ChangeState(m_curState);
	//}
	//// 내가 이동 상태가 끝났다면
	//else if (m_curState == fsm->GetCurStateString() &&
	//	fsm->GetDM()->IsAnimationEnd())
	//{
	//	// 대기 상태로 변경
	//	fsm->ChangeState(Name_IDLE);
	//	m_walkReady = false;
	//	pOwner->GetComponent<CPatternMachineC>()->SetOnBase(false);
	//}
} 

SP(CBronyaBasePattern) CBronyaBasePattern::Create()
{
	SP(CBronyaBasePattern) spInstance(new CBronyaBasePattern, Engine::SmartDeleter<CBronyaBasePattern>);

	return spInstance;
}