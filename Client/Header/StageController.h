#ifndef STAGECONTROLLER_H
#define STAGECONTROLLER_H

#define StageKey_Move_Left			KEY_A
#define StageKey_Move_Right			KEY_D
#define StageKey_Move_Forward		KEY_W
#define StageKey_Move_Back			KEY_S

#define StageKey_CamRotateLeft		KEY_Q
#define StageKey_CamRotateRight		KEY_E

#define StageKey_Attack				KEY_J
#define StageKey_Evade				KEY_K
#define StageKey_WeaponSkill		KEY_U
#define StageKey_QTE				KEY_U
#define StageKey_Ult				KEY_I
									 
#define StageKey_Swap_1				KEY_1
#define StageKey_Swap_2				KEY_2
									 
#define StageKey_Pause				KEY_TAB
#define StageKey_Test_Emotion		KEY_R
#define StageKey_Test_Hit_L			KEY_F
#define StageKey_Test_Hit_H			KEY_C


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