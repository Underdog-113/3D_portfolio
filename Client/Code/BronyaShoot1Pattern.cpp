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
	for (_int i = 0; i < 15; ++i)
	{
		m_vBulletsAB.emplace_back(new _mat);
	}
}

CBronyaShoot1Pattern::~CBronyaShoot1Pattern()
{
	for (_int i = 0; i < 15; ++i)
	{
		delete m_vBulletsAB[i];
		m_vBulletsAB[i] = nullptr;
	}
}

void CBronyaShoot1Pattern::Pattern(Engine::CObject* pOwner)
{
	_float3 tPos = CStageControlTower::GetInstance()->GetCurrentActor()->GetTransform()->GetPosition(); // target pos
	_float3 mPos = pOwner->GetTransform()->GetPosition(); // monster pos
	_float len = D3DXVec3Length(&(tPos - mPos));
	SP(CFSM_BronyaC) fsm = pOwner->GetComponent<CFSM_BronyaC>();

	CoolTime(m_walkTime, m_walkCool, m_walkReady);

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
		if (Name_IDLE == fsm->GetCurStateString())
		{
			// shoot1 상태로 변경
			fsm->ChangeState(Name_Shoot_1);
			m_onAtkBall = false;
			m_offAtkBall = false;
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
	if (Name_Shoot_1 == fsm->GetCurStateString() &&
		0.15f <= fsm->GetDM()->GetAniTimeline() &&
		false == m_offAtkBall)
	{
		//static_cast<CMB_Bronya*>(pOwner)->UnActiveAttackBall();
		m_offAtkBall = true;
	}
	// 내가 공격 상태고, 적절할 때 어택볼 생성
	else if (Name_Shoot_1 == fsm->GetCurStateString() &&
		0.009f <= fsm->GetDM()->GetAniTimeline() &&
		false == m_onAtkBall)
	{
		m_pRHand = &fsm->GetDM()->GetFrameByName("Bip002_L_Forearm")->CombinedTransformMatrix;

		for (_int i = 0; i < 9; ++i)
		{
			static_cast<CMB_Bronya*>(pOwner)->GetBulletAB()[i]->SetOffset(_float3(0.6f, 0.f, 0.f));
			static_cast<CMB_Bronya*>(pOwner)->ActiveAttackBall(1.f, HitInfo::Str_High, HitInfo::CC_None, m_vBulletsAB[i], 0.12f, static_cast<CMB_Bronya*>(pOwner)->GetBulletAB()[i].get());
			GetRHandMat(pOwner, m_vBulletsAB[i]);
			
			auto& bullet = static_cast<CMB_Bronya*>(pOwner)->GetBullets()[i];

			m_dir = tPos - bullet->GetTransform()->GetPosition();
			D3DXVec3Normalize(&m_dir, &m_dir);

			bullet->SetIsEnabled(true);
			bullet->GetTransform()->SetForward(m_dir);
		}
		
		m_onAtkBall = true;
	}
	// 어택볼 이동
	if (true == m_onAtkBall)
	{
		SetBullet(pOwner, 0, _float3(19.f, -2.f, 0.f), mPos, tPos);
		SetBullet(pOwner, 1, _float3(19.f, -2.5f, 0.3f), mPos, tPos);
		SetBullet(pOwner, 2, _float3(19.f, -3.1f, 0.5f), mPos, tPos);
		SetBullet(pOwner, 3, _float3(19.f, -2.7f, 0.4f), mPos, tPos);
		SetBullet(pOwner, 4, _float3(19.f, -2.6f, 0.5f), mPos, tPos);
		SetBullet(pOwner, 5, _float3(19.f, -3.f, 1.f), mPos, tPos);
		SetBullet(pOwner, 6, _float3(19.f, -3.f, 0.8f), mPos, tPos);
		SetBullet(pOwner, 7, _float3(19.f, -2.3f, -0.3f), mPos, tPos);
		SetBullet(pOwner, 8, _float3(19.f, -3.3f, -0.5f), mPos, tPos);
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

void CBronyaShoot1Pattern::SetBullet(Engine::CObject * pOwner, _int index, _float3 addPos, _float3 mPos, _float3 tPos)
{
	_float3 dir = mPos - tPos;
	D3DXVec3Normalize(&dir, &dir);

	auto& attackball = static_cast<CMB_Bronya*>(pOwner)->GetBulletAB()[index];

	_float3 ball = attackball->GetOffset();
	ball.x += GET_DT * addPos.x;
	ball.y += GET_DT * addPos.y;
	ball.z += GET_DT * addPos.z;

	attackball->SetOffset(ball);
	static_cast<CMB_Bronya*>(pOwner)->GetBullets()[index]->GetTransform()->SetPosition(attackball->GetTransform()->GetPosition());
}
