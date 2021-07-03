#include "stdafx.h"
#include "BronyaShock1Pattern.h"

#include "FSM_BronyaC.h"
#include "FSMDefine_Bronya.h"
#include "MB_Bronya.h"

#include "StateMachineC.h"
#include "Valkyrie.h" 
#include "DynamicMeshData.h"
#include "AniCtrl.h"
#include "PatternMachineC.h"
#include "AttackBall.h"

CBronyaShock1Pattern::CBronyaShock1Pattern()
{
}

CBronyaShock1Pattern::~CBronyaShock1Pattern()
{
}

void CBronyaShock1Pattern::Pattern(Engine::CObject* pOwner)
{
	_float3 tPos = CStageControlTower::GetInstance()->GetCurrentActor()->GetTransform()->GetPosition(); // target pos
	_float3 mPos = pOwner->GetTransform()->GetPosition(); // monster pos
	_float len = D3DXVec3Length(&(tPos - mPos));
	SP(CFSM_BronyaC) fsm = pOwner->GetComponent<CFSM_BronyaC>();

	CoolTime(m_walkTime, m_walkCool, m_walkReady);

	if (Name_Shock_1 != fsm->GetCurStateString())
	{
		static_cast<CMB_Bronya*>(pOwner)->ChaseTarget(tPos);
	}

	/************************* Range */
	// ��밡 ���� ���� ���̰�
	if (len > m_atkDis)
	{
		// ���� ��� ���°� �����ٸ�
		if (Name_IDLE == fsm->GetCurStateString() &&
			fsm->GetDM()->IsAnimationEnd())
		{
			// �̵� ���·� ����
			fsm->ChangeState(Name_Run);
		}
	}
	// ��밡 ���� ���� ���̰�
	else if (len <= m_atkDis)
	{
		//// ���� �̵�, ��� ���°� �����ٸ�
		//if ((Name_Run == fsm->GetCurStateString() ||
		//	Name_IDLE == fsm->GetCurStateString()) &&
		//	fsm->GetDM()->IsAnimationEnd())
		//{
		//	// shoot1 ���·� ����
		//	fsm->ChangeState(Name_Shoot_1);
		//}

		// ���� ��� ���¶��
		if (Name_IDLE == fsm->GetCurStateString() ||
			Name_Run == fsm->GetCurStateString())
		{
			// shock1 ���·� ����
			fsm->ChangeState(Name_Shock_1);
		}
	}

	/************************* Running */
	// ���� ��뿡�� �ٰ����� �ִٸ�
	if (Name_Run == fsm->GetCurStateString())
	{
		_float3 dir = tPos - mPos;

		mPos += *D3DXVec3Normalize(&dir, &dir) * GET_DT * 4.f;
		pOwner->GetTransform()->SetPosition(mPos);
	}

	/************************* Shock1 End */
	// ���� shock1 ���°� �����ٸ�
	if (Name_Shock_1 == fsm->GetCurStateString() &&
		fsm->GetDM()->IsAnimationEnd())
	{
		// ��� ���·� ����
		fsm->ChangeState(Name_IDLE);
		pOwner->GetComponent<CPatternMachineC>()->SetOnSelect(false);
	}
} 

SP(CBronyaShock1Pattern) CBronyaShock1Pattern::Create()
{
	SP(CBronyaShock1Pattern) spInstance(new CBronyaShock1Pattern, Engine::SmartDeleter<CBronyaShock1Pattern>);

	return spInstance;
}