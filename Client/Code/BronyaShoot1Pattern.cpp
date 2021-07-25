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

#include "Bronya_Cannon_Charge.h"
#include "Bronya_Ult_Impact_Smoke.h"

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
	
	if (Name_IDLE == fsm->GetCurStateString() &&
		false == m_onShootReady)
	{
		fsm->GetDM()->GetAniCtrl()->SetSpeed(1.2f);
		m_onChargeEffect = false;
		m_onShootReady = true;
	}
	else if (Name_IDLE == fsm->GetCurStateString() &&
		fsm->GetDM()->IsAnimationEnd())
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
			static_cast<CMonster*>(pOwner)->GetStat()->SetOnPatternShield(true);
			m_onAtkBall = false; 
			m_onSmokeEffect = false;

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
		static_cast<CMonster*>(pOwner)->GetStat()->SetOnPatternShield(false);
		pOwner->GetComponent<CPatternMachineC>()->SetOnSelect(false);
		m_onShootReady = false;

		return;
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

	/************************* Effect */
	// shoot charge
	if (Name_IDLE == fsm->GetCurStateString() &&
		false == m_onChargeEffect)
	{
		m_chargeEffect = Engine::GET_CUR_SCENE->GetObjectFactory()->AddClone(L"Bronya_Cannon_Charge", true);
		m_chargeEffect->GetTransform()->SetSize(0.03f, 0.03f, 0.03f);
		SP(Engine::CObject) spWeapon = static_cast<CMB_Bronya*>(pOwner)->GetWeapon();

		//std::cout << "생성" << std::endl;
		PatternPlaySound(L"Bronya_ChargeShot.wav", pOwner);

		m_onChargeEffect = true;
	}
	else if (nullptr != m_chargeEffect &&
		true == m_onChargeEffect)
	{
		m_pRHand = &fsm->GetDM()->GetFrameByName("Bip002_L_Forearm")->CombinedTransformMatrix;
		GetRHandMat(pOwner, m_pAttackBallMat);

		_float3 dir = { m_pAttackBallMat->_11, m_pAttackBallMat->_12, m_pAttackBallMat->_13 };
		_float3 pos = { m_pAttackBallMat->_41, m_pAttackBallMat->_42, m_pAttackBallMat->_43 };
		
		m_chargeEffect->GetTransform()->SetPosition(pos + dir);
		m_chargeEffect->GetTransform()->SetForward(dir);
	}
	
	if (Name_Shoot_1 == fsm->GetCurStateString() &&
		0.2f <= fsm->GetDM()->GetAniTimeline() &&
		true == m_onChargeEffect &&
		nullptr != m_chargeEffect)
	{
		m_chargeEffect->SetDeleteThis(true);
		m_chargeEffect = nullptr;
		//std::cout << "파괴" << std::endl;
	}

	// smoke effect
	if (Name_Shoot_1 == fsm->GetCurStateString() &&
		0.009f <= fsm->GetDM()->GetAniTimeline() &&
		false == m_onSmokeEffect)
	{
		_float3 pos = { m_pAttackBallMat->_41, m_pAttackBallMat->_42, m_pAttackBallMat->_43 };

		SP(Engine::CObject) smoke = Engine::GET_CUR_SCENE->GetObjectFactory()->AddClone(L"Bronya_Ult_Impact_Smoke", true);
		smoke->GetTransform()->SetPosition(pos);
		smoke->GetTransform()->SetSize(0.1f, 0.1f, 0.1f);
		std::cout << "create" << std::endl;

		m_onSmokeEffect = true;
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
