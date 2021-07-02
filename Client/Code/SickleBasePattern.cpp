#include "stdafx.h"
#include "SickleBasePattern.h"

#include "FSM_SickleC.h"
#include "FSMDefine_Sickle.h"
#include "MO_Sickle.h"

#include "StageControlTower.h"
#include "Valkyrie.h"
#include "DynamicMeshData.h"
#include "AttackBall.h"

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

	/************************* Range */
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
		// ���� �̵�, ��� ���¶�� ����
		if ((Name_Sickle_Walk_Forward == fsm->GetCurStateString() ||
			Name_Sickle_StandBy == fsm->GetCurStateString() ||
			Name_Sickle_Walk_Back == fsm->GetCurStateString()) &&
			fsm->GetDM()->IsAnimationEnd())
		{
			fsm->ChangeState(Name_Sickle_Attack_1);
			PatternPlaySound(L"Sickle_Skill_0.wav", pOwner);
		}
		// ����1 ���¶�� �ڷ� �̵� ���·� ����
		else if (Name_Sickle_Attack_1 == fsm->GetCurStateString() && fsm->GetDM()->IsAnimationEnd())
		{
			fsm->ChangeState(Name_Sickle_Walk_Back);
		}
	}

	/************************* AttackBall */
	// ���� ���� ���°�, ������ �� ���ú� �����
	if (Name_Sickle_Attack_1 == fsm->GetCurStateString() && 0.47f <= fsm->GetDM()->GetAniTimeline())
	{
		static_cast<CMO_Sickle*>(pOwner)->UnActiveAttackBall();
	}
	// ���� ���� ���°�, ������ �� ���ú� ����
	else if (Name_Sickle_Attack_1 == fsm->GetCurStateString() && 0.37f <= fsm->GetDM()->GetAniTimeline())
	{
		m_atkMat = pOwner->GetTransform()->GetWorldMatrix();

		_float3 look = _float3(m_atkMat._31, m_atkMat._32, m_atkMat._33);
		D3DXVec3Normalize(&look, &look);

		m_atkMat._42 += pOwner->GetComponent<Engine::CMeshC>()->GetHalfYOffset();
		m_atkMat._41 += (m_atkDis * look.x / 1.8f);
		m_atkMat._43 += (m_atkDis * look.z / 1.8f);

		static_cast<CMO_Sickle*>(pOwner)->ActiveAttackBall(1.f, HitInfo::Str_Low, HitInfo::CC_None, &m_atkMat, 0.34f);
	}
}

SP(CSickleBasePattern) CSickleBasePattern::Create()
{
	SP(CSickleBasePattern) spInstance(new CSickleBasePattern, Engine::SmartDeleter<CSickleBasePattern>);

	return spInstance;
}