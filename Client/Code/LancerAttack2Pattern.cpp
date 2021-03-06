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
	CoolTime(m_walkTime, m_walkCool, m_walkReady);

	/************************* Lerp Move */
	//if (true == m_onLerp && false == pOwner->GetTransform()->GetSlerpOn())
	//{
	//	m_onLerp = false;
	//}
	//else
	//{
	//	_float3 dir = tPos - mPos;
	//	D3DXVec3Normalize(&dir, &dir);

	//	pOwner->GetTransform()->SetGoalForward(dir);
	//}
	//if (Name_WALK_BACKWARD == fsm->GetCurStateString() &&
	//	true == m_onLerp)
	//{
	//	m_onLerp = false;
	//}

	// 내가 공격2 상태가 아니라면 상대를 추적
	if (Name_ATTACK_2 != fsm->GetCurStateString() &&
		false == m_onLerp)
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
			// 뒤로 이동
			fsm->ChangeState(Name_WALK_BACKWARD);
			//m_onLerp = true;

			//_float3 dir = tPos - mPos;
			//D3DXVec3Normalize(&dir, &dir);

			//pOwner->GetTransform()->SetSlerpOn(true);
			//pOwner->GetTransform()->SetGoalForward(dir);
		}
		// 내가 대기 상태가 끝났다면
		else if (Name_STAND == fsm->GetCurStateString() &&
			fsm->GetDM()->IsAnimationEnd())
		{
			// 앞으로 이동
			fsm->ChangeState(Name_WALK_FORWARD);
		}
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
			fsm->GetDM()->IsAnimationEnd() &&
			false == m_onLerp)
		{
			// 공격 상태로 변경
			fsm->ChangeState(Name_ATTACK_2);
			PatternPlaySound(L"Lencer_Skill_Attack.wav", pOwner);

			m_onBladeEffect = false;
			m_onSignEffect = false;
			return;
		}
		// 공격2 상태가 끝났다면
		else if (Name_ATTACK_2 == fsm->GetCurStateString() &&
			fsm->GetDM()->IsAnimationEnd())
		{
			// 뒤로 이동
			fsm->ChangeState(Name_WALK_BACKWARD);
			//m_onLerp = true;
			//
			//_float3 dir = tPos - mPos;
			//D3DXVec3Normalize(&dir, &dir);

			//pOwner->GetTransform()->SetSlerpOn(true);
			//pOwner->GetTransform()->SetGoalForward(dir);
		}
	}

	/************************* AttackBall */
	// 내가 공격 상태고, 적절할 때 어택볼 숨기기
	if (Name_ATTACK_2 == fsm->GetCurStateString() && 
		0.57f <= fsm->GetDM()->GetAniTimeline())
	{
		static_cast<CMO_Lancer*>(pOwner)->UnActiveAttackBall();
	}
	// 내가 공격 상태고, 적절할 때 어택볼 생성
	else if (Name_ATTACK_2 == fsm->GetCurStateString() && 
		0.47f <= fsm->GetDM()->GetAniTimeline())
	{
		m_atkMat = pOwner->GetTransform()->GetWorldMatrix();

		_float3 look = _float3(m_atkMat._31, m_atkMat._32, m_atkMat._33);
		D3DXVec3Normalize(&look, &look);

		m_atkMat._42 += pOwner->GetComponent<Engine::CMeshC>()->GetHalfYOffset();
		m_atkMat._41 += (m_atkDis * look.x / 1.2f);
		m_atkMat._43 += (m_atkDis * look.z / 1.2f);

		static_cast<CMO_Lancer*>(pOwner)->ActiveAttackBall(1.f, HitInfo::Str_Low, HitInfo::CC_None, &m_atkMat, 0.42f);
	}

	/************************* Effect */
	if (Name_ATTACK_2 == fsm->GetCurStateString() &&
		0.1f <= fsm->GetDM()->GetAniTimeline() &&
		false == m_onSignEffect)
	{
		m_spSignEffect = Engine::GET_CUR_SCENE->GetObjectFactory()->AddClone(L"MonsterAttackSign", true);
		m_spSignEffect->GetTransform()->SetPosition(mPos);
		m_spSignEffect->GetTransform()->AddPositionY(1.3f);
		m_spSignEffect->GetTransform()->SetSize(5.f, 3.f, 2.f);
		m_onSignEffect = true;
	}

	if (Name_ATTACK_2 == fsm->GetCurStateString() &&
		0.45f <= fsm->GetDM()->GetAniTimeline() &&
		0.55f > fsm->GetDM()->GetAniTimeline() &&
		false == m_onBladeEffect)
	{
		m_onBladeEffect = true;
		m_spBladeEffect = Engine::GET_CUR_SCENE->GetObjectFactory()->AddClone(L"Lancer_OutSideEff", true);
		m_spBladeEffect->GetTransform()->AddRotationY(D3DXToRadian(180));
		m_spBladeEffect->GetTransform()->SetSize(0.5f, 0.5f, 0.8f);
	}
	else if (true == m_onBladeEffect)
	{
		m_pRHand = &fsm->GetDM()->GetFrameByName("Bip001_R_Hand_1")->CombinedTransformMatrix;
		_mat matHand = GetRHandMat(pOwner);

		_float3 newForward = matHand.m[1];
		_float3 rotAxis = matHand.m[2];
		_mat extraRot;
		D3DXMatrixRotationAxis(&extraRot, &rotAxis, -PI / 180 * 25);
		D3DXVec3TransformNormal(&newForward, &newForward, &extraRot);

		m_spBladeEffect->GetTransform()->SetForwardUp(newForward, matHand.m[2]);
		m_spBladeEffect->GetTransform()->SetPosition(matHand.m[3]);
	}
}

SP(CLancerAttack2Pattern) CLancerAttack2Pattern::Create()
{
	SP(CLancerAttack2Pattern) spInstance(new CLancerAttack2Pattern, Engine::SmartDeleter<CLancerAttack2Pattern>);

	return spInstance;
}

_mat CLancerAttack2Pattern::GetRHandMat(Engine::CObject * pOwner)
{
	_mat combMat = *m_pRHand;
	_float3 rootMotionPos = pOwner->GetComponent<Engine::CMeshC>()->GetRootMotionPos();
	combMat._41 -= rootMotionPos.x;
	combMat._43 -= rootMotionPos.z;

	_mat realPosMat = combMat * pOwner->GetTransform()->GetWorldMatrix();

	return realPosMat;
}
