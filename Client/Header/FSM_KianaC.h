#pragma once
#include "StateMachineC.h"
#define Cool_Attack				0.2f
#define Cool_BranchAttack		0.5f
#define Cool_BranchAttack3to4	0.3f
#define Cool_Evade				0.2f
#define Cool_End				0.75f

#define Cool_Emotion			0.75f

#define Cool_HitPenalty			0.5f
#define Cool_RunOnAttack		0.5f

#define Delay_CreateCatPaw_Atk01 0.29f
#define Delay_CreateCatPaw_Atk02 0.1f
#define Delay_CreateCatPaw_Atk03 0.14f
#define Delay_CreateCatPaw_Atk04 0.05f
#define Delay_CreateCatPaw_Atk05 0.1f

#define Delay_CreateCatPaw_Branch_Atk03 0.05f
#define Delay_CreateCatPaw_Branch_Atk04 0.15f

class CKiana;
class CStageControlTower;
class CEffectMaker_Kiana;
class CFSM_KianaC final : public Engine::CStateMachineC
{
public:
	enum AttackOption {
		ATK01, ATK02, ATK03, ATK04, ATK05,
		Branch_ATK01, Branch_ATK02,
		QTE_ATK
	};

	enum Appear_Option { None, QTE };
public:
	CFSM_KianaC();
	virtual ~CFSM_KianaC();

public:
	SP(Engine::CComponent)		MakeClone(Engine::CObject* pOwner) override;
	void Awake(void) override;
	void Start(SP(CComponent) spThis) override;
	void OnDestroy() override;

private:
	void FixRootMotionOffset(_uint index);

private: /* Normal Actions */
	bool CheckAction_Attack(const std::wstring& switchStateName, float coolTime = Cool_Attack);
	bool CheckAction_Evade_OnAction(float coolTime = Cool_Evade);
	bool CheckAction_EvadeForward(float coolTime = Cool_Evade);
	bool CheckAction_EvadeBackward(float coolTime = Cool_Evade);
	bool CheckAction_StandBy_Timeout(float coolTime = Cool_End);
	bool CheckAction_Run();
	bool CheckAction_Run_OnAction(float coolTime = Cool_Evade);
	bool CheckAction_Run_End();
	bool CheckAction_StandBy();

	bool CheckAction_Emotion(const std::wstring& switchStateName, float coolTime = Cool_Emotion);

private: /* Special Actions */
	bool CheckAction_BranchAttack();
	bool CheckAction_RunBS_To_Run();

	bool CheckAction_Ultra();
	
private: /* sound */
	void PlayActionSound(const std::wstring& soundName, Engine::EChannelID channel);
	void PlaySound_Voice(const std::wstring& soundName);
	void PlaySound_Effect(const std::wstring& soundName);

	void PlaySound_Attack_RandomVoice();
	void PlaySound_Attack_RandomRun();
	void PlaySound_Attack_RandomEvade();
	void PlaySound_Attack_RandomHit();

private:
	void ResetCheckMembers();

	bool m_checkUltraRing = false;
	bool m_checkUltraAtk = false;
	bool m_checkEffect = false;
	bool m_checkEffectSecond = false;

private:
	CKiana* m_pKiana = nullptr;
	Engine::CDynamicMeshData* m_pDM = nullptr;
	CStageControlTower* m_pStageControlTower = nullptr;
	CEffectMaker_Kiana* m_pEffectMaker = nullptr;

	Appear_Option m_appearOption = None;
	bool m_isUltraMode = false;

	_uint m_prevAttackSoundIndex = 0;
	_uint m_prevRunSoundIndex = 0;
	_uint m_prevHitSoundIndex = 0;

	_double m_runSoundTimer = 0;
public:
	// StandBy
	void StandBy_Init(void);
	void StandBy_Enter(void);
	void StandBy_Update(float deltaTime);
	void StandBy_End(void);

	// Appear
	void Appear_Init(void);
	void Appear_Enter(void);
	void Appear_Update(float deltaTime);
	void Appear_End(void);

public:
	// Attack_1
	void Attack_1_Init(void);
	void Attack_1_Enter(void);
	void Attack_1_Update(float deltaTime);
	void Attack_1_End(void);

	// Attack_2
	void Attack_2_Init(void);
	void Attack_2_Enter(void);
	void Attack_2_Update(float deltaTime);
	void Attack_2_End(void);

	// Attack_3
	void Attack_3_Init(void);
	void Attack_3_Enter(void);
	void Attack_3_Update(float deltaTime);
	void Attack_3_End(void);

	// Attack_3_Branch
	void Attack_3_Branch_Init(void);
	void Attack_3_Branch_Enter(void);
	void Attack_3_Branch_Update(float deltaTime);
	void Attack_3_Branch_End(void);

	// Attack_4
	void Attack_4_Init(void);
	void Attack_4_Enter(void);
	void Attack_4_Update(float deltaTime);
	void Attack_4_End(void);

	// Attack_4_Branch
	void Attack_4_Branch_Init(void);
	void Attack_4_Branch_Enter(void);
	void Attack_4_Branch_Update(float deltaTime);
	void Attack_4_Branch_End(void);

	// Attack_5
	void Attack_5_Init(void);
	void Attack_5_Enter(void);
	void Attack_5_Update(float deltaTime);
	void Attack_5_End(void);

	// Attack_QTE
	void Attack_QTE_Init(void);
	void Attack_QTE_Enter(void);
	void Attack_QTE_Update(float deltaTime);
	void Attack_QTE_End(void);

public:
	// Die
	void Die_Init(void);
	void Die_Enter(void);
	void Die_Update(float deltaTime);
	void Die_End(void);

public:
	// EvadeBackward
	void EvadeBackward_Init(void);
	void EvadeBackward_Enter(void);
	void EvadeBackward_Update(float deltaTime);
	void EvadeBackward_End(void);

	// EvadeForward
	void EvadeForward_Init(void);
	void EvadeForward_Enter(void);
	void EvadeForward_Update(float deltaTime);
	void EvadeForward_End(void);

	// Failure
	void Failure_Init(void);
	void Failure_Enter(void);
	void Failure_Update(float deltaTime);
	void Failure_End(void);

	// Failure_Idle
	void Failure_Idle_Init(void);
	void Failure_Idle_Enter(void);
	void Failure_Idle_Update(float deltaTime);
	void Failure_Idle_End(void);

public:
	// Hit_H
	void Hit_H_Init(void);
	void Hit_H_Enter(void);
	void Hit_H_Update(float deltaTime);
	void Hit_H_End(void);

	// Hit_L
	void Hit_L_Init(void);
	void Hit_L_Enter(void);
	void Hit_L_Update(float deltaTime);
	void Hit_L_End(void);

public:
	// Idle_01
	void Idle_01_Init(void);
	void Idle_01_Enter(void);
	void Idle_01_Update(float deltaTime);
	void Idle_01_End(void);
	
	// Idle_02
	void Idle_02_Init(void);
	void Idle_02_Enter(void);
	void Idle_02_Update(float deltaTime);
	void Idle_02_End(void);
	
	// Idle_03
	void Idle_03_Init(void);
	void Idle_03_Enter(void);
	void Idle_03_Update(float deltaTime);
	void Idle_03_End(void);

public:
	//Run
	void Run_Init(void);
	void Run_Enter(void);
	void Run_Update(float deltaTime);
	void Run_End(void);
	//RunBS
	void RunBS_Init(void);
	void RunBS_Enter(void);
	void RunBS_Update(float deltaTime);
	void RunBS_End(void);
	//RunStopLeft
	void RunStopLeft_Init(void);
	void RunStopLeft_Enter(void);
	void RunStopLeft_Update(float deltaTime);
	void RunStopLeft_End(void);
	//RunStopRight
	void RunStopRight_Init(void);
	void RunStopRight_Enter(void);
	void RunStopRight_Update(float deltaTime);
	void RunStopRight_End(void);

public:
	//WeaponSkill
	void WeaponSkill_Init(void);
	void WeaponSkill_Enter(void);
	void WeaponSkill_Update(float deltaTime);
	void WeaponSkill_End(void);

public:
	//Stun
	void Stun_Init(void);
	void Stun_Enter(void);
	void Stun_Update(float deltaTime);
	void Stun_End(void);
	//SwitchIn
	void SwitchIn_Init(void);
	void SwitchIn_Enter(void);
	void SwitchIn_Update(float deltaTime);
	void SwitchIn_End(void);
	//SwitchOut
	void SwitchOut_Init(void);
	void SwitchOut_Enter(void);
	void SwitchOut_Update(float deltaTime);
	void SwitchOut_End(void);
	//Ultra
	void Ultra_Init(void);
	void Ultra_Enter(void);
	void Ultra_Update(float deltaTime);
	void Ultra_End(void);
	//Victory
	void Victory_Init(void);
	void Victory_Enter(void);
	void Victory_Update(float deltaTime);
	void Victory_End(void);
	//Victory_Idle
	void Victory_Idle_Init(void);
	void Victory_Idle_Enter(void);
	void Victory_Idle_Update(float deltaTime);
	void Victory_Idle_End(void);

private:
	void RegisterAllState();
};
