#include "stdafx.h"
#include "LancerAttack2Pattern.h"

#include "FSM_LancerC.h"
#include "FSMDefine_Lancer.h"
#include "MO_Lancer.h"

#include "StateMachineC.h"
#include "Valkyrie.h" 
#include "DynamicMeshData.h"
#include "AniCtrl.h"
#include "PatternMachineC.h"
#include "AttackBox.h"
#include "StageControlTower.h"

CLancerAttack2Pattern::CLancerAttack2Pattern()
{
}

CLancerAttack2Pattern::~CLancerAttack2Pattern()
{
}

void CLancerAttack2Pattern::Pattern(Engine::CObject* pOwner)
{
	_float3 tPos = CStageControlTower::GetInstance()->GetCurrentActor()->GetTransform()->GetPosition(); // target pos
	_float3 mPos = pOwner->GetTransform()->GetPosition(); // monster pos
	_float len = D3DXVec3Length(&(tPos - mPos));
	SP(CFSM_LancerC) fsm = pOwner->GetComponent<CFSM_LancerC>();

	//CoolTime(m_atkTime, m_atkCool, m_atkReady);
	//CoolTime(m_walkTime, m_walkCool, m_walkReady);

	// ���� ��븦 ����
	if (Name_ATTACK_2 != fsm->GetCurStateString())
	{
		static_cast<CMO_Lancer*>(pOwner)->ChaseTarget(tPos);
	}

	/************************* Sound */
	//// run start sound
	//if ((Name_WALK_FORWARD == fsm->GetCurStateString() ||
	//	 Name_RUN_B == fsm->GetCurStateString()) &&
	//	 true == m_onWalk)
	//{
	//	PatternRepeatSound(m_curMoveSound, pOwner, 0.4f);
	//}
	//else if ((Name_RUN_F == fsm->GetCurStateString() ||
	//		  Name_RUN_B == fsm->GetCurStateString()) &&
	//		  false == m_onWalk)
	//{
	//	PatternStopSound(pOwner);
	//}

	/************************* Range */
	// ��밡 ���� ���� ���̰�
	if (len > m_atkDis)
	{
		// ���� ����2 ���¸�
		if (Name_ATTACK_2 == fsm->GetCurStateString() && fsm->GetDM()->IsAnimationEnd())
		{
			fsm->ChangeState(Name_WALK_BACKWARD);
		}
		// ���� ��� ���°� �����ٸ�
		else if (Name_STAND == fsm->GetCurStateString() && fsm->GetDM()->IsAnimationEnd())
		{
			fsm->ChangeState(Name_WALK_FORWARD);
		}
		// ���� ��� ���°� �����ٸ�
		else if (Name_WALK_FORWARD == fsm->GetCurStateString())
		{
			_float3 dir = tPos - mPos;

			mPos += *D3DXVec3Normalize(&dir, &dir) * GET_DT;
			pOwner->GetTransform()->SetPosition(mPos);
		}
		// ���� �ڷ� �̵� ���̶��
		else if (Name_WALK_BACKWARD == fsm->GetCurStateString() && fsm->GetDM()->IsAnimationEnd() && false == m_walkReady)
		{
			_float3 dir = tPos - mPos;

			mPos -= *D3DXVec3Normalize(&dir, &dir) * GET_DT;
			pOwner->GetTransform()->SetPosition(mPos);
			m_onWalk = true;
		}
		// ���� �ڷ� �̵��� �����ٸ�
		else if (Name_WALK_BACKWARD == fsm->GetCurStateString() && fsm->GetDM()->IsAnimationEnd() && true == m_walkReady)
		{
			fsm->ChangeState(Name_WALK_FORWARD);
			pOwner->GetComponent<CPatternMachineC>()->SetOnSelect(false);
		}
	}
	// ��밡 ���� ���� ���̰�
	else if (len <= m_atkDis)
	{
		// ���� �̵�, ��� ���¶�� ����
		if ((Name_WALK_FORWARD == fsm->GetCurStateString() ||
			Name_STAND == fsm->GetCurStateString() ||
			Name_WALK_BACKWARD == fsm->GetCurStateString()) &&
			fsm->GetDM()->IsAnimationEnd())
		{
			fsm->ChangeState(Name_ATTACK_2);
		}
		// ����2 ���¶�� �ڷ� �̵� ���·� ����
		else if (Name_ATTACK_2 == fsm->GetCurStateString() && fsm->GetDM()->IsAnimationEnd())
		{
			fsm->ChangeState(Name_WALK_BACKWARD);
			m_walkReady = false;
		}
	}

 	/************************* AttackBox */
	// shoot2 ���°� �Ϸ�Ǹ� attackbox off
	//if (Name_SHOOT_2 == fsm->GetCurStateString() && 
	//	0.7f <= fsm->GetDM()->GetAniTimeline())
	//{
	//	m_onShoot2 = false;
	//	static_cast<CMO_Scout*>(pOwner)->UnActiveAttackBox();
	//}
	//// shoot2 ���¶��
	//else if (Name_SHOOT_2 == fsm->GetCurStateString() &&
	//	0.65f <= fsm->GetDM()->GetAniTimeline() &&
	//	0.7f > fsm->GetDM()->GetAniTimeline() &&
	//	false == m_onShoot2)
	//{
	//	m_onShoot2 = true;
	//	m_atkMat = pOwner->GetTransform()->GetWorldMatrix();
	//	CMO_Scout* pScout = static_cast<CMO_Scout*>(pOwner);
	//	_float3 size = { 2.f, 1.f, 10.f };
	//	_float3 offset = ZERO_VECTOR;
	//	_float3 mPos = pOwner->GetTransform()->GetPosition();
	//	
	//	pScout->GetAttackBox()->GetTransform()->SetRotation(pScout->GetTransform()->GetRotation());
	//	pScout->GetAttackBox()->GetTransform()->SetPosition(mPos);

	//	offset = _float3(0, 0, 5);

	//	pScout->ActiveAttackBox(1.f, HitInfo::Str_Low, HitInfo::CC_None, &m_atkMat, size, offset, ZERO_VECTOR);
	//}
}

SP(CLancerAttack2Pattern) CLancerAttack2Pattern::Create()
{
	SP(CLancerAttack2Pattern) spInstance(new CLancerAttack2Pattern, Engine::SmartDeleter<CLancerAttack2Pattern>);

	return spInstance;
}

void CLancerAttack2Pattern::SetMoveSound()
{
	/************************* Choose Move Sound */
	_int index = GetRandRange(0, 2);

	switch (index)
	{
	case 0:
		m_curMoveSound = L"Scout_Move_0.wav";
		break;
	case 1:
		m_curMoveSound = L"Scout_Move_1.wav";
		break;
	case 2:
		m_curMoveSound = L"Scout_Move_2.wav";
		break;
	}
}
