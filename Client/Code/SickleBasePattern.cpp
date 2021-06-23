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

	// ��밡 ���� ���� ���̰�
	if (len > m_atkDis)
	{
		// ���� ����1 ���¸�
		if (Name_Sickle_Attack_1 == fsm->GetCurStateString() && fsm->GetDM()->IsAnimationEnd())
		{
			fsm->ChangeState(Name_Sickle_Walk_Back);
		}
		// ���� ��� ���¸� �̵� �ִϷ� ����
		else if (Name_Sickle_StandBy == fsm->GetCurStateString() && fsm->GetDM()->IsAnimationEnd())
		{
			fsm->ChangeState(Name_Sickle_Walk_Forward);
		}
		// ���� �̵� ���̶��
		else if (Name_Sickle_Walk_Forward == fsm->GetCurStateString())
		{
			_float3 dir = tPos - mPos;

			mPos += *D3DXVec3Normalize(&dir, &dir) * GET_DT;
			pOwner->GetTransform()->SetPosition(mPos);
		}
		// ���� �ڷ� �̵� ���̶��
		else if (Name_Sickle_Walk_Back == fsm->GetCurStateString() && fsm->GetDM()->IsAnimationEnd() && false == m_walkReady)
		{
			_float3 dir = tPos - mPos;

			mPos -= *D3DXVec3Normalize(&dir, &dir) * GET_DT;
			pOwner->GetTransform()->SetPosition(mPos);
		}
		// ���� �ڷ� �̵��� �����ٸ�
		else if (Name_Sickle_Walk_Back == fsm->GetCurStateString() && fsm->GetDM()->IsAnimationEnd() && true == m_walkReady)
		{
			fsm->ChangeState(Name_Sickle_Walk_Forward);
		}
	}
	// ��밡 ���� ���� ���̰�
	else if (len <= m_atkDis)
	{
		// ���� �̵� ���� or ��� ���¶�� ����
		if ((Name_Sickle_Walk_Forward == fsm->GetCurStateString() ||
			Name_Sickle_StandBy == fsm->GetCurStateString()) &&
			fsm->GetDM()->IsAnimationEnd())
		{
			fsm->ChangeState(Name_Sickle_Attack_1);
			static_cast<CMO_Sickle*>(pOwner)->ActiveAttackBall(1.f, HitInfo::Str_Low, HitInfo::CC_None, static_cast<CMO_Sickle*>(pOwner)->GetRightHandWorldMatrix(), 0.5f);
		}
		// ����1 ���¶�� �ڷ� �̵� ���·� ����
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