#include "stdafx.h"
#include "SpiderBasePattern.h"

#include "FSM_SpiderC.h"
#include "FSMDefine_Spider.h"
#include "MO_Spider.h"

#include "StageControlTower.h"
#include "Valkyrie.h"
#include "DynamicMeshData.h"

CSpiderBasePattern::CSpiderBasePattern()
{
}

CSpiderBasePattern::~CSpiderBasePattern()
{
}

void CSpiderBasePattern::Pattern(Engine::CObject* pOwner)
{
	_float3 tPos = CStageControlTower::GetInstance()->GetCurrentActor()->GetTransform()->GetPosition(); // target pos
	_float3 mPos = pOwner->GetTransform()->GetPosition(); // monster pos
	_float len = D3DXVec3Length(&(tPos - mPos));
	SP(CFSM_SpiderC) fsm = pOwner->GetComponent<CFSM_SpiderC>();

	CoolTime(m_atkTime, m_atkCool, m_atkReady);
	CoolTime(m_walkTime, m_walkCool, m_walkReady);

	static_cast<CMO_Spider*>(pOwner)->ChaseTarget(tPos);

	// ��밡 ���� ���� ���̰�
	if (len > m_atkDis)
	{
		// ���� ��� ���¸� �̵� �ִϷ� ����
		if (Name_StandBy == fsm->GetCurStateString() && fsm->GetDM()->IsAnimationEnd())
		{
			fsm->ChangeState(Name_Walk_Forward);
		}
		// ���� �̵� ���̶��
		else if (Name_Walk_Forward == fsm->GetCurStateString())
		{
			_float3 dir = tPos - mPos;

			mPos += *D3DXVec3Normalize(&dir, &dir) * GET_DT;
			pOwner->GetTransform()->SetPosition(mPos);
		}
	}
	// ��밡 ���� ���� ���̰�
	else if (len <= m_atkDis)
	{
		// ���� �̵� ���¶�� ����
		if (Name_Walk_Forward == fsm->GetCurStateString() && fsm->GetDM()->IsAnimationEnd())
		{
			fsm->ChangeState(Name_Attack_1);
		}
		
	}

	// ����1 ���¶�� �����
	if (Name_Attack_1 == fsm->GetCurStateString() && fsm->GetDM()->IsAnimationEnd())
	{
		pOwner->SetDeleteThis(true);
	}
}

SP(CSpiderBasePattern) CSpiderBasePattern::Create()
{
	SP(CSpiderBasePattern) spInstance(new CSpiderBasePattern, Engine::SmartDeleter<CSpiderBasePattern>);

	return spInstance;
}