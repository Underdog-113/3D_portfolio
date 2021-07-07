#include "stdafx.h"
#include "StageCameraMan.h"
#include "StageControlTower.h"
#include "ObjectFactory.h"
#include "EmptyObject.h"
#include "Valkyrie.h"
#include "CameraShake.h"

#include "WndApp.h"

CStageCameraMan::CStageCameraMan()
{
}


CStageCameraMan::~CStageCameraMan()
{
	delete m_pCameraShake;
}

void CStageCameraMan::Start()
{
	m_spCamera->SetTargetDist(MidTake);
	m_spCamera->SetMaxDistTPS(MidTake);
	m_spCamera->SetMode(Engine::ECameraMode::TPS_Custom);
	m_spCamera->SetLookAngleRight(MidAngle);


	m_spPivot = Engine::GET_CUR_SCENE->ADD_CLONE(L"EmptyObject", true, (_uint)Engine::ELayerID::Camera, L"CameraPivot");
	m_spPivot->AddComponent<Engine::CCollisionC>()->
		AddCollider(Engine::CAabbCollider::Create((_int)ECollisionID::FloorRay, _float3(0.25f, 0.25f, 0.25f)));
	m_spPivot->AddComponent<Engine::CDebugC>();
	m_spPivot->AddComponent<Engine::CShaderC>();
	m_spPivot->GetComponent<Engine::CTransformC>()->SetPosition(CStageControlTower::GetInstance()->GetCurrentActor()->GetTransform()->GetPosition());

	m_spCamera->SetTarget(m_spPivot);

	m_isStart = true;

	m_pCameraShake = new CCameraShake;
	m_pCameraShake->SetCamera(m_spCamera);
	
}

void CStageCameraMan::UpdateCameraMan()
{
	if(!m_isStart)
		Start();

	if (m_spCamera->GetMode() != Engine::ECameraMode::TPS_Custom)
		return;

	if (m_isSwitching)
		return;

	auto camTr = m_spCamera->GetTransform();

	if (m_pCameraShake->IsShaking()) 
	{
		camTr->AddPosition(-m_pCameraShake->GetLocationOscilation());
		camTr->SetPosition(m_noShakeRot);
	}

	PivotChasing();
	
	if (!MouseControlMode())
	{
		ManualControlMode();

		if (!m_manualControl)
			AutoControlMode();
	}


	if (m_pCameraShake->IsShaking())
	{
		m_pCameraShake->PlayShake();

		m_noShakePos = m_spCamera->GetShakePosOffset();
		m_noShakeRot = camTr->GetRotation();	// 회전값 기억
		
		m_spCamera->SetShakePosOffset(m_pCameraShake->GetLocationOscilation());

		_float3 rotOscilation = m_pCameraShake->GetRotateOscilation();
		camTr->AddRotation(rotOscilation);

		m_spCamera->SetLookAngleRight(m_spCamera->GetLookAngleRight() + rotOscilation.x);
		m_spCamera->SetLookAngleUp(m_spCamera->GetLookAngleUp() + rotOscilation.y);
		// 이거 하고 나서 카메라 트랜스폼 업데이트 해야함
	}
	else
	{
		m_spCamera->SetShakePosOffset(ZERO_VECTOR);
	}
}

void CStageCameraMan::PivotChasing()
{
	if (m_speedIncreaseTimer < 1.f)
	{
		m_chaseSpeedIncreaseTimer += GET_PLAYER_DT;
	}

	CStageControlTower* pCT = CStageControlTower::GetInstance();

	AppendTargetCorrecting();

	_float3 lerpPosition = GetLerpPosition(
		m_spPivot->GetTransform()->GetPosition(), m_dstPivotPos, GET_PLAYER_DT * m_chaseSpeed);


	if (D3DXVec3Length(&(m_dstPivotPos - lerpPosition)) < 0.01f)
	{
		lerpPosition = m_dstPivotPos;
		m_chaseSpeedIncreaseTimer = 0.f;
	}
	m_spPivot->GetTransform()->SetPosition(lerpPosition);
}

void CStageCameraMan::SetIsTargeting(bool value)
{
	m_isTargeting = value;
	m_targetingTimer = 0.f;
}

void CStageCameraMan::SetNearTake()
{
	if (m_curTakeType == Near)
		return;

	m_curTakeType = Change;
	m_nextTakeType = Near;
	m_dstMaxDist = NearTake;
	m_changeTakeTimer = 0.f;
	m_changeTakeSpeed = 0.5f;
	m_rotateXStart = m_spCamera->GetLookAngleRight();
	m_rotateXDst = NearAngle;
}

void CStageCameraMan::SetMidTake()
{
	if (m_curTakeType == Mid)
		return;

	if (m_curTakeType == Change && m_nextTakeType == Far)
		return;

	m_curTakeType = Change;
	m_nextTakeType = Mid;
	m_dstMaxDist = MidTake;
	m_changeTakeTimer = 0.f;
	m_changeTakeSpeed = 2.f;
	m_rotateXStart = m_spCamera->GetLookAngleRight();
	m_rotateXDst = MidAngle;
}

void CStageCameraMan::SetFarTake()
{
	if (m_curTakeType == Change && m_nextTakeType == Far)
		return;

	m_curTakeType = Change;
	m_nextTakeType = Far;
	m_dstMaxDist = FarTake;
	m_changeTakeTimer = 0.f;
	m_changeTakeSpeed = 2.f;
	m_rotateXDst = FarAngle;
}

void CStageCameraMan::ChangeTake()
{
	switch (m_curTakeType)
	{
	case CStageCameraMan::Near:
		if (!CheckNoAction())
		{
			SetMidTake();
			return;
		}
		break;
	case CStageCameraMan::Mid:
		if (CheckNoAction())
		{
			m_gotoNextTakeTimer += GET_PLAYER_DT;
			if (m_gotoNextTakeTimer > 3.f)
			{
				m_gotoNextTakeTimer = 0.f;
				SetNearTake();
			}
		}
		else
		{
			m_gotoNextTakeTimer = 0.f;
		}
		break;
	case CStageCameraMan::Far:
		if (CheckNoAction())
		{
			m_gotoNextTakeTimer += GET_PLAYER_DT;
			if (m_gotoNextTakeTimer > 1.5f)
			{
				m_gotoNextTakeTimer = 0.f;
				SetMidTake();
			}
		}
		break;
	case CStageCameraMan::Change:
		if (m_nextTakeType == Near && !CheckNoAction())
		{
			m_nextTakeType = Mid;
			m_curMaxDist = m_spCamera->GetMaxDistTPS();
			m_dstMaxDist = MidTake;
			m_changeTakeTimer = 0.f;
			m_changeTakeSpeed = 2.f;

			m_rotateXStart = m_spCamera->GetLookAngleRight();
			m_rotateXDst = MidAngle;
		}

		m_changeTakeTimer += GET_PLAYER_DT * m_changeTakeSpeed;
		if (m_changeTakeTimer > 1.f)
		{
			m_curMaxDist = m_dstMaxDist;
			m_curTakeType = m_nextTakeType;
			m_spCamera->SetTargetDist(m_dstMaxDist);
			m_spCamera->SetMaxDistTPS(m_dstMaxDist);
			return;
		}

		float inverseRate = 1.f - m_changeTakeTimer;
		float sLerpTimer = 1.f - inverseRate * inverseRate;

		_float lerpPoint = FloatLerp(m_curMaxDist, m_dstMaxDist, sLerpTimer);
		m_spCamera->SetTargetDist(lerpPoint);
		m_spCamera->SetMaxDistTPS(lerpPoint);

		lerpPoint = FloatLerp(m_rotateXStart, m_rotateXDst, sLerpTimer);
		m_spCamera->SetLookAngleRight(lerpPoint);
		break;
	}
}

void CStageCameraMan::AppendTargetCorrecting()
{
	auto pCT = CStageControlTower::GetInstance();

	if (!m_isTargeting)
	{
		_float3 actorPos = pCT->GetCurrentActor()->GetTransform()->GetPosition();
		_float3 pivotPos = m_spPivot->GetTransform()->GetPosition();
		if (actorPos == pivotPos)
			return;

		_float3 dir = actorPos - pivotPos;
		_float len = D3DXVec3Length(&dir);

		D3DXVec3Normalize(&dir, &dir);
		if (len > MaxChaseDistance)
			m_dstPivotPos = pivotPos + dir * MaxChaseDistance;
		else
			m_dstPivotPos = pCT->GetCurrentActor()->GetTransform()->GetPosition();
		return;
	}

	m_targetingTimer += GET_PLAYER_DT;

	if (m_targetingTimer > 2.f || !pCT->GetCurrentTarget())
	{
		m_isTargeting = false;
		m_targetingTimer = 0.f;
		return;
	}


	_float3 actorPos = pCT->GetCurrentActor()->GetTransform()->GetPosition();
	_float3 targetPos = pCT->GetCurrentTarget()->GetTransform()->GetPosition();

	_float3 dir = targetPos - actorPos;
	_float distance = D3DXVec3Length(&dir) * 0.5f;
	
	D3DXVec3Normalize(&dir, &dir);
	m_dstPivotPos = actorPos + dir * distance;
}

void CStageCameraMan::AppendHorizontalCorrecting()
{
	bool isCorrecting = false;

	if (Engine::IMKEY_PRESS(StageKey_Move_Left))
	{
		m_rotateYDst -= (PI / 4) * GET_PLAYER_DT;
		isCorrecting = true;
	}

	if (Engine::IMKEY_PRESS(StageKey_Move_Right))
	{
		m_rotateYDst += (PI / 4) * GET_PLAYER_DT;
		isCorrecting = true;
	}

	if (isCorrecting &&  m_speedIncreaseTimer < 1.f)
	{
		m_speedIncreaseTimer += GET_PLAYER_DT;
	}

	_float lerpPoint = FloatLerp(m_rotateLerpStart, m_rotateYDst, GET_PLAYER_DT * m_horzCorrectingSpeed * m_speedIncreaseTimer);
	m_spCamera->SetLookAngleUp(lerpPoint);
	m_rotateLerpStart = lerpPoint;

	if (abs(m_rotateYDst - m_rotateLerpStart) < 0.01f)
	{
		m_rotateYDst = m_rotateLerpStart;
		m_speedIncreaseTimer = 0.f;
	}
}


bool CStageCameraMan::MouseControlMode()
{
	if (Engine::IMKEY_PRESS(MOUSE_RIGHT))
	{
		m_spCamera->SetRightClicked(true);
		m_rotateLerpStart = m_spCamera->GetLookAngleUp();
		m_rotateYDst = m_spCamera->GetLookAngleUp();

		ChangeTake();
		m_isTargeting = false;
		return true;
	}
	else
	{
		m_spCamera->SetRightClicked(false);
		return false;
	}
}

void CStageCameraMan::ManualControlMode()
{
	ShowMouseCursor();

	m_manualControl = false;


	if (Engine::IMKEY_PRESS(StageKey_CamRotateLeft))
	{
		//m_spCamera->SetLookAngleUp();
		m_rotateYDst -= m_rotateSpeed;
		m_enterAutoTimer = 0.f;

		m_rotateLerpTimer = 0.5f;
		m_rotateLerpStart = m_spCamera->GetLookAngleUp();
		m_manualControl = true;
		m_isTargeting = false;
	}
	if (Engine::IMKEY_PRESS(StageKey_CamRotateRight))
	{
		m_rotateYDst += m_rotateSpeed;
		m_enterAutoTimer = 0.f;


		m_rotateLerpTimer = 0.5f;
		m_rotateLerpStart = m_spCamera->GetLookAngleUp();
		m_manualControl = true;
		m_isTargeting = false;
	}

	m_rotateLerpTimer += GET_PLAYER_DT;
	if (m_rotateLerpTimer > 1.f)
	{
		m_spCamera->SetLookAngleUp(m_rotateYDst);
		return;
	}

	float inverseRate = 1.f - m_rotateLerpTimer;
	float sLerpTimer = 1.f - inverseRate * inverseRate;

	_float lerpPoint = FloatLerp(m_rotateLerpStart, m_rotateYDst, sLerpTimer);
	m_spCamera->SetLookAngleUp(lerpPoint);
}

void CStageCameraMan::AutoControlMode()
{
	HideMouseCursor();

	if (m_enterAutoTimer < 1.f)
	{
		m_enterAutoTimer += GET_PLAYER_DT;
		m_speedIncreaseTimer = 0.f;
		return;
	}

	AppendHorizontalCorrecting();


	ChangeTake();
	
}

void CStageCameraMan::ShakeCamera_Low(_float3 eventPos)
{
	m_pCameraShake->Preset_LowAttack(eventPos);
}


bool CStageCameraMan::CheckNoAction()
{
	if (!Engine::IMKEY_PRESS(StageKey_Move_Forward) &&
		!Engine::IMKEY_PRESS(StageKey_Move_Left) &&
		!Engine::IMKEY_PRESS(StageKey_Move_Right) &&
		!Engine::IMKEY_PRESS(StageKey_Move_Back) &&
		!Engine::IMKEY_PRESS(StageKey_Attack) &&
		!Engine::IMKEY_PRESS(StageKey_Evade) &&
		!Engine::IMKEY_PRESS(StageKey_WeaponSkill) &&
		!Engine::IMKEY_PRESS(StageKey_Switch_1) &&
		!Engine::IMKEY_PRESS(StageKey_Switch_2) &&
		!Engine::IMKEY_PRESS(StageKey_Ult))
	{
		return true;
	}
	return false;
}

void CStageCameraMan::ShowMouseCursor()
{
	if (Engine::CInputManager::GetInstance()->GetMousePosDelta() != ZERO_VECTOR)
	{
		m_hideCursorTimer = 0.f;
		if (!m_cursorOn)
		{
			m_cursorOn = true;
			ShowCursor(true);
		}
	}
}

void CStageCameraMan::HideMouseCursor()
{
	m_hideCursorTimer += GET_PLAYER_DT;

	if (m_cursorOn && m_hideCursorTimer > 3.f)
	{
		m_cursorOn = false;
		ShowCursor(false);
		if (m_whyCursorOffOneMore)
		{
			m_whyCursorOffOneMore = false;
			ShowCursor(false);
		}
	}
}
