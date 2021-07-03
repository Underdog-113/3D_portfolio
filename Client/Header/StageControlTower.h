#ifndef StageControlTower_H
#define StageControlTower_H

#define MULT(x, y) ((x)*(y))

static uint64_t StageKey_AllOut = 1;
#define StageKeyAllOut(boolValue)		\
{										\
   if (boolValue)						\
     StageKey_AllOut = 0;				\
   else									\
	 StageKey_AllOut = 1;				\
}

#define StageKey_Move_Left			MULT(KEY_A, StageKey_AllOut)
#define StageKey_Move_Right			MULT(KEY_D, StageKey_AllOut)
#define StageKey_Move_Forward		MULT(KEY_W, StageKey_AllOut)
#define StageKey_Move_Back			MULT(KEY_S, StageKey_AllOut)

#define StageKey_CamRotateLeft		MULT(KEY_Q, StageKey_AllOut)
#define StageKey_CamRotateRight		MULT(KEY_E, StageKey_AllOut)

#define StageKey_Attack				MULT(KEY_J, StageKey_AllOut)
#define StageKey_Evade				MULT(KEY_K, StageKey_AllOut)
#define StageKey_WeaponSkill		MULT(KEY_U, StageKey_AllOut)
#define StageKey_QTE				MULT(KEY_U, StageKey_AllOut)
#define StageKey_Ult				MULT(KEY_I, StageKey_AllOut)

#define StageKey_Switch_1			MULT(KEY_1, StageKey_AllOut)
#define StageKey_Switch_2			MULT(KEY_2, StageKey_AllOut)
									
#define StageKey_Pause				MULT(KEY_TAB, StageKey_AllOut)
#define StageKey_Test_Emotion		MULT(KEY_Z, StageKey_AllOut)
#define StageKey_Test_Hit_L			MULT(KEY_F, StageKey_AllOut)
#define StageKey_Test_Hit_H			MULT(KEY_C, StageKey_AllOut)


class CValkyrie;
class CActorController;
class CUILinker;
class CStatusDealer;
class CPhaseControl;
class COneStagePhaseControl;
enum class EOneStagePhase;
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
	void ActorControl_SetCurrentMainCam(SP(Engine::CCamera) pCam);
	void ActorControl_SetInputLock(bool lock);
	

public:		/* Phase */
	void IncreasePhase();
	void ChangePhase(EOneStagePhase phaseType);


public:		/* Battle */
	void FindTarget();
	void HitMonster(Engine::CObject* pValkyrie, Engine::CObject* pMonster, HitInfo info, _float3 hitPoint);
	void HitValkyrie(Engine::CObject* pMonster, Engine::CObject* pValkyrie, HitInfo info, _float3 hitPoint);

	void SwitchValkyrie(Squad_Role role);


public:		/* Stage Control Mode */
	void StageClear();

private:
	typedef std::vector<SP(Engine::CObject)> _Squad;
	GETTOR			(_Squad,				m_vSquad,			{},				Squad)
	GETTOR_SETTOR	(CValkyrie*,			m_pCurActor,		nullptr,		CurrentActor)
			
	GETTOR			(CActorController*,		m_pActorController,	nullptr,		ActorController)
	GETTOR			(CUILinker*,			m_pLinker,			nullptr,		UILinker)
	GETTOR			(CStatusDealer*,		m_pDealer,			nullptr,		StatDealer)
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