#include "stdafx.h"
#include "ScoutShoot2Pattern.h"

#include "FSM_ScoutC.h"
#include "FSMDefine_Scout.h"
#include "MO_Scout.h"

#include "StateMachineC.h"
#include "Valkyrie.h" 
#include "DynamicMeshData.h"
#include "AniCtrl.h"
#include "PatternMachineC.h"
#include "AttackBox.h"
#include "StageControlTower.h"
#include "Scout_Att_Range.h"

CScoutShoot2Pattern::CScoutShoot2Pattern()
{
}

CScoutShoot2Pattern::~CScoutShoot2Pattern()
{
}

void CScoutShoot2Pattern::Pattern(Engine::CObject* pOwner)
{
	_float3 tPos = CStageControlTower::GetInstance()->GetCurrentActor()->GetTransform()->GetPosition(); // target pos
	_float3 mPos = pOwner->GetTransform()->GetPosition(); // monster pos
	_float len = D3DXVec3Length(&(tPos - mPos));
	SP(CFSM_ScoutC) fsm = pOwner->GetComponent<CFSM_ScoutC>();

	//CoolTime(m_atkTime, m_atkCool, m_atkReady);
	//CoolTime(m_walkTime, m_walkCool, m_walkReady);

	// 내가 상대를 추적
	if (true == m_onChase)
	{
		static_cast<CMO_Scout*>(pOwner)->ChaseTarget(tPos);
	}

	/************************* Sound */
	// run start sound
	if ((Name_RUN_F == fsm->GetCurStateString() ||
		 Name_RUN_B == fsm->GetCurStateString()) &&
		 true == m_onWalk)
	{
		PatternRepeatSound(m_curMoveSound, pOwner, 0.6f);
	}
	else if ((Name_RUN_F == fsm->GetCurStateString() ||
			  Name_RUN_B == fsm->GetCurStateString()) &&
			  false == m_onWalk)
	{
		PatternStopSound(pOwner);
	}

	/************************* Range */
	// 상대가 shoot2 범위 밖이고
	if (len > m_atkDis)
	{
		// 내가 shoot2 상태가 끝났다면
		if (Name_SHOOT_2 == fsm->GetCurStateString() &&
			fsm->GetDM()->IsAnimationEnd())
		{
			fsm->ChangeState(Name_RUN_B);
			m_onChase = true;
			m_onEffect = false;
		}
		// 내가 대기 상태가 끝났다면
		else if (Name_IDLE == fsm->GetCurStateString() &&
			fsm->GetDM()->IsAnimationEnd())
		{
			fsm->ChangeState(Name_RUN_F);
			SetMoveSound();
		}
		// 내가 이동 상태라면
		else if (Name_RUN_F == fsm->GetCurStateString())
		{
			_float3 dir = tPos - mPos;

			mPos += *D3DXVec3Normalize(&dir, &dir) * GET_DT;
			pOwner->GetTransform()->SetPosition(mPos);
			m_onWalk = true;
		}
		// 내가 뒤로 이동 상태라면
		else if (Name_RUN_B == fsm->GetCurStateString() &&
			fsm->GetDM()->IsAnimationEnd() &&
			false == m_walkReady)
		{
			_float3 dir = tPos - mPos;

			mPos -= *D3DXVec3Normalize(&dir, &dir) * GET_DT;
			pOwner->GetTransform()->SetPosition(mPos);
			m_onWalk = true;
		}
		// 내가 뒤로 이동이 끝났다면
		else if (Name_RUN_B == fsm->GetCurStateString() &&
			fsm->GetDM()->IsAnimationEnd() &&
			true == m_walkReady)
		{
			fsm->ChangeState(Name_IDLE);
			pOwner->GetComponent<CPatternMachineC>()->SetOnSelect(false);
			m_onWalk = false;
		}
	}
	// 상대가 shoot2 범위 안이고
	else if (len <= m_atkDis)
	{
		// 내가 이동, 대기 상태가 끝났다면
		if ((Name_RUN_F == fsm->GetCurStateString() ||
			Name_IDLE == fsm->GetCurStateString() ||
			Name_RUN_B == fsm->GetCurStateString()) &&
			fsm->GetDM()->IsAnimationEnd())
		{
			fsm->ChangeState(Name_SHOOT_2);
			m_onChase = false;
			m_onWalk = false;
			PatternPlaySound(L"Scout_Laser.wav", pOwner);

			// shoot2 위치 잡기
			CMO_Scout* pScout = static_cast<CMO_Scout*>(pOwner);
			_float3 mPos = pOwner->GetTransform()->GetPosition();
			_float3 pPos = CStageControlTower::GetInstance()->GetCurrentActor()->GetTransform()->GetPosition();
			_float3 beamDir = pPos - mPos;
			beamDir.y = 0.f;

			D3DXVec3Normalize(&beamDir, &beamDir);
			pScout->GetAttackBox()->GetTransform()->SetPosition(mPos + beamDir * 5);
			pScout->GetAttackBox()->GetTransform()->SetRotation(pScout->GetTransform()->GetRotation());
		}
		// shoot2 상태라면 뒤로 이동 상태로 변경
		else if (Name_SHOOT_2 == fsm->GetCurStateString() && fsm->GetDM()->IsAnimationEnd())
		{
			fsm->ChangeState(Name_RUN_B);
			SetMoveSound();
			m_onChase = true;
			m_onWalk = true;
			m_onEffect = false;
		}
	}

 	/************************* AttackBox */
	// shoot2 상태가 완료되면 attackbox off
	if (Name_SHOOT_2 == fsm->GetCurStateString() && 
		0.7f <= fsm->GetDM()->GetAniTimeline())
	{
		m_onShoot2 = false;
		static_cast<CMO_Scout*>(pOwner)->UnActiveAttackBox();
	}
	// shoot2 상태라면
	else if (Name_SHOOT_2 == fsm->GetCurStateString() &&
		0.65f <= fsm->GetDM()->GetAniTimeline() &&
		0.7f > fsm->GetDM()->GetAniTimeline() &&
		false == m_onShoot2)
	{
		m_onShoot2 = true;
		m_atkMat = pOwner->GetTransform()->GetWorldMatrix();
		CMO_Scout* pScout = static_cast<CMO_Scout*>(pOwner);
		_float3 size = { 0.5f, 1.f, 10.f };
		_float3 offset = ZERO_VECTOR;

		pScout->ActiveAttackBox(1.f, HitInfo::Str_High, HitInfo::CC_None, &m_atkMat, size, offset, ZERO_VECTOR);
	}

	/************************* Effect */
	if (Name_SHOOT_2 == fsm->GetCurStateString() &&
		0.09f <= fsm->GetDM()->GetAniTimeline() &&
		false == m_onEffect)
	{
		// 공격 범위 이펙트
		SP(CScout_Att_Range) spScoutRange = std::dynamic_pointer_cast<CScout_Att_Range>(Engine::GET_CUR_SCENE->GetObjectFactory()->AddClone(L"Scout_Att_Range", true, (_int)Engine::ELayerID::Effect, L"MeshEffect"));
		spScoutRange->GetComponent<Engine::CMeshC>()->SetMeshData(L"Scout_Att_Range_Move");
		spScoutRange->GetComponent<Engine::CGraphicsC>()->SetRenderID((_int)Engine::ERenderID::AlphaBlend);
		spScoutRange->GetComponent<Engine::CTextureC>()->AddTexture(L"Sign");
		spScoutRange->GetComponent<Engine::CTextureC>()->AddTexture(L"Sign");
		spScoutRange->GetComponent<Engine::CTextureC>()->AddTexture(L"Sign");
		spScoutRange->GetComponent<Engine::CShaderC>()->AddShader((_int)EShaderID::AlphaMaskShader);
		spScoutRange->GetTransform()->SetRotation(pOwner->GetTransform()->GetRotation());
		spScoutRange->GetTransform()->AddRotationY(PI);
		spScoutRange->GetTransform()->SetPosition(mPos);

		// ball 이펙트
		_mat atkMat = pOwner->GetTransform()->GetWorldMatrix();

		_float3 look = _float3(atkMat._31, atkMat._32, atkMat._33);
		D3DXVec3Normalize(&look, &look);

		atkMat._42 += pOwner->GetComponent<Engine::CMeshC>()->GetHalfYOffset();
		atkMat._41 += (look.x / 2.2f);
		atkMat._43 += (look.z / 2.2f);

		SP(Engine::CObject) spMeshEffect = Engine::GET_CUR_SCENE->GetObjectFactory()->AddClone(L"ScoutBall", true, (_int)Engine::ELayerID::Effect, L"MeshEffect");
		spMeshEffect->GetComponent<Engine::CMeshC>()->SetMeshData(L"Scout_Ball");
		spMeshEffect->GetComponent<Engine::CGraphicsC>()->SetRenderID((_int)Engine::ERenderID::AlphaBlend);
		spMeshEffect->GetComponent<Engine::CTextureC>()->AddTexture(L"BallColor");
		spMeshEffect->GetComponent<Engine::CTextureC>()->AddTexture(L"BallColor");
		spMeshEffect->GetComponent<Engine::CShaderC>()->AddShader((_int)EShaderID::AlphaMaskShader);
		spMeshEffect->GetTransform()->SetRotation(pOwner->GetTransform()->GetRotation());
		spMeshEffect->GetTransform()->AddRotationY(PI);
		spMeshEffect->GetTransform()->SetPosition(_float3(atkMat._41, atkMat._42, atkMat._43));

		m_onEffect = true;
	}
}

SP(CScoutShoot2Pattern) CScoutShoot2Pattern::Create()
{
	SP(CScoutShoot2Pattern) spInstance(new CScoutShoot2Pattern, Engine::SmartDeleter<CScoutShoot2Pattern>);

	return spInstance;
}

void CScoutShoot2Pattern::DeleteEffects()
{
}

void CScoutShoot2Pattern::SetMoveSound()
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
