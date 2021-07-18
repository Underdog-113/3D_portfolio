#include "stdafx.h"
#include "BronyaShoot1Pattern.h"

#include "FSM_BronyaC.h"
#include "FSMDefine_Bronya.h"
#include "MB_Bronya.h"

#include "StateMachineC.h"
#include "Valkyrie.h" 
#include "DynamicMeshData.h"
#include "AniCtrl.h"
#include "PatternMachineC.h"
#include "AttackBall.h"
#include "BronyaBullet.h"

CBronyaShoot1Pattern::CBronyaShoot1Pattern()
{
	m_pAttackBallMat = new _mat;
}

CBronyaShoot1Pattern::~CBronyaShoot1Pattern()
{
	delete m_pAttackBallMat;
	m_pAttackBallMat = nullptr;
}

void CBronyaShoot1Pattern::Pattern(Engine::CObject* pOwner)
{
	_float3 tPos = CStageControlTower::GetInstance()->GetCurrentActor()->GetTransform()->GetPosition(); // target pos
	_float3 mPos = pOwner->GetTransform()->GetPosition(); // monster pos
	_float len = D3DXVec3Length(&(tPos - mPos));
	SP(CFSM_BronyaC) fsm = pOwner->GetComponent<CFSM_BronyaC>();

	static_cast<CMB_Bronya*>(pOwner)->ChaseTarget(tPos);

	CoolTime(m_walkTime, m_walkCool, m_walkReady);

	if (Name_IDLE == fsm->GetCurStateString())
	{
		fsm->GetDM()->GetAniCtrl()->SetSpeed(2.2f);
	}
	else
	{
		fsm->GetDM()->GetAniCtrl()->SetSpeed(1.f);
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
		if ((Name_IDLE == fsm->GetCurStateString() ||
			Name_Run == fsm->GetCurStateString()) &&
			fsm->GetDM()->IsAnimationEnd())
		{
			// shoot1 상태로 변경
			fsm->ChangeState(Name_Shoot_1);
			m_onAtkBall = false;
			return;
		}
	}

	/************************* Shoot1 End */
	// 내가 공격 상태가 끝났다면
	if (Name_Shoot_1 == fsm->GetCurStateString() &&
		fsm->GetDM()->IsAnimationEnd())
	{
		// 대기 상태로 변경
		fsm->ChangeState(Name_IDLE);
		pOwner->GetComponent<CPatternMachineC>()->SetOnSelect(false);
	}

	/************************* AttackBall */
	// 내가 공격 상태고, 적절할 때 어택볼 숨기기
	//if (Name_Shoot_1 == fsm->GetCurStateString() &&
	//	0.75f <= fsm->GetDM()->GetAniTimeline())
	//{
	//}
	// 내가 공격 상태고, 적절할 때 어택볼 생성
	else if (Name_Shoot_1 == fsm->GetCurStateString() &&
		0.009f <= fsm->GetDM()->GetAniTimeline() &&
		false == m_onAtkBall)
	{
		m_pRHand = &fsm->GetDM()->GetFrameByName("Bip002_L_Forearm")->CombinedTransformMatrix;
		GetRHandMat(pOwner, m_pAttackBallMat);

		for (_int i = 0; i < m_bulletCnt; ++i)
		{
			auto& bullet = static_cast<CMB_Bronya*>(pOwner)->GetBullets()[i];

			bullet->GetTransform()->SetPosition(_float3(m_pAttackBallMat->_41, m_pAttackBallMat->_42, m_pAttackBallMat->_43));

			m_dir = tPos- bullet->GetTransform()->GetPosition();
			D3DXVec3Normalize(&m_dir, &m_dir);

			bullet->GetTransform()->SetForward(-m_dir);
			bullet->SetDir(m_dir);
			bullet->SetIsEnabled(true);
		}
		
		m_onAtkBall = true;
	}
}

SP(CBronyaShoot1Pattern) CBronyaShoot1Pattern::Create()
{
	SP(CBronyaShoot1Pattern) spInstance(new CBronyaShoot1Pattern, Engine::SmartDeleter<CBronyaShoot1Pattern>);

	return spInstance;
}

void CBronyaShoot1Pattern::GetRHandMat(Engine::CObject * pOwner, _mat * pAtkBall)
{
	_mat combMat = *m_pRHand;
	_float3 rootMotionPos = pOwner->GetComponent<Engine::CMeshC>()->GetRootMotionPos();
	combMat._41 -= rootMotionPos.x;
	combMat._43 -= rootMotionPos.z;

	*pAtkBall = combMat * pOwner->GetTransform()->GetWorldMatrix();
}
