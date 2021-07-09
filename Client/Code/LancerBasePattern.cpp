#include "stdafx.h"
#include "LancerBasePattern.h"

#include "FSM_LancerC.h"
#include "FSMDefine_Lancer.h"
#include "MO_Lancer.h"

#include "StageControlTower.h"
#include "Valkyrie.h"
#include "DynamicMeshData.h"
#include "AttackBall.h"

CLancerBasePattern::CLancerBasePattern()
{
}

CLancerBasePattern::~CLancerBasePattern()
{
}

void CLancerBasePattern::Pattern(Engine::CObject* pOwner)
{
	_float3 tPos = CStageControlTower::GetInstance()->GetCurrentActor()->GetTransform()->GetPosition(); // target pos
	_float3 mPos = pOwner->GetTransform()->GetPosition(); // monster pos
	_float len = D3DXVec3Length(&(tPos - mPos));
	SP(CFSM_LancerC) fsm = pOwner->GetComponent<CFSM_LancerC>();

	if (false == fsm->GetDM())
		return;

	CoolTime(m_atkTime, m_atkCool, m_atkReady);
	CoolTime(m_walkTime, m_walkCool, m_walkReady);

	// ���� ����1 ���°� �ƴ϶�� ��� ����
	if (Name_ATTACK_1 != fsm->GetCurStateString())
	{
		static_cast<CMO_Lancer*>(pOwner)->ChaseTarget(tPos);
	}

	/************************* Range */
	// ��밡 ���� ���� ���̰�
	if (len > m_atkDis)
	{
		// ���� ����1 ���°� �����ٸ�
		if (Name_ATTACK_1 == fsm->GetCurStateString() &&
			fsm->GetDM()->IsAnimationEnd())
		{
			// �ڷ� �̵�
			fsm->ChangeState(Name_WALK_BACKWARD);
		}
		// ���� ��� ���°� �����ٸ�
		else if (Name_STAND == fsm->GetCurStateString() &&
			fsm->GetDM()->IsAnimationEnd())
		{
			// ������ �̵�
			fsm->ChangeState(Name_WALK_FORWARD);
		}
		//// ���� �̵� ���̶��
		//else if (Name_WALK_FORWARD == fsm->GetCurStateString())
		//{
		//	_float3 dir = tPos - mPos;

		//	mPos += *D3DXVec3Normalize(&dir, &dir) * GET_DT;
		//	pOwner->GetTransform()->SetPosition(mPos);
		//}
		//// ���� �ڷ� �̵� ���̶��
		//else if (Name_WALK_BACKWARD == fsm->GetCurStateString() &&
		//	fsm->GetDM()->IsAnimationEnd() &&
		//	false == m_walkReady)
		//{
		//	_float3 dir = tPos - mPos;

		//	mPos -= *D3DXVec3Normalize(&dir, &dir) * GET_DT;
		//	pOwner->GetTransform()->SetPosition(mPos);
		//}
		// ���� �ڷ� �̵��� �����ٸ�
		else if (Name_WALK_BACKWARD == fsm->GetCurStateString() &&
			fsm->GetDM()->IsAnimationEnd() &&
			true == m_walkReady)
		{
			// ������ �̵�
			fsm->ChangeState(Name_WALK_FORWARD);
			pOwner->GetComponent<CPatternMachineC>()->SetOnBase(false);
		}
	}
	// ��밡 ���� ���� ���̰�
	else if (len <= m_atkDis)
	{
		// ���� �̵�, ��� ���°� �����ٸ�
		if ((Name_WALK_FORWARD == fsm->GetCurStateString() ||
			Name_WALK_BACKWARD == fsm->GetCurStateString() ||
			Name_STAND == fsm->GetCurStateString()) &&
			fsm->GetDM()->IsAnimationEnd())
		{
			// ���� ���·� ����
			fsm->ChangeState(Name_ATTACK_1);
			PatternPlaySound(L"Lencer_Skill_Attack_2.wav", pOwner);
			m_onEffect = false;
			return;
		}
		// ���� ����1 ���°� �����ٸ�
		else if (Name_ATTACK_1 == fsm->GetCurStateString() &&
			fsm->GetDM()->IsAnimationEnd())
		{
			// �ڷ� �̵�
			fsm->ChangeState(Name_WALK_BACKWARD);
		}
	}

	/************************* AttackBall */
	// ���� ���� ���°�, ������ �� ���ú� �����
	if (Name_ATTACK_1 == fsm->GetCurStateString() &&
		0.54f <= fsm->GetDM()->GetAniTimeline())
	{
		static_cast<CMO_Lancer*>(pOwner)->UnActiveAttackBall();
	}
	// ���� ���� ���°�, ������ �� ���ú� ����
	else if (Name_ATTACK_1 == fsm->GetCurStateString() &&
		0.37f <= fsm->GetDM()->GetAniTimeline())
	{
		m_atkMat = pOwner->GetTransform()->GetWorldMatrix();

		_float3 look = _float3(m_atkMat._31, m_atkMat._32, m_atkMat._33);
		D3DXVec3Normalize(&look, &look);

		m_atkMat._42 += pOwner->GetComponent<Engine::CMeshC>()->GetHalfYOffset();
		m_atkMat._41 += (m_atkDis * look.x / 1.6f);
		m_atkMat._43 += (m_atkDis * look.z / 1.6f);
	}

	/************************* Effect */
	if (Name_ATTACK_1 == fsm->GetCurStateString() &&
		0.27f <= fsm->GetDM()->GetAniTimeline() &&
		false == m_onEffect)
	{
		static_cast<CMO_Lancer*>(pOwner)->ActiveAttackBall(1.f, HitInfo::Str_High, HitInfo::CC_None, &m_atkMat, 0.45f);
		SP(Engine::CObject) spEffect = Engine::GET_CUR_SCENE->GetObjectFactory()->AddClone(L"Lancer_OutSideEff", true);
		spEffect->GetTransform()->SetSize(0.7f, 0.7f, 0.7f);
		spEffect->GetTransform()->SetPosition(_float3(m_atkMat._41, m_atkMat._42, m_atkMat._43));

		m_onEffect = true;
	}
}

SP(CLancerBasePattern) CLancerBasePattern::Create()
{
	SP(CLancerBasePattern) spInstance(new CLancerBasePattern, Engine::SmartDeleter<CLancerBasePattern>);

	return spInstance;
}