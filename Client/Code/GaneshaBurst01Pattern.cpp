#include "stdafx.h"
#include "GaneshaBurst01Pattern.h"

#include "FSM_GaneshaC.h"
#include "FSMDefine_Ganesha.h"
#include "MB_Ganesha.h"

#include "StateMachine.h"
#include "Valkyrie.h" 
#include "DynamicMeshData.h"
#include "AniCtrl.h"
#include "PatternMachineC.h"
#include "AttackBall.h"

CGaneshaBurst01Pattern::CGaneshaBurst01Pattern()
{
}

CGaneshaBurst01Pattern::~CGaneshaBurst01Pattern()
{
}

void CGaneshaBurst01Pattern::Pattern(Engine::CObject* pOwner)
{
	_float3 tPos = CStageControlTower::GetInstance()->GetCurrentActor()->GetTransform()->GetPosition(); // target pos
	_float3 mPos = pOwner->GetTransform()->GetPosition(); // monster pos
	_float len = D3DXVec3Length(&(tPos - mPos));
	SP(CFSM_GaneshaC) fsm = pOwner->GetComponent<CFSM_GaneshaC>();

	CoolTime(m_atkTime, m_atkCool, m_atkReady);
	CoolTime(m_walkTime, m_walkCool, m_walkReady);

	// ���� burst1 ���°� �ƴϸ� ��븦 ����
	if (Name_Ganesha_Burst01 != fsm->GetCurStateString())
	{
		static_cast<CMB_Ganesha*>(pOwner)->ChaseTarget(tPos);
	}

	// ��밡 burst1 ���� ���̰�
	if (len > m_atkDis)
	{
		// ���� burst1 ���¸�
		if (Name_Ganesha_Burst01 == fsm->GetCurStateString() && fsm->GetDM()->IsAnimationEnd())
		{
			fsm->ChangeState(Name_Ganesha_Jump_Back);
		}
		// ���� ��� ���¸� �̵� �ִϷ� ����
		else if (Name_Ganesha_StandBy == fsm->GetCurStateString() && fsm->GetDM()->IsAnimationEnd())
		{
			fsm->ChangeState(Name_Ganesha_Run);
		}
		// ���� �̵� ���̶��
		else if (Name_Ganesha_Run == fsm->GetCurStateString())
		{
			_float3 dir = tPos - mPos;

			mPos += *D3DXVec3Normalize(&dir, &dir) * GET_DT;
			pOwner->GetTransform()->SetPosition(mPos);
		}
	}
	// ��밡 burst1 ���� ���̰�
	else if (len <= m_atkDis)
	{
		// ���� �̵� ���¶�� burst1
		if (Name_Ganesha_StandBy == fsm->GetCurStateString() && fsm->GetDM()->IsAnimationEnd())
		{
			fsm->ChangeState(Name_Ganesha_Burst01);
		}
	}

	// ���� burst1 ���¶�� �ڷ� �̵�
	if (Name_Ganesha_Burst01 == fsm->GetCurStateString() && fsm->GetDM()->IsAnimationEnd())
	{
		fsm->ChangeState(Name_Ganesha_Jump_Back);
		m_walkReady = false;
	}
	// ���� �ڷ� �̵� ���̶��
	else if (Name_Ganesha_Jump_Back == fsm->GetCurStateString() && 0.9f <= fsm->GetDM()->GetAniTimeline() && false == m_walkReady)
	{
		_float3 dir = tPos - mPos;

		mPos -= *D3DXVec3Normalize(&dir, &dir) * GET_DT;
		pOwner->GetTransform()->SetPosition(mPos);
	}
	// ���� �ڷ� �̵��� �����ٸ�
	else if (Name_Ganesha_Jump_Back == fsm->GetCurStateString() && 0.9f <= fsm->GetDM()->GetAniTimeline() && true == m_walkReady)
	{
		++m_jumpCnt;

		if (2 != m_jumpCnt)
		{
			m_walkReady = false;
		}
		else
		{
			fsm->ChangeState(Name_Ganesha_StandBy);
			m_jumpCnt = 0;
			pOwner->GetComponent<CPatternMachineC>()->SetOnSelect(false);
		}
	}

	// burst ���°� �Ϸ�Ǹ� attackball off �� ������Ʈ ����
	//if (Name_Ganesha_Burst01 == fsm->GetCurStateString() && 0.45f <= fsm->GetDM()->GetAniTimeline())
	//{
	//	static_cast<CMB_Ganesha*>(pOwner)->UnActiveAttackBall();
	//}
	// burst ���¶��
	else if (Name_Ganesha_Burst01 == fsm->GetCurStateString() && 0.3f <= fsm->GetDM()->GetAniTimeline())
	{
		m_atkMat = pOwner->GetTransform()->GetWorldMatrix();
		static_cast<CMB_Ganesha*>(pOwner)->ActiveAttackBall(1.f, HitInfo::Str_High, HitInfo::CC_None, &m_atkMat, 1.5f);
		// ���� ������ �ݶ��̴� ũ�� ����
		static_cast<Engine::CObbCollider*>(static_cast<CMB_Ganesha*>(pOwner)->GetAttackBall()->GetCollision()->GetColliders()[0].get())->SetSize(_float3(10.f, 3.f, 10.f));
		static_cast<Engine::CObbCollider*>(static_cast<CMB_Ganesha*>(pOwner)->GetAttackBall()->GetCollision()->GetColliders()[0].get())->SetHalfSize(_float3(10.f, 3.f, 10.f));
		static_cast<Engine::CObbCollider*>(static_cast<CMB_Ganesha*>(pOwner)->GetAttackBall()->GetCollision()->GetColliders()[0].get())->SetOffset(_float3(0.f, 0.f, 0.f));
		static_cast<Engine::CObbCollider*>(static_cast<CMB_Ganesha*>(pOwner)->GetAttackBall()->GetCollision()->GetColliders()[0].get())->SetRotOffset(_float3(0.f, 0.f, 0.f));
	}
}

SP(CGaneshaBurst01Pattern) CGaneshaBurst01Pattern::Create()
{
	SP(CGaneshaBurst01Pattern) spInstance(new CGaneshaBurst01Pattern, Engine::SmartDeleter<CGaneshaBurst01Pattern>);

	return spInstance;
}