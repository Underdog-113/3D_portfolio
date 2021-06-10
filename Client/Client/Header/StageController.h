#ifndef STAGECONTROLLER_H
#define STAGECONTROLLER_H

#define Key_Move_Left			KEY_A
#define Key_Move_Right			KEY_D
#define Key_Move_Forward		KEY_W
#define Key_Move_Back			KEY_S

#define MoveFlag_Left 0x01
#define MoveFlag_Right 0x02
#define MoveFlag_Forward 0x04
#define MoveFlag_Back 0x08


class CStageController
{
public:
	enum Squad_Role { Actor, Wait_1, Wait_2};

public:
	CStageController();
	~CStageController();

	void Awake(void);
	void Start(void);
	void Update(void);

public:
	void AddSquadMember(SP(Engine::CObject) pCharacter);

private:	/* Actor Move */
	void MoveControl();
	bool CheckMoveOrder();
	void RotateCurrentActor();

private:	/* Change Actor */
	//void ChangeActor();

private:
	typedef std::vector<SP(Engine::CObject)> _Squad;
	GETTOR			(_Squad,				m_vSquad,			{},			Squad)
	GETTOR_SETTOR	(SP(Engine::CCamera),	m_spCurMainCam,		nullptr,	CurrentMainCam)
	GETTOR_SETTOR	(SP(Engine::CObject),	m_spCurActor,		nullptr,	CurrentActor)
	
private:
	Engine::CInputManager*		m_pInput	= nullptr;
	float						m_rotSpeed	= 10.f;
	float						m_rotSpeedHighRate = 0.8f;
	float						m_rotSpeedLowRate = 0.5f;
	_ubyte						m_moveFlag	= 0;
	_float3						m_moveOrderDir	= ZERO_VECTOR;
};

#endif