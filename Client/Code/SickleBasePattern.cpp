#include "stdafx.h"
#include "SickleBasePattern.h"

//#include "FSM_SickleC.h"
#include "FSMDefine_Sickle.h"
#include "MO_Sickle.h"

#include "StageControlTower.h"
#include "Valkyrie.h"

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

	CoolTime(m_atkTime, m_atkCool, m_atkReady);
	CoolTime(m_walkTime, m_walkCool, m_walkReady);

	static_cast<CMO_Sickle*>(pOwner)->ChaseTarget(tPos);

	if (len > m_atkDis)
	{
		// 공격1 상태면
		if (Name_Sickle_Attack_1 == m_fsm->GetCurStateString() && m_fsm->GetDM()->IsAnimationEnd())
		{
			m_fsm->ChangeState(Name_Sickle_Walk_Back);
			m_sicklePattern1 = false;
			m_sicklePattern2 = true;
		}
	}
}

SP(CSickleBasePattern) CSickleBasePattern::Create()
{
	SP(CSickleBasePattern) spInstance(new CSickleBasePattern, Engine::SmartDeleter<CSickleBasePattern>);

	return spInstance;
}