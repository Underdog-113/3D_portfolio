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

	// ��밡 ���� ���� ���̰�
	if (len > m_atkDis)
	{
		// ���� ����2 ���¸�
		if (Name_Sickle_Attack_2 == fsm->GetCurStateString() && fsm->GetDM()->IsAnimationEnd())
		{
			fsm->ChangeState(Name_Sickle_Walk_Back);
		}
		// ���� ��� ���¸� �̵� �ִϷ� ����
		else if ((Name_Sickle_StandBy == fsm->GetCurStateString() ||
			Name_Sickle_Attack_1 == fsm->GetCurStateString())
			&& fsm->GetDM()->IsAnimationEnd())
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
		// ���� �̵� ����, ���� ��ٿ� ���̶�� ���
		if (Name_Sickle_Walk_Forward == fsm->GetCurStateString() &&
			fsm->GetDM()->IsAnimationEnd() &&
			false == m_atkReady)
		{
			fsm->ChangeState(Name_Sickle_StandBy);
		}
		// ���� �̵� ���¶�� ����
		else if ((Name_Sickle_Walk_Forward == fsm->GetCurStateString()) &&
			fsm->GetDM()->IsAnimationEnd() &&
			true == m_atkReady)
		{
			fsm->ChangeState(Name_Sickle_Attack_2);
		}
		// ���� ���¶�� �ڷ� �̵� ���·� ����
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