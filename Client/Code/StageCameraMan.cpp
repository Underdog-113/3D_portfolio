#include "stdafx.h"
#include "StageCameraMan.h"
#include "StageControlTower.h"

CStageCameraMan::CStageCameraMan()
{
}


CStageCameraMan::~CStageCameraMan()
{
}

void CStageCameraMan::Awake()
{
}

void CStageCameraMan::UpdateCameraMan()
{
	if (m_spCamera->GetMode() != Engine::ECameraMode::TPS)
		return;

	ApplyHorizontalMove();
}

void CStageCameraMan::SetNearTake()
{
}

void CStageCameraMan::SetMiddleTake()
{
}

void CStageCameraMan::SetFarTake()
{
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
}

void CStageCameraMan::AutoControlMode()
{
}
