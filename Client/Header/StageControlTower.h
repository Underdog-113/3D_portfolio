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

#define StageKey_Switch_1			KEY_1
#define StageKey_Switch_2			KEY_2

#define StageKey_Pause				KEY_TAB
#define StageKey_Test_Emotion		KEY_Z
#define StageKey_Test_Hit_L			KEY_F
#define StageKey_Test_Hit_H			KEY_C


#define Kiana_Bonus_Level				5
#define Theresa_Bonus_Level				5
#define Sakura_Bonus_Level				5

class CValkyrie;
class CActorController;
class CUILinker;
class CStatusDealer;
class CStageCameraMan;
class CMovieDirector;
class CTimeSeeker;
class CPhaseControl;
class COneStagePhaseControl;
class CThreeStagePhaseControl;
class CValkyrieStatusData;
enum class EOneStagePhase;
enum class EThreeStagePhase;
class CStageControlTower
{
	DECLARE_SINGLETON(CStageControlTower)

public:
	enum CreateMode { ALL, WithoutUI };
	enum Squad_Role { Actor, Wait_1, Wait_2 };

	enum Env_Type { NoColoring,TheresaUlt, SakuraUlt, PerfectEvade };

public:
	void Awake();
	void Start(CreateMode mode = ALL);
	void Init();
	void Update();

	void OnDestroy();

public:		/* Stage Setting */
	SP(Engine::CObject) SettingSquad(Engine::CScene* pCurScene);
	SP(Engine::CObject) CreateValkyrie(Engine::CScene* pCurScene, CValkyrieStatusData* pStatData);
	void AddSquadMember(SP(Engine::CObject) pValkyrie);

	void SetCurrentMainCam(SP(Engine::CCamera) pCam);

	void ActorControl_SetInputLock(bool lock);

public:		/* Player Input */
	void ActAttack();
	void ActEvade();
	bool ActSkill();
	bool ActUltra();

	void ActSwitching();
	void SwitchValkyrie(Squad_Role role);
	void BattonTouch();
	void BattonTouch_2Member();
	void BattonTouch_3Member();
	void WaitMemberCooltimeUpdate();

public:		/* Stage System */

	bool FindTarget(HitInfo::CrowdControl cc = HitInfo::CrowdControl::CC_None);
	void LookTarget();
	void RemoveTarget();
	void CheckTargetAirBorne();

	void HitMonster(Engine::CObject* pValkyrie, Engine::CObject* pMonster, HitInfo info, _float3 hitPoint);
	void HitValkyrie(Engine::CObject* pMonster, Engine::CObject* pValkyrie, HitInfo info, _float3 hitPoint);

	void IncreasePhase();
	void ChangePhase(EOneStagePhase phaseType);

public:		/* Camera Man */
	void SetCameraMidShot();
	void SetCameraFarShot();
	void SetCameraCustomShot(_float dstMaxDistance, _float changeSpeed, _float dstXAngle);
	void OffCameraTargeting();
	void EndSwitching();

	void SetVertCorrecting(_bool val);


public:		/* Time Seeker */

	void OnPerfectEvadeMode();
	_bool GetIsPerfectEvadeMode();

	void OnSakuraUltraActive();
	void OffSakuraUltraActive();

	void OnSlowExceptPlayer();
	void OffSlowExceptPlayer();

	_float GetPlayerDeltaTime();

	void SettingEnvironmentColor();
	void SetEnvType(Env_Type envType);

public:		/* Movie Director */
	void SetDirectorMode(bool value);

private:
	typedef std::vector<SP(Engine::CObject)> _Squad;
	GETTOR			(_Squad,				m_vSquad,			{},				Squad)
	GETTOR_SETTOR	(CValkyrie*,			m_pCurActor,		nullptr,		CurrentActor)
	GETTOR_SETTOR	(SP(Engine::CObject),	m_spCurTarget,		nullptr,		CurrentTarget) 
			
private:
	GETTOR			(CActorController*,		m_pActorController,	nullptr,		ActorController)
	GETTOR			(CUILinker*,			m_pLinker,			nullptr,		UILinker)
	GETTOR			(CStatusDealer*,		m_pDealer,			nullptr,		StatDealer)
	GETTOR			(CStageCameraMan*,		m_pCameraMan,		nullptr,		CameraMan)
	GETTOR			(CMovieDirector*,		m_pMovieDirector,	nullptr,		MovieDirector)
	GETTOR			(CTimeSeeker*,			m_pTimeSeeker,		nullptr,		TimeSeeker)

	GETTOR_SETTOR	(CPhaseControl*,		m_pPhaseControl,	nullptr,		PhaseControl)

private:	/* Stage Info? */
	GETTOR_SETTOR	(_uint,					m_hitCount,			0,				HitCount)
	GETTOR_SETTOR	(_float,				m_chainLimitTime,	3.f,			ChainLimitTime)

	GETTOR			(CreateMode,			m_mode,				ALL,			CurrentMode)
	GETTOR			(Env_Type,				m_envType,			NoColoring,		EnvType)

	_bool m_isInit = false;
	_bool m_isQTESwitch = false;

	_bool m_isQTEUsed = false;
	_float m_QTEOnTimer = 0.f;


	_bool m_envColorChange = false;
	_float m_envColorTimer = 0.f;
	_float m_envColorDuration = 0.f;
	_float4 m_startEnvColor = _float4(1.f, 1.f, 1.f, 1.f);
	_float4 m_dstEnvColor = _float4(1.f, 1.f, 1.f, 1.f);


private:
	_bool cheat_eternal = false;
	_float m_time;
};

#endif

