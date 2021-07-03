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

void CStageCameraMan::UpdateCameraMan()
{
	if (m_spCamera->GetMode() != Engine::ECameraMode::TPS)
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
	m_changeTakeSpeed = 1.f;
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
	m_changeTakeSpeed = 2.f;
}

void CStageCameraMan::ChangeTake()
{
	switch (m_curTakeType)
	{
	case CStageCameraMan::Near:

		break;
	case CStageCameraMan::Mid:

		break;
	case CStageCameraMan::Far:
		break;
	case CStageCameraMan::Change:
	{
		m_changeTakeTimer += GET_DT;
		if (m_changeTakeTimer > 1.f)
		{
			m_curMaxDist = m_dstMaxDist;
			switch (m_nextTakeType)
			{
			case CStageCameraMan::Near:
				break;
			case CStageCameraMan::Mid:
				break;
			case CStageCameraMan::Far:
				break;
			}
			return;
		}

		_float lerpPoint = FloatLerp(m_curMaxDist, m_dstMaxDist, m_changeTakeTimer);
		m_spCamera->SetMaxDistTPS(lerpPoint);
		break;
	}
	}
// 	if (m_curMaxDist == m_dstMaxDist)
// 	{
// 		if (m_noAction)
// 		{
// 			m_gotoNearTakeTimer += GET_DT;
// 			if (m_gotoNearTakeTimer > 3.f)
// 			{
// 				SetNearTake();
// 			}
// 			return;
// 		}
// 		
// 		if (!Engine::IMKEY_PRESS(StageKey_Move_Forward) &&
// 				!Engine::IMKEY_PRESS(StageKey_Move_Left) &&
// 				!Engine::IMKEY_PRESS(StageKey_Move_Right) &&
// 				!Engine::IMKEY_PRESS(StageKey_Move_Back) &&
// 				!Engine::IMKEY_PRESS(StageKey_Attack) &&
// 				!Engine::IMKEY_PRESS(StageKey_Evade) &&
// 				!Engine::IMKEY_PRESS(StageKey_WeaponSkill) &&
// 				!Engine::IMKEY_PRESS(StageKey_Switch_1) &&
// 				!Engine::IMKEY_PRESS(StageKey_Switch_2) &&
// 				!Engine::IMKEY_PRESS(StageKey_Ult))
// 		{
// 			m_gotoNearTakeTimer = 0.f;
// 			m_noAction = true;
// 		}
// 		else if(m_dstMaxDist == NearTake)
// 		{
// 
// 			m_noAction = false;
// 			SetMidTake();
// 		}
// 		return;
// 	}

}

void CStageCameraMan::ApplyTargetingMove()
{
}

void CStageCameraMan::ApplyHorizontalMove()
{
	if (Engine::IMKEY_PRESS(StageKey_Move_Left))
		m_spCamera->SetLookAngleUp(m_spCamera->GetLookAngleUp() - (PI / 3) * GET_DT);
	if (Engine::IMKEY_PRESS(StageKey_Move_Right))
		m_spCamera->SetLookAngleUp(m_spCamera->GetLookAngleUp() + (PI / 3) * GET_DT);
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
		m_rotateDst -= m_rotateSpeed;
		m_enterAutoTimer = 0.f;

		m_rotateLerpTimer = 0.5f;
		m_rotateLerpStart = m_spCamera->GetLookAngleUp();
		m_manualControl = true;
	}
	if (Engine::IMKEY_PRESS(StageKey_CamRotateRight))
	{
		m_rotateDst += m_rotateSpeed;
		m_enterAutoTimer = 0.f;


		m_rotateLerpTimer = 0.5f;
		m_rotateLerpStart = m_spCamera->GetLookAngleUp();
		m_manualControl = true;
	}
	if (Engine::IMKEY_PRESS(MOUSE_RIGHT))
	{
		m_spCamera->SetRightClicked(true);
		m_rotateDst = m_spCamera->GetLookAngleUp();
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
		m_spCamera->SetLookAngleUp(m_rotateDst);
		return;
	}

	float inverseRate = 1.f - m_rotateLerpTimer;
	float sLerpTimer = 1.f - inverseRate * inverseRate;

	_float lerpPoint = FloatLerp(m_rotateLerpStart, m_rotateDst, sLerpTimer);
	m_spCamera->SetLookAngleUp(lerpPoint);
}

void CStageCameraMan::AutoControlMode()
{
	HideMouseCursor();

	if (m_enterAutoTimer < 1.f)
	{
		m_enterAutoTimer += GET_DT;
		return;
	}

	//ChangeTake();
	
	ApplyHorizontalMove();
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
