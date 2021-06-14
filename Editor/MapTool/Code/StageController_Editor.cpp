#include "stdafx.h"
#include "StageController_Editor.h"

IMPLEMENT_SINGLETON(CStageController_Editor)

//CStageController_Editor::CStageController_Editor()
//{
//}
//
//
//CStageController_Editor::~CStageController_Editor()
//{
//}

void CStageController_Editor::Awake(void)
{
	m_pInput = Engine::CInputManager::GetInstance();
	//m_spCurMainCam = Engine::GET_MAIN_CAM;
}

void CStageController_Editor::Start(void)
{
}


void CStageController_Editor::Update(void)
{
	if(m_spCurActor)
		MoveControl();
}

void CStageController_Editor::OnDestroy()
{
}

void CStageController_Editor::AddSquadMember(SP(Engine::CObject) pCharacter)
{
	//if (m_vSquad.size() == 3)
	//{
	//	MSG_BOX(__FILE__, L"Camera mode enum is broken in LateUpdate");
	//	ABORT;
	//}

	//m_vSquad.emplace_back(pCharacter);
}


void CStageController_Editor::MoveControl()
{
	// stand
	if (!m_inputLock_ByAni && !CheckMoveOrder())
		return;

	_float speed = 5.f;
	_float3 actorForward = m_spCurActor->GetTransform()->GetForward();
	actorForward = _float3(actorForward.x, 0.f, actorForward.z);
	m_spCurActor->GetTransform()->AddPosition(actorForward * GET_DT *speed);
	if (!m_rotateLock)
		RotateCurrentActor();
}

_bool CStageController_Editor::CheckMoveOrder()
{
	bool isMove = false;

	// up
	if (m_pInput->KeyUp(StageKey_Move_Left))
	{
		m_moveFlag &= ~MoveFlag_Left;
		m_rotateAcc = 0.f;
		m_rotateLock = false;
	}
	if (m_pInput->KeyUp(StageKey_Move_Right))
	{
		m_moveFlag &= ~MoveFlag_Right;
		m_rotateAcc = 0.f;
		m_rotateLock = false;
	}
	if (m_pInput->KeyUp(StageKey_Move_Forward))
	{
		m_moveFlag &= ~MoveFlag_Forward;
		m_rotateAcc = 0.f;
		m_rotateLock = false;
	}
	if (m_pInput->KeyUp(StageKey_Move_Back))
	{
		m_moveFlag &= ~MoveFlag_Back;
		m_rotateAcc = 0.f;
		m_rotateLock = false;
	}

	// down
	if (m_pInput->KeyPress(StageKey_Move_Left))
	{
		m_moveFlag &= ~MoveFlag_Right;
		m_moveFlag |= MoveFlag_Left;
		m_rotateAcc = 0.f;
		m_rotateLock = false;
	}
	if (m_pInput->KeyPress(StageKey_Move_Right))
	{
		m_moveFlag |= MoveFlag_Right;
		m_moveFlag &= ~MoveFlag_Left;
		m_rotateAcc = 0.f;
		m_rotateLock = false;
	}

	if (m_pInput->KeyPress(StageKey_Move_Forward))
	{
		m_moveFlag |= MoveFlag_Forward;
		m_moveFlag &= ~MoveFlag_Back;
		m_rotateAcc = 0.f;
		m_rotateLock = false;
	}
	if (m_pInput->KeyPress(StageKey_Move_Back))
	{
		m_moveFlag &= ~MoveFlag_Forward;
		m_moveFlag |= MoveFlag_Back;
		m_rotateAcc = 0.f;
		m_rotateLock = false;
	}

	if (!m_moveFlag)
		return false;

	m_moveOrderDir = ZERO_VECTOR;

	if (m_moveFlag & MoveFlag_Left)
	{
		_float3 right = Engine::GET_MAIN_CAM->GetTransform()->GetRight();
		right = _float3(right.x, 0.f, right.z);
		D3DXVec3Normalize(&right, &right);
		m_moveOrderDir -= right;
	}

	if (m_moveFlag & MoveFlag_Right)
	{
		_float3 right = Engine::GET_MAIN_CAM->GetTransform()->GetRight();
		right = _float3(right.x, 0.f, right.z);
		D3DXVec3Normalize(&right, &right);
		m_moveOrderDir += right;
	}

	if (m_moveFlag & MoveFlag_Forward)
	{
		_float3 forward = Engine::GET_MAIN_CAM->GetTransform()->GetForward();
		forward = _float3(forward.x, 0.f, forward.z);
		D3DXVec3Normalize(&forward, &forward);
		m_moveOrderDir += forward;
	}

	if (m_moveFlag & MoveFlag_Back)
	{
		_float3 forward = Engine::GET_MAIN_CAM->GetTransform()->GetForward();
		forward = _float3(forward.x, 0.f, forward.z);
		D3DXVec3Normalize(&forward, &forward);
		m_moveOrderDir -= forward;

	}

	m_moveOrderDir.y = 0.f;
	D3DXVec3Normalize(&m_moveOrderDir, &m_moveOrderDir);

	return true;
}

void CStageController_Editor::RotateCurrentActor()
{
	SP(Engine::CTransformC) pActorTransform = m_spCurActor->GetTransform();

	float rotSpeedRate = m_rotSpeedHighRate;

	_float3 actorForward = pActorTransform->GetForward();
	actorForward = _float3(actorForward.x, 0.f, actorForward.z);
	float angleSynchroRate = D3DXVec3Dot(&m_moveOrderDir, &actorForward);

	if (angleSynchroRate > 0.95f)
		rotSpeedRate = m_rotSpeedLowRate;

	_float3 rotAxis = { 0.f, 0.f, 0.f };
	D3DXVec3Cross(&rotAxis, &actorForward, &m_moveOrderDir);
	D3DXVec3Normalize(&rotAxis, &rotAxis);


	if (rotAxis.y > 0.f)
		m_spCurActor->GetTransform()->AddRotationY(m_rotSpeed * rotSpeedRate * GET_DT);
	else
		m_spCurActor->GetTransform()->AddRotationY(-m_rotSpeed * rotSpeedRate * GET_DT);

	// for correcting y rotate 0.01
	if (angleSynchroRate > 0.95f && angleSynchroRate < 0.96f)
	{
		m_rotateAcc += m_rotSpeed * rotSpeedRate * GET_DT;
	}

	if (angleSynchroRate > 0.99f)
	{
		m_spCurActor->GetTransform()->AddRotationY(m_rotateAcc);
		m_rotateAcc = 0.f;
		m_rotateLock = true;


	}

}

// 1. 새로운 애니 시작할 때 방향 고정
// 2. 회전 끝나면 회전 고정
// 3. 새 키 들어오는지 확인해야함