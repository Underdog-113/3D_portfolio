#include "stdafx.h"
#include "SickleAtk02Pattern.h"

#include "FSM_SickleC.h"
#include "FSMDefine_Sickle.h"
#include "MO_Sickle.h"

#include "StageControlTower.h"
#include "Valkyrie.h"
#include "DynamicMeshData.h"
#include "PatternMachineC.h"

CSickleAtk02Pattern::CSickleAtk02Pattern()
{
}

CSickleAtk02Pattern::~CSickleAtk02Pattern()
{
}

void CSickleAtk02Pattern::Pattern(Engine::CObject* pOwner)
{
	_float3 tPos = CStageControlTower::GetInstance()->GetCurrentActor()->GetTransform()->GetPosition(); // target pos
	_float3 mPos = pOwner->GetTransform()->GetPosition(); // monster pos
	_float len = D3DXVec3Length(&(tPos - mPos));
	SP(CFSM_SickleC) fsm = pOwner->GetComponent<CFSM_SickleC>();

	CoolTime(m_atkTime, m_atkCool, m_atkReady);
	CoolTime(m_walkTime, m_walkCool, m_walkReady);

	static_cast<CMO_Sickle*>(pOwner)->ChaseTarget(tPos);

	// 상대가 공격 범위 밖이고
	if (len > m_atkDis)
	{
		// 내가 공격2 상태면
		if (Name_Sickle_Attack_2 == fsm->GetCurStateString() && fsm->GetDM()->IsAnimationEnd())
		{
			fsm->ChangeState(Name_Sickle_Walk_Back);
		}
		// 내가 대기 상태면 이동 애니로 변경
		else if ((Name_Sickle_StandBy == fsm->GetCurStateString() ||
			Name_Sickle_Attack_1 == fsm->GetCurStateString())
			&& fsm->GetDM()->IsAnimationEnd())
		{
			fsm->ChangeState(Name_Sickle_Walk_Forward);
		}
		// 내가 이동 중이라면
		else if (Name_Sickle_Walk_Forward == fsm->GetCurStateString())
		{
			_float3 dir = tPos - mPos;

			mPos += *D3DXVec3Normalize(&dir, &dir) * GET_DT;
			pOwner->GetTransform()->SetPosition(mPos);
		}
		// 내가 뒤로 이동 중이라면
		else if (Name_Sickle_Walk_Back == fsm->GetCurStateString() && fsm->GetDM()->IsAnimationEnd() && false == m_walkReady)
		{
			_float3 dir = tPos - mPos;

			mPos -= *D3DXVec3Normalize(&dir, &dir) * GET_DT;
			pOwner->GetTransform()->SetPosition(mPos);
		}
		// 내가 뒤로 이동이 끝났다면
		else if (Name_Sickle_Walk_Back == fsm->GetCurStateString() && fsm->GetDM()->IsAnimationEnd() && true == m_walkReady)
		{
			fsm->ChangeState(Name_Sickle_Walk_Forward);
		}
	}
	// 상대가 공격 범위 안이고
	else if (len <= m_atkDis)
	{
		// 내가 이동 상태, 공격 쿨다운 중이라면 대기
		if (Name_Sickle_Walk_Forward == fsm->GetCurStateString() &&
			fsm->GetDM()->IsAnimationEnd() &&
			false == m_atkReady)
		{
			fsm->ChangeState(Name_Sickle_StandBy);
		}
		// 내가 이동 상태라면 공격
		else if ((Name_Sickle_Walk_Forward == fsm->GetCurStateString()) &&
			fsm->GetDM()->IsAnimationEnd() &&
			true == m_atkReady)
		{
			fsm->ChangeState(Name_Sickle_Attack_2);
		}
		// 공격 상태라면 뒤로 이동 상태로 변경
		else if ((Name_Sickle_Attack_2 == fsm->GetCurStateString() ||
			Name_Sickle_Attack_1 == fsm->GetCurStateString()) &&
			fsm->GetDM()->IsAnimationEnd())
		{
			fsm->ChangeState(Name_Sickle_Walk_Back);
		}
	}
}

SP(CSickleAtk02Pattern) CSickleAtk02Pattern::Create()
{
	SP(CSickleAtk02Pattern) spInstance(new CSickleAtk02Pattern, Engine::SmartDeleter<CSickleAtk02Pattern>);

	return spInstance;
}