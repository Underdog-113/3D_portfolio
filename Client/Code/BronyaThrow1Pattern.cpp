#include "stdafx.h"
#include "BronyaThrow1Pattern.h"

#include "FSM_BronyaC.h"
#include "FSMDefine_Bronya.h"
#include "MB_Bronya.h"

#include "StateMachineC.h"
#include "Valkyrie.h" 
#include "DynamicMeshData.h"
#include "AniCtrl.h"
#include "PatternMachineC.h"
#include "AttackBall.h"

CBronyaThrow1Pattern::CBronyaThrow1Pattern()
{
}

CBronyaThrow1Pattern::~CBronyaThrow1Pattern()
{
}

void CBronyaThrow1Pattern::Pattern(Engine::CObject* pOwner)
{
	_float3 tPos = CStageControlTower::GetInstance()->GetCurrentActor()->GetTransform()->GetPosition(); // target pos
	_float3 mPos = pOwner->GetTransform()->GetPosition(); // monster pos
	_float len = D3DXVec3Length(&(tPos - mPos));
	SP(CFSM_BronyaC) fsm = pOwner->GetComponent<CFSM_BronyaC>();

	CoolTime(m_walkTime, m_walkCool, m_walkReady);

	/************************* Range */
	// 상대가 공격 범위 밖이고
	if (len > m_atkDis)
	{
		// 내가 대기 상태가 끝났다면
		if (Name_IDLE == fsm->GetCurStateString() &&
			fsm->GetDM()->IsAnimationEnd())
		{
			// 이동 상태로 변경
			fsm->ChangeState(Name_Run);
		}
	}
	// 상대가 공격 범위 안이고
	else if (len <= m_atkDis)
	{
		//// 내가 이동, 대기 상태가 끝났다면
		//if ((Name_Run == fsm->GetCurStateString() ||
		//	Name_IDLE == fsm->GetCurStateString()) &&
		//	fsm->GetDM()->IsAnimationEnd())
		//{
		//	// shoot1 상태로 변경
		//	fsm->ChangeState(Name_Shoot_1);
		//}

		// 내가 대기 상태라면
		if (Name_IDLE == fsm->GetCurStateString() ||
			Name_Run == fsm->GetCurStateString())
		{
			// throw1 상태로 변경
			fsm->ChangeState(Name_Throw_1);
		}
	}

	/************************* throw1 End */
	// 내가 throw1 상태가 끝났다면
	if (Name_Throw_1 == fsm->GetCurStateString() &&
		fsm->GetDM()->IsAnimationEnd())
	{
		// 대기 상태로 변경
		fsm->ChangeState(Name_IDLE);
		pOwner->GetComponent<CPatternMachineC>()->SetOnSelect(false);
	}
} 

SP(CBronyaThrow1Pattern) CBronyaThrow1Pattern::Create()
{
	SP(CBronyaThrow1Pattern) spInstance(new CBronyaThrow1Pattern, Engine::SmartDeleter<CBronyaThrow1Pattern>);

	return spInstance;
}