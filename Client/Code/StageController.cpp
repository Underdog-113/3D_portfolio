#include "stdafx.h"
#include "StageController.h"


CStageController::CStageController()
{
}


CStageController::~CStageController()
{
}

void CStageController::Awake(void)
{
	m_pInput = Engine::CInputManager::GetInstance();
	m_spCurMainCam = Engine::CCameraManager::GetInstance()->GetMainCamera();
}

void CStageController::Start(void)
{
	m_spCurActor = m_vSquad[Actor];
}


void CStageController::Update(void)
{
	MoveControl();
}

void CStageController::AddSquadMember(SP(Engine::CObject) pCharacter)
{
	if (m_vSquad.size() == 3)
	{
		MSG_BOX(__FILE__, L"Camera mode enum is broken in LateUpdate");
		ABORT;
	}

	m_vSquad.emplace_back(pCharacter);
}


void CStageController::MoveControl()
{
	// stand
	if (!CheckMoveOrder())
		return;

	RotateCurrentActor();
}

bool CStageController::CheckMoveOrder()
{
	bool isMove = false;

	// up
	if (m_pInput->KeyUp(Key_Move_Left))
	{
		m_moveFlag &= ~MoveFlag_Left;
	}
	if (m_pInput->KeyUp(Key_Move_Right))
	{
		m_moveFlag &= ~MoveFlag_Right;
	}
	if (m_pInput->KeyUp(Key_Move_Forward))
	{
		m_moveFlag &= ~MoveFlag_Forward;
	}
	if (m_pInput->KeyUp(Key_Move_Back))
	{
		m_moveFlag &= ~MoveFlag_Back;
	}

	// down
	if (m_pInput->KeyDown(Key_Move_Left))
	{
		m_moveFlag &= ~MoveFlag_Right;
		m_moveFlag |= MoveFlag_Left;
	}
	if (m_pInput->KeyDown(Key_Move_Right))
	{
		m_moveFlag |= MoveFlag_Right;
		m_moveFlag &= ~MoveFlag_Left;
	}

	if (m_pInput->KeyDown(Key_Move_Forward))
	{
		m_moveFlag |= MoveFlag_Forward;
		m_moveFlag &= ~MoveFlag_Back;
	}
	if (m_pInput->KeyDown(Key_Move_Back))
	{
		m_moveFlag &= ~MoveFlag_Forward;
		m_moveFlag |= MoveFlag_Back;
	}

	if (!m_moveFlag)
		return false;

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

	return true;
}

void CStageController::RotateCurrentActor()
{
	SP(Engine::CTransformC) pActorTransform = m_spCurActor->GetTransform();
	
	float rotSpeedRate = m_rotSpeedHighRate;

	_float3 actorForward = pActorTransform->GetForward();
	actorForward = _float3(actorForward.x, 0.f, actorForward.z);
	float angleSynchroRate = D3DXVec3Dot(&m_moveOrderDir, &actorForward);

	if (angleSynchroRate > 0.99f)
		return;
	if (angleSynchroRate > 0.95f)
		rotSpeedRate = m_rotSpeedLowRate;

	_float3 rotAxis = { 0.f, 0.f, 0.f };
	D3DXVec3Cross(&rotAxis, &actorForward, &m_moveOrderDir);
	D3DXVec3Normalize(&rotAxis, &rotAxis);
	
	if (rotAxis.y > 0.f)
		m_spCurActor->GetTransform()->AddRotationY(m_rotSpeed * rotSpeedRate * GET_DT);
	else
		m_spCurActor->GetTransform()->AddRotationY(-m_rotSpeed * rotSpeedRate * GET_DT);

}
