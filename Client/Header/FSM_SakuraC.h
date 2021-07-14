#pragma once
#include "StateMachineC.h"
#define Cool_Attack				0.25f
#define Cool_ChargeAttack		0.5f
#define Cool_ChargeQuick		0.3f
#define Cool_Evade				0.2f
#define Cool_End				0.85f

#define Cool_HitPenalty			0.5f
#define Cool_RunOnAttack		0.5f

#define Delay_Attack1_StandBy	0.11f
#define Delay_Attack1_Combat	0.09f
#define Delay_Attack2_1	0.10f
#define Delay_Attack2_2	0.27f
#define Delay_Attack3	0.28f
#define Delay_Attack4_1	0.15f
#define Delay_Attack4_2	0.22f
#define Delay_Attack4_3	0.37f

#define Delay_Effect_Charge1 0.4f


class CSakura;
class CStageControlTower;
class CEffectMaker_Sakura;
class CFSM_SakuraC : public Engine::CStateMachineC
{
	enum Appear_Option { None, QTE };
public:
	CFSM_SakuraC();
	virtual ~CFSM_SakuraC();

public:
	SP(Engine::CComponent)		MakeClone(Engine::CObject* pObject) override;
	void Awake(void) override;
	void Start(SP(CComponent) spThis) override;
	void OnDestroy() override;
private:
	void FixRootMotionOffset(_uint index);
	void ResetCheckMembers();

	void OnAttackBall(_float damageRate, _float breakDamage, HitInfo::Strength strType, HitInfo::CrowdControl ccType);

	void FlashAttack(_float damageRate, _float breakDamage, HitInfo::Strength strType, HitInfo::CrowdControl ccType);
	void SakuraCutting();
	void InfernoActive_1st();

private: /* Normal Actions */
	bool CheckAction_Attack(const std::wstring& switchStateName, float coolTime = Cool_Attack);
	bool CheckAction_Charge(float coolTime = Cool_ChargeAttack);
	bool CheckAction_ChargeQuick(float coolTime = Cool_ChargeQuick);
	bool CheckAction_Evade_OnAction(float coolTime = Cool_Evade);
	bool CheckAction_EvadeForward(float coolTime = Cool_Evade);
	bool CheckAction_EvadeBackward(float coolTime = Cool_Evade);
	bool CheckAction_StandBy_Timeout(float coolTime = Cool_End);
	bool CheckAction_CombatToStandBy(float coolTime = Cool_End);
	bool CheckAction_Combat_Timeout(float coolTime = Cool_End);
	bool CheckAction_Run_OnCombat(float coolTime = Cool_Evade);
	bool CheckAction_Run_OnAction(float coolTime = Cool_Evade);
	bool CheckAction_Run_End();
	bool CheckAction_RunBS_To_Run();
	bool CheckAction_WeaponSkill(float coolTime = 0.f);
	bool CheckAction_Ultra(float coolTime = 0.f);
	bool CheckAction_Idle();

private: /* Special Actions */
	bool CheckAction_ChargeEnd();


private: /* sound */
	void PlayActionSound(const std::wstring& soundName, Engine::EChannelID channel);
	void PlaySound_Voice(const std::wstring& soundName);
	void PlaySound_Effect(const std::wstring& soundName);
	void PlaySound_EffectCh2(const std::wstring& soundName);

	void PlaySound_Voice_RandomAttack();
	void PlaySound_Voice_RandomHit();

	void PlaySound_Effect_RandomEvade();	
	void PlaySound_Effect_RandomUltraAttack();
	void PlaySound_Effect_RandomRun();

	_uint m_prevAttackVoiceSoundIndex = 0;
	_uint m_prevHitVoiceSoundIndex = 0;
	_uint m_prevEvadeEffectSoundIndex = 0;
	_uint m_prevUltraAttackEffectSoundIndex = 0;
	_uint m_prevRunSoundIndex = 0;

private:
	bool m_checkEffect = false;
	bool m_checkEffect2nd = false;
	bool m_checkEffect3rd = false;
	bool m_checkAttack = false;
	bool m_checkAttack2nd = false;
	bool m_checkAttack3rd = false;
	bool m_checkFlashCol = false;
	bool m_checkEndFlash = false;
	bool m_checkFlashMove = false;

	bool m_isEvade = false;
	bool m_isSecondEvade = false;

private:
	CSakura* m_pSakura = nullptr;
	Engine::CDynamicMeshData* m_pDM = nullptr;
	CStageControlTower* m_pStageControlTower = nullptr;
	CEffectMaker_Sakura* m_pEffectMaker = nullptr;

	Appear_Option m_appearOption = None;
	_float m_idleTimer = 0.f;
	_float m_combatTimer = 0.f;
	_float m_chargeEnterTimer = 0.f;

	_double m_runSoundTimer = 0;

	_float3 m_targetToSakura = ZERO_VECTOR;


private:
	// Appear
	void Appear_Init(void);
	void Appear_Enter(void);
	void Appear_Update(float deltaTime);
	void Appear_End(void);

	// StandBy
	void StandBy_Init(void);
	void StandBy_Enter(void);
	void StandBy_Update(float deltaTime);
	void StandBy_End(void);

	// Attack1_StandBy
	void Attack1_StandBy_Init(void);
	void Attack1_StandBy_Enter(void);
	void Attack1_StandBy_Update(float deltaTime);
	void Attack1_StandBy_End(void);

	// Attack1_Combat
	void Attack1_Combat_Init(void);
	void Attack1_Combat_Enter(void);
	void Attack1_Combat_Update(float deltaTime);
	void Attack1_Combat_End(void);

	// Attack2
	void Attack2_Init(void);
	void Attack2_Enter(void);
	void Attack2_Update(float deltaTime);
	void Attack2_End(void);

	// Attack3
	void Attack3_Init(void);
	void Attack3_Enter(void);
	void Attack3_Update(float deltaTime);
	void Attack3_End(void);

	// Attack4
	void Attack4_Init(void);
	void Attack4_Enter(void);
	void Attack4_Update(float deltaTime);
	void Attack4_End(void);

	// Attack5
	void Attack5_Init(void);
	void Attack5_Enter(void);
	void Attack5_Update(float deltaTime);
	void Attack5_End(void);

	// Attack6
	void Attack6_Init(void);
	void Attack6_Enter(void);
	void Attack6_Update(float deltaTime);
	void Attack6_End(void);

	// Charge1
	void Charge1_Init(void);
	void Charge1_Enter(void);
	void Charge1_Update(float deltaTime);
	void Charge1_End(void);

	// Charge1_AS
	void Charge1_AS_Init(void);
	void Charge1_AS_Enter(void);
	void Charge1_AS_Update(float deltaTime);
	void Charge1_AS_End(void);

	// Charge1_Quick
	void Charge1_Quick_Init(void);
	void Charge1_Quick_Enter(void);
	void Charge1_Quick_Update(float deltaTime);
	void Charge1_Quick_End(void);

	// Combat
	void Combat_Init(void);
	void Combat_Enter(void);
	void Combat_Update(float deltaTime);
	void Combat_End(void);

	// CombatToStandBy
	void CombatToStandBy_Init(void);
	void CombatToStandBy_Enter(void);
	void CombatToStandBy_Update(float deltaTime);
	void CombatToStandBy_End(void);

	// Die
	void Die_Init(void);
	void Die_Enter(void);
	void Die_Update(float deltaTime);
	void Die_End(void);

	// EvadeForward
	void EvadeForward_Init(void);
	void EvadeForward_Enter(void);
	void EvadeForward_Update(float deltaTime);
	void EvadeForward_End(void);

	// EvadeBackward
	void EvadeBackward_Init(void);
	void EvadeBackward_Enter(void);
	void EvadeBackward_Update(float deltaTime);
	void EvadeBackward_End(void);

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

	// Idle
	void Idle_Init(void);
	void Idle_Enter(void);
	void Idle_Update(float deltaTime);
	void Idle_End(void);
	
	// Run
	void Run_Init(void);
	void Run_Enter(void);
	void Run_Update(float deltaTime);
	void Run_End(void);

	// Run_StartFromZero
	void Run_StartFromZero_Init(void);
	void Run_StartFromZero_Enter(void);
	void Run_StartFromZero_Update(float deltaTime);
	void Run_StartFromZero_End(void);

	// RunBS
	void RunBS_Init(void);
	void RunBS_Enter(void);
	void RunBS_Update(float deltaTime);
	void RunBS_End(void);

	// RunStopLeft
	void RunStopLeft_Init(void);
	void RunStopLeft_Enter(void);
	void RunStopLeft_Update(float deltaTime);
	void RunStopLeft_End(void);

	// RunStopRight
	void RunStopRight_Init(void);
	void RunStopRight_Enter(void);
	void RunStopRight_Update(float deltaTime);
	void RunStopRight_End(void);

	// StandBy_Back
	void StandBy_Back_Init(void);
	void StandBy_Back_Enter(void);
	void StandBy_Back_Update(float deltaTime);
	void StandBy_Back_End(void);

	// Stun
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

	//TurnAround
	void TurnAround_Init(void);
	void TurnAround_Enter(void);
	void TurnAround_Update(float deltaTime);
	void TurnAround_End(void);

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

	//WeaponSkill
	void WeaponSkill_Init(void);
	void WeaponSkill_Enter(void);
	void WeaponSkill_Update(float deltaTime);
	void WeaponSkill_End(void);

private:
	void RegisterAllState();
};