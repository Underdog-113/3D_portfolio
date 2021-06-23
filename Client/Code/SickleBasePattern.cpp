#include "stdafx.h"
#include "SickleBasePattern.h"

#include "FSM_SickleC.h"
#include "FSMDefine_Sickle.h"
#include "MO_Sickle.h"

#include "StageControlTower.h"
#include "Valkyrie.h"
#include "DynamicMeshData.h"

CSickleBasePattern::CSickleBasePattern()
{
}

CSickleBasePattern::~CSickleBasePattern()
{
}

void CSickleBasePattern::Pattern(Engine::CObject* pOwner)
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
		// 내가 공격1 상태면
		if (Name_Sickle_Attack_1 == fsm->GetCurStateString() && fsm->GetDM()->IsAnimationEnd())
		{
			fsm->ChangeState(Name_Sickle_Walk_Back);
		}
		// 내가 대기 상태면 이동 애니로 변경
		else if (Name_Sickle_StandBy == fsm->GetCurStateString() && fsm->GetDM()->IsAnimationEnd())
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
		// 내가 이동 상태 or 대기 상태라면 공격
		if ((Name_Sickle_Walk_Forward == fsm->GetCurStateString() ||
			Name_Sickle_StandBy == fsm->GetCurStateString()) &&
			fsm->GetDM()->IsAnimationEnd())
		{
			fsm->ChangeState(Name_Sickle_Attack_1);
			static_cast<CMO_Sickle*>(pOwner)->ActiveAttackBall(1.f, HitInfo::Str_Low, HitInfo::CC_None, static_cast<CMO_Sickle*>(pOwner)->GetRightHandWorldMatrix(), 0.5f);
		}
		// 공격1 상태라면 뒤로 이동 상태로 변경
		else if (Name_Sickle_Attack_1 == fsm->GetCurStateString() && fsm->GetDM()->IsAnimationEnd())
		{
			fsm->ChangeState(Name_Sickle_Walk_Back);
		}
	}
}

SP(CSickleBasePattern) CSickleBasePattern::Create()
{
	SP(CSickleBasePattern) spInstance(new CSickleBasePattern, Engine::SmartDeleter<CSickleBasePattern>);

	return spInstance;
}