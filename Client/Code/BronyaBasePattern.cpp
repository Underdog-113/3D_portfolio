#include "stdafx.h"
#include "BronyaBasePattern.h"

#include "FSM_BronyaC.h"
#include "FSMDefine_Bronya.h"
#include "MB_Bronya.h"

#include "StateMachineC.h"
#include "Valkyrie.h" 
#include "DynamicMeshData.h"
#include "AniCtrl.h"
#include "PatternMachineC.h"
#include "AttackBall.h"

CBronyaBasePattern::CBronyaBasePattern()
{
}

CBronyaBasePattern::~CBronyaBasePattern()
{
}

void CBronyaBasePattern::Pattern(Engine::CObject* pOwner)
{
	_float3 tPos = CStageControlTower::GetInstance()->GetCurrentActor()->GetTransform()->GetPosition(); // target pos
	_float3 mPos = pOwner->GetTransform()->GetPosition(); // monster pos
	_float len = D3DXVec3Length(&(tPos - mPos));
	SP(CFSM_BronyaC) fsm = pOwner->GetComponent<CFSM_BronyaC>();

	CoolTime(m_atkTime, m_atkCool, m_atkReady);
	CoolTime(m_walkTime, m_walkCool, m_walkReady);

	//if (Name_Shoot_1 != fsm->GetCurStateString() &&
	//	Name_Evade_Left != fsm->GetCurStateString() &&
	//	Name_Evade_Right != fsm->GetCurStateString())
	//{
	//	static_cast<CMB_Bronya*>(pOwner)->ChaseTarget(tPos);
	//}

	// ��밡 ���� ���� ���̰�
	if (len <= m_atkDis)
	{
		// ���� �̵�, ��� ���°� �����ٸ�
		if ((Name_Run == fsm->GetCurStateString() ||
			Name_IDLE == fsm->GetCurStateString()) &&
			fsm->GetDM()->IsAnimationEnd() &&
			true == m_atkReady)
		{
			fsm->ChangeState(Name_Shoot_1);
			m_atkReady = false;
		}
	}
	// ���� shoot1�� ��Ÿ���̶��
	//else if ()

	/************************* Evade */
	// ���� shoot1 ���°� �����ٸ�
	if (Name_Shoot_1 == fsm->GetCurStateString() &&
		fsm->GetDM()->IsAnimationEnd() &&
		false == m_atkReady)
	{
		fsm->ChangeState(Name_Evade_Left);
	}
} 

SP(CBronyaBasePattern) CBronyaBasePattern::Create()
{
	SP(CBronyaBasePattern) spInstance(new CBronyaBasePattern, Engine::SmartDeleter<CBronyaBasePattern>);

	return spInstance;
}