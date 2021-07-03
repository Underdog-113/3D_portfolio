#include "stdafx.h"
#include "StageCameraMan.h"
#include "StageControlTower.h"

#include "WndApp.h"

CStageCameraMan::CStageCameraMan()
{
}


CStageCameraMan::~CStageCameraMan()
{
}

void CStageCameraMan::Start()
{
	m_spCamera->SetTargetDist(MidTake);
	m_spCamera->SetMaxDistTPS(MidTake);
	m_spCamera->SetMode(Engine::ECameraMode::TPS_Custom);
}

void CStageCameraMan::UpdateCameraMan()
{
	if (m_spCamera->GetMode() != Engine::ECameraMode::TPS_Custom)
		return;

	
	ManualControlMode();
	
	if(!m_manualControl)
		AutoControlMode();
}

void CStageCameraMan::SetNearTake()
{
	m_curTakeType = Change;
	m_nextTakeType = Near;
	m_dstMaxDist = NearTake;
	m_changeTakeTimer = 0.f;
	m_changeTakeSpeed = 0.5f;
}

void CStageCameraMan::SetMidTake()
{
	m_curTakeType = Change;
	m_nextTakeType = Mid;
	m_dstMaxDist = MidTake;
	m_changeTakeTimer = 0.f;
	m_changeTakeSpeed = 2.f;
}

void CStageCameraMan::SetFarTake()
{
	// 거의 행동 끝나면 바로 mid로
	m_curTakeType = Change;
	m_nextTakeType = Far;
	m_dstMaxDist = FarTake;
	m_changeTakeTimer = 0.f;
	m_changeTakeSpeed = 3.f;
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
			m_gotoNearTakeTimer += GET_DT;
			if (m_gotoNearTakeTimer > 3.f)
			{
				m_gotoNearTakeTimer = 0.f;
				SetNearTake();
			}
		}
		else
		{
			m_gotoNearTakeTimer = 0.f;
		}
		break;
	case CStageCameraMan::Far:
		break;
	case CStageCameraMan::Change:
		if (m_nextTakeType == Near && !CheckNoAction())
		{
			float curDist = m_dstMaxDist;
			SetMidTake();

			m_curMaxDist = curDist;
		}

		m_changeTakeTimer += GET_DT * m_changeTakeSpeed;
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
		break;
	}
}

void CStageCameraMan::AppendTargetCorrecting()
{
}

void CStageCameraMan::AppendHorizontalCorrecting()
{
	bool isCorrected = false;

	if (Engine::IMKEY_PRESS(StageKey_Move_Left))
	{
		m_rotateYDst -= (PI / 3) * GET_DT;
		isCorrected = true;

		m_rotateLerpTimer += GET_DT;
		if (m_rotateLerpTimer > 0.5f)
		{
			m_rotateLerpTimer = 0.5f;
		}
	}
		//m_spCamera->SetLookAngleUp(m_spCamera->GetLookAngleUp() - (PI / 3) * GET_DT);
	if (Engine::IMKEY_PRESS(StageKey_Move_Right))
	{
		m_rotateYDst += (PI / 3) * GET_DT;
	}
		
		//m_spCamera->SetLookAngleUp(m_spCamera->GetLookAngleUp() + (PI / 3) * GET_DT);



	float inverseRate = 1.f - m_rotateLerpTimer;
	float sLerpTimer = 1.f - inverseRate * inverseRate;

	_float lerpPoint = FloatLerp(m_rotateLerpStart, m_rotateYDst, sLerpTimer);
	m_spCamera->SetLookAngleUp(lerpPoint);
}

void CStageCameraMan::ShakeCamera()
{
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
	}
	if (Engine::IMKEY_PRESS(StageKey_CamRotateRight))
	{
		m_rotateYDst += m_rotateSpeed;
		m_enterAutoTimer = 0.f;


		m_rotateLerpTimer = 0.5f;
		m_rotateLerpStart = m_spCamera->GetLookAngleUp();
		m_manualControl = true;
	}
	if (Engine::IMKEY_PRESS(MOUSE_RIGHT))
	{
		m_spCamera->SetRightClicked(true);
		m_rotateYDst = m_spCamera->GetLookAngleUp();
		m_manualControl = true;
		return;
	}
	else
	{
		m_spCamera->SetRightClicked(false);
	}

	m_rotateLerpTimer += GET_DT;
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

	AppendHorizontalCorrecting();

	if (m_enterAutoTimer < 1.f)
	{
		m_enterAutoTimer += GET_DT;
		return;
	}

	ChangeTake();
	
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
	m_hideCursorTimer += GET_DT;

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
