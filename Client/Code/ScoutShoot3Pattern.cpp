#include "stdafx.h"
#include "ScoutShoot3Pattern.h"

#include "FSM_ScoutC.h"
#include "FSMDefine_Scout.h"
#include "MO_Scout.h"

#include "StateMachineC.h"
#include "Valkyrie.h" 
#include "DynamicMeshData.h"
#include "AniCtrl.h"
#include "PatternMachineC.h"
#include "AttackBall.h"
#include "StageControlTower.h"
#include "ScoutBall.h"
#include "ScoutCircleRange.h"

CScoutShoot3Pattern::CScoutShoot3Pattern()
{
}

CScoutShoot3Pattern::~CScoutShoot3Pattern()
{
}

void CScoutShoot3Pattern::Pattern(Engine::CObject* pOwner)
{
	_float3 tPos = CStageControlTower::GetInstance()->GetCurrentActor()->GetTransform()->GetPosition(); // target pos
	_float3 mPos = pOwner->GetTransform()->GetPosition(); // monster pos
	_float len = D3DXVec3Length(&(tPos - mPos));
	SP(CFSM_ScoutC) fsm = pOwner->GetComponent<CFSM_ScoutC>();

	if (false == m_oneTime)
	{
		m_oneTime = true;
	}

	CoolTime(m_atkTime, m_atkCool, m_atkReady);
	CoolTime(m_walkTime, m_walkCool, m_walkReady);

	/************************* Fast Idle */
	if (Name_IDLE == fsm->GetCurStateString() &&
		false == m_onFastIdle)
	{
		fsm->GetDM()->GetAniCtrl()->SetSpeed(2.f);
		m_onFastIdle = true;
	}
	else if (Name_IDLE != fsm->GetCurStateString() &&
		true == m_onFastIdle)
	{
		fsm->GetDM()->GetAniCtrl()->SetSpeed(1.f);
		m_onFastIdle = false;
	}

	// 내가 shoot3 상태가 아니면 상대를 추적
	if (Name_SHOOT_3 != fsm->GetCurStateString())
	{
		static_cast<CMO_Scout*>(pOwner)->ChaseTarget(tPos);
	}

	/************************* Sound */
	// shoot3 sound
	if (Name_SHOOT_3 == fsm->GetCurStateString() &&
		0.8f <= fsm->GetDM()->GetAniTimeline() &&
		true == m_onSound)
	{
		//PatternPlaySound(L"Scout_UpAttack_2.wav", pOwner);
		//EChannelID id = static_cast<CMonster*>(pOwner)->GetChannelID();
		//std::dynamic_pointer_cast<CScoutBall>(m_spCircleRange)->SetChannelID(id);
		m_onSound = false;
	}
	else if (Name_SHOOT_3 == fsm->GetCurStateString() &&
		0.0f <= fsm->GetDM()->GetAniTimeline() &&
		0.4f > fsm->GetDM()->GetAniTimeline() &&
		false == m_onSound)
	{
		PatternPlaySound(L"Scout_UpAttack.wav", pOwner);
		m_onSound = true;
	}

	/************************* Range */
	// 상대가 shoot3 범위 밖이고
	if (len > m_atkDis)
	{
		// 내가 shoot3 상태면
		if (Name_SHOOT_3 == fsm->GetCurStateString() && fsm->GetDM()->IsAnimationEnd())
		{
			fsm->ChangeState(Name_IDLE);
			m_onEffect = false;
		}
		// 내가 대기 상태면 이동 애니로 변경
		else if (Name_IDLE == fsm->GetCurStateString() && fsm->GetDM()->IsAnimationEnd())
		{
			fsm->ChangeState(Name_RUN_F);
			SetMoveSound();
		}
		// 내가 이동 중이라면
		else if (Name_RUN_F == fsm->GetCurStateString())
		{
			_float3 dir = tPos - mPos;

			mPos += *D3DXVec3Normalize(&dir, &dir) * GET_DT;
			pOwner->GetTransform()->SetPosition(mPos);
			PatternRepeatSound(m_curMoveSound, pOwner, 0.6f);
		}
	}
	// 상대가 shoot3 범위 안이고
	else if (len <= m_atkDis)
	{
		// 내가 이동, 대기 상태라면 shoot3
		if ((Name_IDLE == fsm->GetCurStateString() ||
			Name_RUN_F == fsm->GetCurStateString()) &&
			fsm->GetDM()->IsAnimationEnd())

		{
			fsm->ChangeState(Name_SHOOT_3);

			m_spLeftScoutBall = Engine::GET_CUR_SCENE->GetObjectFactory()->AddClone(L"ScoutBall", true, (_int)Engine::ELayerID::Effect, L"MeshEffect");
			m_spRightScoutBall = Engine::GET_CUR_SCENE->GetObjectFactory()->AddClone(L"ScoutBall", true, (_int)Engine::ELayerID::Effect, L"MeshEffect");
			m_spCircleRange = Engine::GET_CUR_SCENE->GetObjectFactory()->AddClone(L"ScoutCircleRange", true);

			std::dynamic_pointer_cast<CScoutBall>(m_spLeftScoutBall)->SetFlyingBall(true);
			std::dynamic_pointer_cast<CScoutBall>(m_spRightScoutBall)->SetFlyingBall(true);
			std::dynamic_pointer_cast<CScoutCircleRange>(m_spCircleRange)->SetBallShooter(pOwner);
			
			m_spCircleRange->GetTransform()->SetPosition(tPos);
			m_targetMat = CStageControlTower::GetInstance()->GetCurrentActor()->GetTransform()->GetWorldMatrix();
		}
	}

	/************************* Run_B */
 	// 내가 shoot3 상태라면 뒤로 이동
	if (Name_SHOOT_3 == fsm->GetCurStateString() && fsm->GetDM()->IsAnimationEnd())
	{
		fsm->ChangeState(Name_RUN_B);
		SetMoveSound();
		m_walkReady = false;
		m_onSound = false;
		m_onShoot = false;
		m_onEffect = false;
	}
	// 내가 뒤로 이동 중이라면
	else if (Name_RUN_B == fsm->GetCurStateString() && 0.9f <= fsm->GetDM()->GetAniTimeline() && false == m_walkReady)
	{
		_float3 dir = tPos - mPos;

		mPos -= *D3DXVec3Normalize(&dir, &dir) * GET_DT;
		pOwner->GetTransform()->SetPosition(mPos);
		PatternRepeatSound(m_curMoveSound, pOwner, 0.3f);
	}
	// 내가 뒤로 이동이 끝났다면
	else if (Name_RUN_B == fsm->GetCurStateString() && 0.9f <= fsm->GetDM()->GetAniTimeline() && true == m_walkReady)
	{
		m_walkReady = false;
		fsm->ChangeState(Name_IDLE);
		PatternStopSound(pOwner);
		pOwner->GetComponent<CPatternMachineC>()->SetOnSelect(false);
	}

	/************************* AttackBall */
	// shoot3 상태가 완료되면 attackball off
	if (Name_SHOOT_3 == fsm->GetCurStateString() && 
		0.8f <= fsm->GetDM()->GetAniTimeline() &&
		true == m_onShoot)
	{
		m_onShoot = false;
		//static_cast<CMO_Scout*>(pOwner)->UnActiveAttackBall();
	}
	// shoot3 상태라면 포격 위치를 잡음
	else if (Name_SHOOT_3 == fsm->GetCurStateString() &&
		0.3f <= fsm->GetDM()->GetAniTimeline() &&
		0.4f > fsm->GetDM()->GetAniTimeline() &&
		false == m_firePosFix)
	{
		//_float3 pPos = CStageControlTower::GetInstance()->GetCurrentActor()->GetTransform()->GetPosition();
		//m_atkMat = pOwner->GetTransform()->GetWorldMatrix();
		//m_atkMat._41 = pPos.x;
		m_targetMat._42 += 0.3f;
		//m_atkMat._43 = pPos.z;
		m_firePosFix = true;

		std::dynamic_pointer_cast<CScoutCircleRange>(m_spCircleRange)->SetAtkMat(m_targetMat);
	}
	// shoot3 상태라면 어택볼 생성
	else if (Name_SHOOT_3 == fsm->GetCurStateString() &&
		0.7f <= fsm->GetDM()->GetAniTimeline() &&
		0.75f > fsm->GetDM()->GetAniTimeline() &&
		false == m_onShoot)
	{
		m_onShoot = true;
		m_firePosFix = false;
		//static_cast<CMO_Scout*>(pOwner)->ActiveAttackBall(1.f, HitInfo::Str_Low, HitInfo::CC_None, &m_atkMat, 0.48f);
	}

	/************************* Ball Effect */
	if (Name_SHOOT_3 == fsm->GetCurStateString() &&
		0.45f <= fsm->GetDM()->GetAniTimeline() &&
		false == m_onEffect)
	{
		m_atkMat = pOwner->GetTransform()->GetWorldMatrix();

		_float3 look = _float3(m_atkMat._31, m_atkMat._32, m_atkMat._33);
		D3DXVec3Normalize(&look, &look);

		m_atkMat._42 += pOwner->GetComponent<Engine::CMeshC>()->GetHalfYOffset() + 0.5f;
		m_atkMat._41 += (look.x / 2.4f);
		m_atkMat._43 += (look.z / 2.4f);

		_float3 a = { m_atkMat._41, m_atkMat._42, m_atkMat._43 };
		_float3 b = { m_atkMat._41, m_atkMat._42, m_atkMat._43 };

		_float3 right = { m_atkMat._11, m_atkMat._12, m_atkMat._13 };

		a -= right / 1.71f;
		b += right / 1.71f;

		m_spLeftScoutBall->GetTransform()->SetRotation(pOwner->GetTransform()->GetRotation());
		m_spLeftScoutBall->GetTransform()->AddRotationY(PI);
		m_spLeftScoutBall->GetTransform()->SetPosition(a);

		m_spRightScoutBall->GetTransform()->SetRotation(pOwner->GetTransform()->GetRotation());
		m_spRightScoutBall->GetTransform()->AddRotationY(PI);
		m_spRightScoutBall->GetTransform()->SetPosition(b);

		m_onEffect = true;
	}
}

SP(CScoutShoot3Pattern) CScoutShoot3Pattern::Create()
{
	SP(CScoutShoot3Pattern) spInstance(new CScoutShoot3Pattern, Engine::SmartDeleter<CScoutShoot3Pattern>);

	return spInstance;
}

void CScoutShoot3Pattern::SetMoveSound()
{
	/************************* Choose Move Sound */
	_int index = GetRandRange(0, 2);

	switch (index)
	{
	case 0:
		m_curMoveSound = L"Scout_Move_0.wav";
		break;
	case 1:
		m_curMoveSound = L"Scout_Move_1.wav";
		break;
	case 2:
		m_curMoveSound = L"Scout_Move_2.wav";
		break;
	}
}
