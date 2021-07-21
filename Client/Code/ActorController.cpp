#include "stdafx.h"
#include "ActorController.h"

#include "StageControlTower.h"
#include "UILinker.h"

#include "Valkyrie.h"

CActorController::CActorController()
{
	m_pInput = Engine::CInputManager::GetInstance();
	m_rotSpeed = 18.f;

	m_rotateLock = true;

}


CActorController::~CActorController()
{
}


void CActorController::UpdateController()
{
	if (m_directorMode)
		return;

	if (m_inputLock_ByAni)
	{
		ReserveMoveOrder();
	}
	else
	{
		if (!CheckMoveOrder())
			return;
// 		else
// 			m_pCT->OffCameraTargeting();
	}
	
	if (!m_rotateLock)
	{
		RotateCurrentActor();
	}
}

void CActorController::SetInputLock_ByAni(bool lock)
{
	m_inputLock_ByAni = lock;

	if (lock)
	{
		// start attack
		if (m_moveFlag)
		{
			//move
			m_reserveMoveFlag = m_moveFlag;
			m_prevMoveFlag = m_moveFlag;
		}
		else
		{
			//stop
			m_reserveMoveFlag = m_prevMoveFlag;
			m_prevMoveFlag = 0;
		}
	}
	else
	{
		if (m_reserveMoveFlag)
		{
			if (m_prevMoveFlag != m_reserveMoveFlag)
			{
				// move
				m_rotateLock = false;

				m_moveFlag = m_reserveMoveFlag;
				m_moveOrderDir = m_reserveMoveOrderDir;
			}
		}
		else
		{
			// stop
			m_rotateLock = true;
			m_moveFlag = 0;
			m_prevMoveFlag = 0;
		}
	}
}

bool CActorController::CheckMoveOrder()
{
	if (m_rotateByTarget)
		return false;

	bool isMove = false;

	// up
	if (m_pInput->KeyUp(StageKey_Move_Left))
	{
		m_moveFlag &= ~MoveFlag_Left;

	}
	if (m_pInput->KeyUp(StageKey_Move_Right))
	{
		m_moveFlag &= ~MoveFlag_Right;

	}
	if (m_pInput->KeyUp(StageKey_Move_Forward))
	{
		m_moveFlag &= ~MoveFlag_Forward;

	}
	if (m_pInput->KeyUp(StageKey_Move_Back))
	{
		m_moveFlag &= ~MoveFlag_Back;

	}

	// down
	if (m_pInput->KeyPress(StageKey_Move_Left))
	{
		m_moveFlag &= ~MoveFlag_Right;
		m_moveFlag |= MoveFlag_Left;

	}
	if (m_pInput->KeyPress(StageKey_Move_Right))
	{
		m_moveFlag |= MoveFlag_Right;
		m_moveFlag &= ~MoveFlag_Left;

	}

	if (m_pInput->KeyPress(StageKey_Move_Forward))
	{
		m_moveFlag |= MoveFlag_Forward;
		m_moveFlag &= ~MoveFlag_Back;

	}
	if (m_pInput->KeyPress(StageKey_Move_Back))
	{
		m_moveFlag &= ~MoveFlag_Forward;
		m_moveFlag |= MoveFlag_Back;

	}

	if (m_pCT->GetCurrentMode() != CStageControlTower::WithoutUI)
		m_pCT->GetUILinker()->MoveJoyStick();	// ui interact

	if (!m_moveFlag)
		return false;
	if (m_rotateByTarget)
		return true;

	m_moveOrderDir = ZERO_VECTOR;

	if (m_moveFlag & MoveFlag_Left)
	{
		_float3 right = m_spCurMainCam->GetTransform()->GetRight();
		right = _float3(right.x, 0.f, right.z);
		D3DXVec3Normalize(&right, &right);
		m_moveOrderDir -= right;
	}

	if (m_moveFlag & MoveFlag_Right)
	{
		_float3 right = m_spCurMainCam->GetTransform()->GetRight();
		right = _float3(right.x, 0.f, right.z);
		D3DXVec3Normalize(&right, &right);
		m_moveOrderDir += right;
	}

	if (m_moveFlag & MoveFlag_Forward)
	{
		_float3 forward = m_spCurMainCam->GetTransform()->GetForward();
		forward = _float3(forward.x, 0.f, forward.z);
		D3DXVec3Normalize(&forward, &forward);
		m_moveOrderDir += forward;
	}

	if (m_moveFlag & MoveFlag_Back)
	{
		_float3 forward = m_spCurMainCam->GetTransform()->GetForward();
		forward = _float3(forward.x, 0.f, forward.z);
		D3DXVec3Normalize(&forward, &forward);
		m_moveOrderDir -= forward;

	}

	m_moveOrderDir.y = 0.f;
	D3DXVec3Normalize(&m_moveOrderDir, &m_moveOrderDir);


// 	if (m_prevMoveFlag != m_moveFlag || m_moveFlag & MoveFlag_Left || m_moveFlag & MoveFlag_Right)
// 		m_rotateLock = false;
	if (m_moveFlag)
	{

		CValkyrie* pCurActor = m_pCT->GetCurrentActor();

		_float3 actorForward = pCurActor->GetTransform()->GetForward();
		actorForward = _float3(actorForward.x, 0.f, actorForward.z);
		D3DXVec3Normalize(&actorForward, &actorForward);

		float angleSynchroRate = D3DXVec3Dot(&actorForward, &m_moveOrderDir);

		if (angleSynchroRate < 0.99f)
		{
			m_rotateLock = false;
		}
	}


	m_prevMoveFlag = m_moveFlag;
	return true;
}

void CActorController::ReserveMoveOrder()
{
	bool isMove = false;

	// up
	if (m_pInput->KeyUp(StageKey_Move_Left))
	{
		m_reserveMoveFlag &= ~MoveFlag_Left;
	}
	if (m_pInput->KeyUp(StageKey_Move_Right))
	{
		m_reserveMoveFlag &= ~MoveFlag_Right;
	}
	if (m_pInput->KeyUp(StageKey_Move_Forward))
	{
		m_reserveMoveFlag &= ~MoveFlag_Forward;
	}
	if (m_pInput->KeyUp(StageKey_Move_Back))
	{
		m_reserveMoveFlag &= ~MoveFlag_Back;
	}

	// down
	if (m_pInput->KeyPress(StageKey_Move_Left))
	{
		m_reserveMoveFlag &= ~MoveFlag_Right;
		m_reserveMoveFlag |= MoveFlag_Left;
	}
	if (m_pInput->KeyPress(StageKey_Move_Right))
	{
		m_reserveMoveFlag |= MoveFlag_Right;
		m_reserveMoveFlag &= ~MoveFlag_Left;
	}

	if (m_pInput->KeyPress(StageKey_Move_Forward))
	{
		m_reserveMoveFlag |= MoveFlag_Forward;
		m_reserveMoveFlag &= ~MoveFlag_Back;
	}
	if (m_pInput->KeyPress(StageKey_Move_Back))
	{
		m_reserveMoveFlag &= ~MoveFlag_Forward;
		m_reserveMoveFlag |= MoveFlag_Back;
	}

	if (m_pCT->GetCurrentMode() != CStageControlTower::WithoutUI)
		m_pCT->GetUILinker()->MoveJoyStick();	// ui interact

	if (!m_reserveMoveFlag)
		return;

	m_reserveMoveOrderDir = ZERO_VECTOR;

	if (m_reserveMoveFlag & MoveFlag_Left)
	{
		_float3 right = m_spCurMainCam->GetTransform()->GetRight();
		right = _float3(right.x, 0.f, right.z);
		D3DXVec3Normalize(&right, &right);
		m_reserveMoveOrderDir -= right;
	}

	if (m_reserveMoveFlag & MoveFlag_Right)
	{
		_float3 right = m_spCurMainCam->GetTransform()->GetRight();
		right = _float3(right.x, 0.f, right.z);
		D3DXVec3Normalize(&right, &right);
		m_reserveMoveOrderDir += right;
	}

	if (m_reserveMoveFlag & MoveFlag_Forward)
	{
		_float3 forward = m_spCurMainCam->GetTransform()->GetForward();
		forward = _float3(forward.x, 0.f, forward.z);
		D3DXVec3Normalize(&forward, &forward);
		m_reserveMoveOrderDir += forward;
	}

	if (m_reserveMoveFlag & MoveFlag_Back)
	{
		_float3 forward = m_spCurMainCam->GetTransform()->GetForward();
		forward = _float3(forward.x, 0.f, forward.z);
		D3DXVec3Normalize(&forward, &forward);
		m_reserveMoveOrderDir -= forward;

	}

	m_reserveMoveOrderDir.y = 0.f;
	D3DXVec3Normalize(&m_reserveMoveOrderDir, &m_reserveMoveOrderDir);

}

void CActorController::RotateCurrentActor()
{
	CValkyrie* pCurActor = m_pCT->GetCurrentActor();
	
	float rotSpeedRate = m_rotSpeedHighRate;

	_float3 actorForward = pCurActor->GetTransform()->GetForward();
	actorForward = _float3(actorForward.x, 0.f, actorForward.z);
	D3DXVec3Normalize(&actorForward, &actorForward);

	float angleSynchroRate = D3DXVec3Dot(&actorForward, &m_moveOrderDir);
	angleSynchroRate = GET_MATH->RoundOffRange(angleSynchroRate, 1);

// 	if (angleSynchroRate > 0.95f)
// 	{
// 		m_rotSpeed = 10.f;
// 		float lerpValue = (angleSynchroRate - 0.95f) * 20.f;
// 		rotSpeedRate = 1.f - lerpValue;
// 	}
// 	else
// 	{
// 		m_rotSpeed = 18.f;
// 	}


	_float3 rotAxis = { 0.f, 0.f, 0.f };
	D3DXVec3Cross(&rotAxis, &actorForward, &m_moveOrderDir);
	D3DXVec3Normalize(&rotAxis, &rotAxis);
	if (rotAxis.y > 0.f)
	{
		if (angleSynchroRate > 0.95f)
		{
			m_rotateLock = true;
			m_rotateByTarget = false;

			_float cosValue = acosf(angleSynchroRate);

			pCurActor->GetTransform()->AddRotationY(cosValue);
			
			return;
		}
		pCurActor->GetTransform()->AddRotationY(m_rotSpeed * rotSpeedRate * GET_PLAYER_DT);
	}
	else
	{
		if (angleSynchroRate > 0.95f)
		{
			m_rotateLock = true;
			m_rotateByTarget = false;

			_float cosValue = acosf(angleSynchroRate);

			pCurActor->GetTransform()->AddRotationY(-cosValue);
			return;
		}
		pCurActor->GetTransform()->AddRotationY(-m_rotSpeed * rotSpeedRate * GET_PLAYER_DT);
	}

}


void CActorController::TargetingOn()
{
	m_rotateLock = false;
	m_rotateByTarget = true;

	CValkyrie* pCurActor = m_pCT->GetCurrentActor();
	_float3 valkyriePos = pCurActor->GetTransform()->GetPosition();
	valkyriePos.y = 0.f;

	_float3 targetPos = m_pCT->GetCurrentTarget()->GetTransform()->GetPosition();
	targetPos.y = 0.f;
	m_moveOrderDir = targetPos - valkyriePos;

	D3DXVec3Normalize(&m_moveOrderDir, &m_moveOrderDir);

	m_moveFlag = 0;
	m_prevMoveFlag = 0;
}

void CActorController::LookHittedDirection(_float3 hitPos)
{
	CValkyrie* pCurActor = m_pCT->GetCurrentActor();
	_float3 valkyriePos = pCurActor->GetTransform()->GetPosition();
	valkyriePos.y = 0.f;

	hitPos.y = 0.f;
	_float3 dir = hitPos - valkyriePos;

	D3DXVec3Normalize(&dir, &dir);
	
	_float3 rotAxis = { 0.f, 0.f, 0.f };
	_float3 actorForward = pCurActor->GetTransform()->GetForward();
	D3DXVec3Cross(&rotAxis, &actorForward, &dir);
	D3DXVec3Normalize(&rotAxis, &rotAxis);

	float angleSynchroRate = D3DXVec3Dot(&actorForward, &dir);
	angleSynchroRate = GET_MATH->RoundOffRange(angleSynchroRate, 1);
	_float cosValue = acosf(angleSynchroRate);

	if (rotAxis.y > 0.f)
	{
		pCurActor->GetTransform()->AddRotationY(cosValue);
	}
	else
	{
		pCurActor->GetTransform()->AddRotationY(-cosValue);
	}

	m_moveOrderDir = dir;
	m_reserveMoveOrderDir = dir;
}
