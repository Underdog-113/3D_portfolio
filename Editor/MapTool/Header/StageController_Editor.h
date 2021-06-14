
#ifndef STAGECONTROLLER_EDITOR_H
#define STAGECONTROLLER_EDITOR_H

#define StageKey_Move_Left			KEY_LEFT
#define StageKey_Move_Right			KEY_RIGHT
#define StageKey_Move_Forward		KEY_UP
#define StageKey_Move_Back			KEY_DOWN

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


class CStageController_Editor
{
	DECLARE_SINGLETON(CStageController_Editor)

public:
	enum Squad_Role { Actor, Wait_1, Wait_2 };

public:
	//CStageController_Editor();
	//~CStageController_Editor();

	void Awake(void);
	void Start(void);
	void Update(void);

	void OnDestroy();

public:
	void AddSquadMember(SP(Engine::CObject) pCharacter);

private:	/* Actor Move */
	void MoveControl();
	bool CheckMoveOrder();
	void RotateCurrentActor();

private:
	//typedef std::vector<SP(Engine::CObject)> _Squad;
	//GETTOR(_Squad, m_vSquad, {}, Squad)
	GETTOR_SETTOR(SP(Engine::CCamera), m_spCurMainCam, nullptr, CurrentMainCam)
	GETTOR_SETTOR(Engine::CObject*, m_spCurActor, nullptr, CurrentActor)

	GETTOR(_bool, m_inputLock_ByAni, false, InputLock_ByAni)

private:
	Engine::CInputManager*		m_pInput = nullptr;
	_float						m_rotSpeed = 10.f;
	_float						m_rotSpeedHighRate = 0.8f;
	_float						m_rotSpeedLowRate = 0.5f;
	_ubyte						m_moveFlag = 0;
	_float3						m_moveOrderDir = ZERO_VECTOR;

	_float						m_rotateAcc = 0.f;
	_bool						m_rotateLock = false;
};

#endif