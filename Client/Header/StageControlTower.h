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


class CValkyrie;
class CActorController;
class CUILinker;
class CStatusDealer;
class CStageCameraMan;
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
public:
	void Awake(void);
	void Start(CreateMode mode = ALL);
	void Update(void);

	void OnDestroy();

public:
	SP(Engine::CObject) SettingSquad(Engine::CScene* pCurScene);
	SP(Engine::CObject) CreateValkyrie(Engine::CScene* pCurScene, CValkyrieStatusData* pStatData);
	void AddSquadMember(SP(Engine::CObject) pValkyrie);
	void ActorControl_SetInputLock(bool lock);

	void SetCurrentMainCam(SP(Engine::CCamera) pCam);

public:		/* Phase */
	void IncreasePhase();
	void ChangePhase(EOneStagePhase phaseType);
	void ChangePhase(EThreeStagePhase phaseType);

public:		/* Battle */
	void ActAttack();
	void ActEvade();
	bool ActSkill();
	bool ActUltra();

	bool FindTarget(HitInfo::CrowdControl cc = HitInfo::CrowdControl::CC_None);
	void LookTarget();
	void RemoveTarget();
	void HitMonster(Engine::CObject* pValkyrie, Engine::CObject* pMonster, HitInfo info, _float3 hitPoint);
	void HitValkyrie(Engine::CObject* pMonster, Engine::CObject* pValkyrie, HitInfo info, _float3 hitPoint);

	void SwitchValkyrie(Squad_Role role);

	void SetCameraMidTake();
	void SetCameraFarTake();
	void SetCameraCustomTake(_float dstMaxDistance, _float changeSpeed, _float dstXAngle);
	void OffCameraTargeting();
	void EndSwitching();

	void OnPerfectEvadeMode();
	_bool GetIsPerfectEvadeMode();

	void OnSakuraUltraActive();
	void OffSakuraUltraActive();

	_float GetPlayerDeltaTime();
public:		/* Stage Control Mode */

private:
	typedef std::vector<SP(Engine::CObject)> _Squad;
	GETTOR			(_Squad,				m_vSquad,			{},				Squad)
	GETTOR_SETTOR	(CValkyrie*,			m_pCurActor,		nullptr,		CurrentActor)
			
	GETTOR			(CActorController*,		m_pActorController,	nullptr,		ActorController)
	GETTOR			(CUILinker*,			m_pLinker,			nullptr,		UILinker)
	GETTOR			(CStatusDealer*,		m_pDealer,			nullptr,		StatDealer)
	GETTOR			(CStageCameraMan*,		m_pCameraMan,		nullptr,		CameraMan)
	GETTOR			(CTimeSeeker*,			m_pTimeSeeker,		nullptr,		TimeSeeker)

	GETTOR_SETTOR	(CPhaseControl*,		m_pPhaseControl,	nullptr,		PhaseControl)

private:	/* Stage Info? */
	GETTOR_SETTOR	(_uint,					m_hitCount,			0,				HitCount)
	GETTOR_SETTOR	(_float,				m_chainLimitTime,	3.f,			ChainLimitTime)
	GETTOR_SETTOR	(SP(Engine::CObject),	m_spCurTarget,		nullptr,		CurrentTarget)

	GETTOR			(CreateMode,			m_mode,				ALL,			CurrentMode)


	GETTOR(std::list<ItemSave>, m_itemList, {}, ItemList)
	GETTOR(_int, m_gold, 30, Gold)
	GETTOR(_int, m_captainExp, 530, CaptainExp)
	GETTOR(_int, m_valkyrieExp, 830, ValkyrieExp)
};

#endif

