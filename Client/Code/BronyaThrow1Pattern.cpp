#include "stdafx.h"
#include "BronyaThrow1Pattern.h"

#include "FSM_BronyaC.h"
#include "FSMDefine_Bronya.h"
#include "MB_Bronya.h"

#include "StateMachineC.h"
#include "Valkyrie.h" 
#include "DynamicMeshData.h"
#include "AniCtrl.h"
#include "PatternMachineC.h"
#include "AttackBall.h"

#include "BronyaGrenade.h"

CBronyaThrow1Pattern::CBronyaThrow1Pattern()
{
	m_pAttackBallMat = new _mat;
}

CBronyaThrow1Pattern::~CBronyaThrow1Pattern()
{
	Engine::SafeDelete(m_pAttackBallMat);
}

void CBronyaThrow1Pattern::Pattern(Engine::CObject* pOwner)
{
	_float3 tPos = CStageControlTower::GetInstance()->GetCurrentActor()->GetTransform()->GetPosition(); // target pos
	_float3 mPos = pOwner->GetTransform()->GetPosition(); // monster pos
	_float len = D3DXVec3Length(&(tPos - mPos));
	SP(CFSM_BronyaC) fsm = pOwner->GetComponent<CFSM_BronyaC>();

	CoolTime(m_walkTime, m_walkCool, m_walkReady);

	/************************* Fast Idle */
	if (Name_IDLE == fsm->GetCurStateString())
	{
		if (fsm->GetDM()->IsAnimationEnd())
		{
			fsm->GetDM()->GetAniCtrl()->SetSpeed(1.f);
		}
		else
		{
			fsm->GetDM()->GetAniCtrl()->SetSpeed(1.7f);
		}
	}

	/************************* Range */
	// 상대가 공격 범위 밖이고
	if (len > m_atkDis)
	{
		// 내가 대기 상태가 끝났다면
		if (Name_IDLE == fsm->GetCurStateString() &&
			fsm->GetDM()->IsAnimationEnd())
		{
			// 이동 상태로 변경
			fsm->ChangeState(Name_Run);
		}
	}
	// 상대가 공격 범위 안이고
	else if (len <= m_atkDis)
	{
		// 내가 대기 상태라면
		if (Name_IDLE == fsm->GetCurStateString() ||
			Name_Run == fsm->GetCurStateString())
		{
			// throw1 상태로 변경
			fsm->ChangeState(Name_Throw_1);
			m_onAtkBall = false;

			return;
		}
	}

	/************************* throw1 End */
	// 내가 throw1 상태가 끝났다면
	if (Name_Throw_1 == fsm->GetCurStateString() &&
		fsm->GetDM()->IsAnimationEnd())
	{
		// 대기 상태로 변경
		fsm->ChangeState(Name_IDLE);
		pOwner->GetComponent<CPatternMachineC>()->SetOnSelect(false);

		return;
	}

	/************************* throw grenade */
	if (Name_Throw_1 == fsm->GetCurStateString() &&
		0.47f <= fsm->GetDM()->GetAniTimeline() &&
		false == m_onAtkBall)
	{
		m_pRHand = &fsm->GetDM()->GetFrameByName("Bip002_R_Hand")->CombinedTransformMatrix;
		GetRHandMat(pOwner, m_pAttackBallMat);

		for (_int i = 0; i < m_grenadeCnt; ++i)
		{
			auto& grenade = static_cast<CMB_Bronya*>(pOwner)->GetGrenades()[i];

			grenade->GetTransform()->SetPosition(_float3(m_pAttackBallMat->_41, m_pAttackBallMat->_42, m_pAttackBallMat->_43));

			m_dir = tPos - grenade->GetTransform()->GetPosition();
			
			D3DXVec3Normalize(&m_dir, &m_dir);

			grenade->GetTransform()->SetForward(-m_dir);
			grenade->SetDir(m_dir);
			grenade->SetIsEnabled(true);
		}

		m_onAtkBall = true;
	}

}

SP(CBronyaThrow1Pattern) CBronyaThrow1Pattern::Create()
{
	SP(CBronyaThrow1Pattern) spInstance(new CBronyaThrow1Pattern, Engine::SmartDeleter<CBronyaThrow1Pattern>);

	return spInstance;
}

void CBronyaThrow1Pattern::GetRHandMat(Engine::CObject * pOwner, _mat * pAtkBall)
{
	_mat combMat = *m_pRHand;
	_float3 rootMotionPos = pOwner->GetComponent<Engine::CMeshC>()->GetRootMotionPos();
	combMat._41 -= rootMotionPos.x;
	combMat._43 -= rootMotionPos.z;

	*pAtkBall = combMat * pOwner->GetTransform()->GetWorldMatrix();
}
