#include "stdafx.h"
#include "GaneshaBurst02Pattern.h"

#include "FSM_GaneshaC.h"
#include "FSMDefine_Ganesha.h"
#include "MB_Ganesha.h"

#include "StateMachine.h"
#include "Valkyrie.h" 
#include "DynamicMeshData.h"
#include "AniCtrl.h"
#include "PatternMachineC.h"
#include "AttackBall.h"

CGaneshaBurst02Pattern::CGaneshaBurst02Pattern()
{
}

CGaneshaBurst02Pattern::~CGaneshaBurst02Pattern()
{
}

void CGaneshaBurst02Pattern::Pattern(Engine::CObject* pOwner)
{
	_float3 tPos = CStageControlTower::GetInstance()->GetCurrentActor()->GetTransform()->GetPosition(); // target pos
	_float3 mPos = pOwner->GetTransform()->GetPosition(); // monster pos
	_float len = D3DXVec3Length(&(tPos - mPos));
	SP(CFSM_GaneshaC) fsm = pOwner->GetComponent<CFSM_GaneshaC>();

	CoolTime(m_atkTime, m_atkCool, m_atkReady);
	CoolTime(m_walkTime, m_walkCool, m_walkReady);

	// ���� burst2 ���°� �ƴϸ� ��븦 ����
	if (Name_Ganesha_Burst02 != fsm->GetCurStateString())
	{
		static_cast<CMB_Ganesha*>(pOwner)->ChaseTarget(tPos);
	}

	// ��밡 burst2 ���� ���̰�
	if (len > m_atkDis)
	{
		// ���� burst2 ���¸�
		if (Name_Ganesha_Burst02 == fsm->GetCurStateString() && fsm->GetDM()->IsAnimationEnd())
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
	// ��밡 burst2 ���� ���̰�
	else if (len <= m_atkDis)
	{
		// ���� �̵� ���¶�� burst2
		if (Name_Ganesha_StandBy == fsm->GetCurStateString() && fsm->GetDM()->IsAnimationEnd())
		{
			fsm->ChangeState(Name_Ganesha_Burst02);
			Engine::CSoundManager::GetInstance()->StopSound((_uint)Engine::EChannelID::GANESHA_JUMPBACK);
			Engine::CSoundManager::GetInstance()->StartSound(L"Ganesha_Burst02.wav", (_uint)Engine::EChannelID::GANESHA_BARRIER);
		}
	}

	// ���� burst2 ���¶�� �ڷ� �̵�
	if (Name_Ganesha_Burst02 == fsm->GetCurStateString() && fsm->GetDM()->IsAnimationEnd())
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

	// ���� burst ���°�, ������ �� ���ú� �����
	if (Name_Ganesha_Burst02 == fsm->GetCurStateString() && 0.65f <= fsm->GetDM()->GetAniTimeline())
	{
		static_cast<CMB_Ganesha*>(pOwner)->UnActiveAttackBall();
	}
	// ���� burst ���°�, ������ �� ���ú� ����
	else if (Name_Ganesha_Burst02 == fsm->GetCurStateString() && 0.55f <= fsm->GetDM()->GetAniTimeline())
	{
		m_atkMat = pOwner->GetTransform()->GetWorldMatrix();
		static_cast<CMB_Ganesha*>(pOwner)->ActiveAttackBall(1.f, HitInfo::Str_High, HitInfo::CC_None, &m_atkMat, 3.4f);
		// ���� ������ �ݶ��̴� ũ�� ����
		//static_cast<Engine::CSphereCollider*>(static_cast<CMB_Ganesha*>(pOwner)->GetAttackBall()->GetCollision()->GetColliders()[0].get())->SetRadius(3.4f);
	}
}

SP(CGaneshaBurst02Pattern) CGaneshaBurst02Pattern::Create()
{
	SP(CGaneshaBurst02Pattern) spInstance(new CGaneshaBurst02Pattern, Engine::SmartDeleter<CGaneshaBurst02Pattern>);

	return spInstance;
}