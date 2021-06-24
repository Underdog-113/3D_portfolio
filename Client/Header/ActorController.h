#pragma once
class CActorController
{
public:
	CActorController();
	~CActorController();

public:
	void UpdateController();
	void SetInputLock_ByAni(bool value);

private:	/* Actor Move */
	bool CheckMoveOrder();
	void ReserveMoveOrder();
	void RotateCurrentActor();

	void TargetingOn();

private:
	Engine::CInputManager*		m_pInput	= nullptr;
	
	GETTOR_SETTOR	(CStageControlTower*,		m_pCT,			nullptr,		ControlTower)
	GETTOR_SETTOR	(SP(Engine::CCamera),	m_spCurMainCam,		nullptr,		CurrentMainCam)

	float						m_rotSpeed	= 10.f;
	float						m_rotSpeedHighRate = 0.8f;
	float						m_rotSpeedLowRate = 0.5f;
	
	GETTOR			(bool,		m_inputLock_ByAni,  false,			InputLock_ByAni)
	GETTOR			(_ubyte,	m_moveFlag,			0,				MoveFlag);
	GETTOR			(_ubyte,	m_reserveMoveFlag,	0,				ReserveMoveFlag)
	_ubyte						m_prevMoveFlag = 0;

	_float3						m_moveOrderDir = ZERO_VECTOR;
	_float3						m_reserveMoveOrderDir = ZERO_VECTOR;

	bool						m_rotateLock = false;
	bool						m_rotateByTarget = false;


};

