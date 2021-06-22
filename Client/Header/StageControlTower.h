#ifndef StageControlTower_H
#define StageControlTower_H

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
#define StageKey_Test_Emotion		KEY_Z
#define StageKey_Test_Hit_L			KEY_F
#define StageKey_Test_Hit_H			KEY_C


#define MoveFlag_Left 0x01
#define MoveFlag_Right 0x02
#define MoveFlag_Forward 0x04
#define MoveFlag_Back 0x08

#include "StatusDealer.h"
class CValkyrie;
class CUILinker;
class CStageControlTower
{
	DECLARE_SINGLETON(CStageControlTower)

public:
	enum CreateMode { ALL, WithoutUI };
	enum Squad_Role { Actor, Wait_1, Wait_2 };

public:
	void Awake(void);
	void Start(CreateMode mode = ALL);
	void Update(void);

	void OnDestroy();

public:
	void AddSquadMember(SP(Engine::CObject) pValkyrie);

public:


private:	/* Actor Move */
	void MoveControl();
	bool CheckMoveOrder();
	void ReserveMoveOrder();
	void RotateCurrentActor();


private:	/* Change Actor */
	//void ChangeActor();

public:
	void SetInputLock_ByAni(bool value);
	
	void StageUIControl();
	
public:		/* Battle */
	void FindTarget();
	void HitMonster(Engine::CObject* pValkyrie, Engine::CObject* pMonster, HitInfo info);
	void HitValkyrie(Engine::CObject* pMonster, Engine::CObject* pValkyrie, HitInfo info);


private:
	typedef std::vector<SP(Engine::CObject)> _Squad;
	GETTOR			(_Squad,				m_vSquad,			{},				Squad)
	GETTOR_SETTOR	(SP(Engine::CCamera),	m_spCurMainCam,		nullptr,		CurrentMainCam)
	GETTOR_SETTOR	(CValkyrie*,			m_pCurActor,		nullptr,		CurrentActor)
	
	GETTOR			(bool,					m_inputLock_ByAni,  false,			InputLock_ByAni)
		
		
	GETTOR			(CUILinker*,			m_pLinker,			nullptr,		UILinker)
	GETTOR			(CStatusDealer*,		m_pDealer,			nullptr,		StatDealer)


private:	/* Stage Info? */
	GETTOR_SETTOR	(_uint,					m_hitCount,			0,				HitCount)
	GETTOR_SETTOR	(_float,				m_chainLimitTime,	3.f,			ChainLimitTime)
	GETTOR_SETTOR	(SP(Engine::CObject),	m_spCurTarget,		nullptr,		CurrentTarget)


private:
	Engine::CInputManager*		m_pInput	= nullptr;
	float						m_rotSpeed	= 10.f;
	float						m_rotSpeedHighRate = 0.8f;
	float						m_rotSpeedLowRate = 0.5f;

	GETTOR			(_ubyte,				m_moveFlag,			0,				MoveFlag);
	_ubyte						m_prevMoveFlag = 0;
	_float3						m_moveOrderDir = ZERO_VECTOR;

	GETTOR			(_ubyte,				m_reserveMoveFlag,	0,				ReserveMoveFlag)
	_float3						m_reserveMoveOrderDir = ZERO_VECTOR;

	bool						m_rotateLock = false;
	bool						m_rotateByTarget = false;

	CreateMode					m_mode;

};

#endif