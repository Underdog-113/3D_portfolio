#include "stdafx.h"
#include "NinzaBasePattern.h"

#include "FSM_NinzaC.h"
#include "FSMDefine_Ninza.h"
#include "MO_Ninza.h"

#include "StageControlTower.h"
#include "Valkyrie.h"
#include "DynamicMeshData.h"
#include "AttackBall.h"

CNinzaBasePattern::CNinzaBasePattern()
{
}

CNinzaBasePattern::~CNinzaBasePattern()
{
}

void CNinzaBasePattern::Pattern(Engine::CObject* pOwner)
{
	_float3 tPos = CStageControlTower::GetInstance()->GetCurrentActor()->GetTransform()->GetPosition(); // target pos
	_float3 mPos = pOwner->GetTransform()->GetPosition(); // monster pos
	_float len = D3DXVec3Length(&(tPos - mPos));
	SP(CFSM_NinzaC) fsm = pOwner->GetComponent<CFSM_NinzaC>();

	if (false == fsm->GetDM())
		return;

	CoolTime(m_atkTime, m_atkCool, m_atkReady);
	CoolTime(m_walkTime, m_walkCool, m_walkReady);

	//if (Name_attack_1_as != fsm->GetCurStateString() ||
	//	Name_attack_1_atk != fsm->GetCurStateString() ||
	//	Name_attack_1_bs != fsm->GetCurStateString())
	//{
	//	
	//}

	//static_cast<CMO_Ninza*>(pOwner)->ChaseTarget(tPos);

	/************************* Range */
	// ��밡 ���� ���� ���̰�
	//if (len > m_atkDis)
	//{
	//	// ���� ����1 ���°� �����ٸ�
	//	if (Name_attack_1_bs == fsm->GetCurStateString() &&
	//		fsm->GetDM()->IsAnimationEnd())
	//	{
	//		fsm->ChangeState(Name_walk_b);
	//	}
	//	// ���� ��� ���°� �����ٸ�
	//	else if (Name_standby == fsm->GetCurStateString() &&
	//		fsm->GetDM()->IsAnimationEnd())
	//	{
	//		fsm->ChangeState(Name_walk_f);
	//	}
	//	// ���� �̵� ���̶��
	//	else if (Name_walk_f == fsm->GetCurStateString())
	//	{
	//		_float3 dir = tPos - mPos;

	//		mPos += *D3DXVec3Normalize(&dir, &dir) * GET_DT;
	//		pOwner->GetTransform()->SetPosition(mPos);
	//	}
	//	// ���� �ڷ� �̵� ���̶��
	//	else if (Name_walk_b == fsm->GetCurStateString() &&
	//		fsm->GetDM()->IsAnimationEnd() &&
	//		false == m_walkReady)
	//	{
	//		_float3 dir = tPos - mPos;

	//		mPos -= *D3DXVec3Normalize(&dir, &dir) * GET_DT;
	//		pOwner->GetTransform()->SetPosition(mPos);
	//	}
	//	// ���� �ڷ� �̵��� �����ٸ�
	//	else if (Name_walk_b == fsm->GetCurStateString() &&
	//		fsm->GetDM()->IsAnimationEnd() &&
	//		true == m_walkReady)
	//	{
	//		fsm->ChangeState(Name_walk_f);
	//		pOwner->GetComponent<CPatternMachineC>()->SetOnBase(false);
	//	}
	//}
	//// ��밡 ���� ���� ���̰�
	//else if (len <= m_atkDis)
	//{
	//	// ���� �̵�, ��� ���°� �����ٸ�
	//	if ((Name_walk_f == fsm->GetCurStateString() ||
	//		Name_standby == fsm->GetCurStateString()) &&
	//		fsm->GetDM()->IsAnimationEnd())
	//	{
	//		fsm->ChangeState(Name_attack_1_as);
	//		//PatternPlaySound(L"Lencer_Skill_Attack_2.wav", pOwner);
	//	}
	//	// ���� attack_1_as ���°� �����ٸ�
	//	else if (Name_attack_1_as == fsm->GetCurStateString() &&
	//		fsm->GetDM()->IsAnimationEnd())
	//	{
	//		fsm->ChangeState(Name_attack_1_atk);
	//	}
	//	// ���� attack_1_atk ���°� �����ٸ�
	//	else if (Name_attack_1_atk == fsm->GetCurStateString() &&
	//		fsm->GetDM()->IsAnimationEnd())
	//	{
	//		fsm->ChangeState(Name_attack_1_bs);
	//	}
	//	// ���� attack_1_bs ���°� �����ٸ�
	//	else if (Name_attack_1_bs == fsm->GetCurStateString() &&
	//		fsm->GetDM()->IsAnimationEnd())
	//	{
	//		fsm->ChangeState(Name_walk_b);
	//	}
	//}

	///************************* AttackBall */
	//// ���� ���� ���°�, ������ �� ���ú� �����
	//if (Name_ATTACK_1 == fsm->GetCurStateString() && 0.54f <= fsm->GetDM()->GetAniTimeline())
	//{
	//	static_cast<CMO_Lancer*>(pOwner)->UnActiveAttackBall();
	//}
	//// ���� ���� ���°�, ������ �� ���ú� ����
	//else if (Name_ATTACK_1 == fsm->GetCurStateString() && 0.37f <= fsm->GetDM()->GetAniTimeline())
	//{
	//	m_atkMat = pOwner->GetTransform()->GetWorldMatrix();

	//	_float3 look = _float3(m_atkMat._31, m_atkMat._32, m_atkMat._33);
	//	D3DXVec3Normalize(&look, &look);

	//	m_atkMat._42 += pOwner->GetComponent<Engine::CMeshC>()->GetHalfYOffset();
	//	m_atkMat._41 += (m_atkDis * look.x / 1.6f);
	//	m_atkMat._43 += (m_atkDis * look.z / 1.6f);

	//	static_cast<CMO_Lancer*>(pOwner)->ActiveAttackBall(1.f, HitInfo::Str_High, HitInfo::CC_None, &m_atkMat, 0.45f);
	//}
}

SP(CNinzaBasePattern) CNinzaBasePattern::Create()
{
	SP(CNinzaBasePattern) spInstance(new CNinzaBasePattern, Engine::SmartDeleter<CNinzaBasePattern>);

	return spInstance;
}