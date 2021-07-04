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

	// 내가 공격2 상태가 아니라면 상대를 추적
	if (Name_ATTACK_2 != fsm->GetCurStateString())
	{
		static_cast<CMO_Lancer*>(pOwner)->ChaseTarget(tPos);
	}

	/************************* Range */
	// 상대가 공격 범위 밖이고
	if (len > m_atkDis)
	{
		// 내가 공격2 상태가 끝났다면
		if (Name_ATTACK_2 == fsm->GetCurStateString() &&
			fsm->GetDM()->IsAnimationEnd())
		{
			// 앞으로 이동
			fsm->ChangeState(Name_WALK_FORWARD);
		}
		// 내가 대기 상태가 끝났다면
		else if (Name_STAND == fsm->GetCurStateString() &&
			fsm->GetDM()->IsAnimationEnd())
		{
			// 앞으로 이동
			fsm->ChangeState(Name_WALK_FORWARD);
		}
		//// 내가 이동 중이라면
		//else if (Name_WALK_FORWARD == fsm->GetCurStateString())
		//{
		//	_float3 dir = tPos - mPos;

		//	mPos += *D3DXVec3Normalize(&dir, &dir) * GET_DT;
		//	pOwner->GetTransform()->SetPosition(mPos);
		//}
		// 내가 뒤로 이동 중이라면
		//else if (Name_WALK_BACKWARD == fsm->GetCurStateString() &&
		//	fsm->GetDM()->IsAnimationEnd() &&
		//	false == m_walkReady)
		//{
		//	_float3 dir = tPos - mPos;

		//	mPos -= *D3DXVec3Normalize(&dir, &dir) * GET_DT;
		//	pOwner->GetTransform()->SetPosition(mPos);
		//}
		// 내가 뒤로 이동이 끝났다면
		else if (Name_WALK_BACKWARD == fsm->GetCurStateString() &&
			fsm->GetDM()->IsAnimationEnd() &&
			true == m_walkReady)
		{
			// 앞으로 이동
			fsm->ChangeState(Name_WALK_FORWARD);
			pOwner->GetComponent<CPatternMachineC>()->SetOnSelect(false);
		}
	}
	// 상대가 공격 범위 안이고
	else if (len <= m_atkDis)
	{
		// 내가 이동, 대기 상태가 끝났다면
		if ((Name_WALK_FORWARD == fsm->GetCurStateString() ||
			Name_WALK_BACKWARD == fsm->GetCurStateString() ||
			Name_STAND == fsm->GetCurStateString()) &&
			fsm->GetDM()->IsAnimationEnd())
		{
			// 공격 상태로 변경
			fsm->ChangeState(Name_ATTACK_2);
			PatternPlaySound(L"Lencer_Skill_Attack.wav", pOwner);
		}
		// 공격2 상태가 끝났다면
		else if (Name_ATTACK_2 == fsm->GetCurStateString() &&
			fsm->GetDM()->IsAnimationEnd())
		{
			// 뒤로 이동
			fsm->ChangeState(Name_WALK_BACKWARD);
		}
	}

	/************************* AttackBall */
	// 내가 공격 상태고, 적절할 때 어택볼 숨기기
	if (Name_ATTACK_2 == fsm->GetCurStateString() && 0.57f <= fsm->GetDM()->GetAniTimeline())
	{
		static_cast<CMO_Lancer*>(pOwner)->UnActiveAttackBall();
	}
	// 내가 공격 상태고, 적절할 때 어택볼 생성
	else if (Name_ATTACK_2 == fsm->GetCurStateString() && 0.47f <= fsm->GetDM()->GetAniTimeline())
	{
		m_atkMat = pOwner->GetTransform()->GetWorldMatrix();

		_float3 look = _float3(m_atkMat._31, m_atkMat._32, m_atkMat._33);
		D3DXVec3Normalize(&look, &look);

		m_atkMat._42 += pOwner->GetComponent<Engine::CMeshC>()->GetHalfYOffset();
		m_atkMat._41 += (m_atkDis * look.x / 1.2f);
		m_atkMat._43 += (m_atkDis * look.z / 1.2f);

		static_cast<CMO_Lancer*>(pOwner)->ActiveAttackBall(1.f, HitInfo::Str_High, HitInfo::CC_None, &m_atkMat, 0.42f);
	}
}

SP(CLancerAttack2Pattern) CLancerAttack2Pattern::Create()
{
	SP(CLancerAttack2Pattern) spInstance(new CLancerAttack2Pattern, Engine::SmartDeleter<CLancerAttack2Pattern>);

	return spInstance;
}
