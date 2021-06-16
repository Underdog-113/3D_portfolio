#include "stdafx.h"
#include "StageController.h"

IMPLEMENT_SINGLETON(CStageController)

//CStageController::CStageController()
//{
//}
//
//
//CStageController::~CStageController()
//{
//}

void CStageController::Awake(void)
{
	m_pInput = Engine::CInputManager::GetInstance();
}

void CStageController::Start(void)
{
	m_spCurMainCam = Engine::CCameraManager::GetInstance()->GetCamera(L"JongSceneBasicCamera");
}


void CStageController::Update(void)
{
	MoveControl();
}

void CStageController::OnDestroy()
{
}

void CStageController::AddSquadMember(SP(Engine::CObject) pCharacter)
{
	if (m_vSquad.size() == 3)
	{
		MSG_BOX(__FILE__, L"Camera mode enum is broken in LateUpdate");
		ABORT;
	}

	Base_Stat bs;

	Squad_Stat ss(&bs);
	_SquadInfo info = std::make_pair(ss, pCharacter);

	m_vSquad.emplace_back(info);

	m_spcurActor = m_vSquad[Actor].second;
}


void CStageController::MoveControl()
{
	if (m_inputLock_ByAni)
	{
		ReserveMoveOrder();
	}
	else
	{
		if (!CheckMoveOrder())
			return;
	}

	if (!m_rotateLock)
	{
		RotateCurrentActor();
	}
}

bool CStageController::CheckMoveOrder()
{
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

	if (m_prevMoveFlag != m_moveFlag)
		m_rotateLock = false;

	m_prevMoveFlag = m_moveFlag;
	return true;
}

void CStageController::ReserveMoveOrder()
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

void CStageController::RotateCurrentActor()
{
	SP(Engine::CTransformC) pActorTransform = m_spcurActor->GetTransform();
	
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
		m_spcurActor->GetTransform()->AddRotationY(m_rotSpeed * rotSpeedRate * GET_DT);
	else
		m_spcurActor->GetTransform()->AddRotationY(-m_rotSpeed * rotSpeedRate * GET_DT);


	if (angleSynchroRate > 0.99f)
	{
		if (rotAxis.y > 0.f)
			m_spcurActor->GetTransform()->AddRotationY(D3DXToRadian(0.9f));
		else
			m_spcurActor->GetTransform()->AddRotationY(D3DXToRadian(-0.9f));

		m_rotateLock = true;
	}

}

void CStageController::SetInputLock_ByAni(bool lock)
{
	m_inputLock_ByAni = lock;
	
	if (!lock)
	{
		m_prevMoveFlag = m_moveFlag;
		m_moveFlag = m_reserveMoveFlag;


		m_moveOrderDir = m_reserveMoveOrderDir;
		if (m_prevMoveFlag != m_moveFlag)
			m_rotateLock = false;

		m_prevMoveFlag = m_moveFlag;
	}
	else
	{
		m_reserveMoveFlag = m_moveFlag;
	}
}

// 1. 새로운 애니 시작할 때 방향 고정
// 2. 회전 끝나면 회전 고정
// 3. 새 키 들어오는지 확인해야함