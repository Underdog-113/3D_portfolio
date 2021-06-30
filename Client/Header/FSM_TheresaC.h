#pragma once
#include "StateMachineC.h"
#define Cool_Attack				0.25f
#define Cool_ChargeAttack		0.5f
#define Cool_Evade				0.2f
#define Cool_End				0.75f

#define Cool_HitPenalty			0.5f
#define Cool_RunOnAttack		0.5f

#define Delay_UltShowAxe		0.1f
#define Delay_UltHideAxe		0.1f


class CTheresa;
class CStageControlTower;
class CEffectMaker_Theresa;
class CFSM_TheresaC : public Engine::CStateMachineC
{
	enum Appear_Option { None, QTE };
public:
	CFSM_TheresaC();
	virtual ~CFSM_TheresaC();

public:
	SP(Engine::CComponent)		MakeClone(Engine::CObject* pObject) override;
	void Awake(void) override;
	void Start(SP(CComponent) spThis) override;
	void OnDestroy() override;

private:
	void FixRootMotionOffset(_uint index);
	void ResetCheckMembers();

	void OnSwordCollider();
	void OffSwordCollider();

	void OnAxeCollider();
	void OffAxeCollider();

private: /* Normal Actions */
	bool CheckAction_Attack(const std::wstring& switchStateName, float coolTime = Cool_Attack);
	bool CheckAction_Evade_OnAction(float coolTime = Cool_Evade);
	bool CheckAction_EvadeForward(float coolTime = Cool_Evade);
	bool CheckAction_EvadeBackward(float coolTime = Cool_Evade);
	bool CheckAction_StandBy_Timeout(float coolTime = Cool_End);
	bool CheckAction_Run();
	bool CheckAction_Run_OnAction(float coolTime = Cool_Evade);
	bool CheckAction_Run_End();
	bool CheckAction_Idle();
	bool CheckAction_RunBS_To_Run();
	bool CheckAction_Ultra();

private: /* Special Actions */
	bool CheckAction_ChargeAttack();
	bool CheckAction_ChargeAttack_End();
	bool CheckAction_ChargeMode();
	

private:
	CTheresa* m_pTheresa = nullptr;
	Engine::CDynamicMeshData* m_pDM = nullptr;
	CStageControlTower* m_pStageControlTower = nullptr;
	CEffectMaker_Theresa* m_pEffectMaker = nullptr;

	Appear_Option m_appearOption = None;

	_uint m_chargeAttackIndex = 1;
	_float m_chargeEnterTimer = 0.f;

	bool m_ultraAxeOnOff = false;
	bool m_ultraUsed = false;
	bool m_ultraImpact = false;

	bool m_checkEffect = false;


public:
	//StandBy
	void StandBy_Init(void);
	void StandBy_Enter(void);
	void StandBy_Update(float deltaTime);
	void StandBy_End(void);

	//Idle
	void Idle_Init(void);
	void Idle_Enter(void);
	void Idle_Update(float deltaTime);
	void Idle_End(void);

	//Appear
	void Appear_Init(void);
	void Appear_Enter(void);
	void Appear_Update(float deltaTime);
	void Appear_End(void);

	//Run
	void Run_Init(void);
	void Run_Enter(void);
	void Run_Update(float deltaTime);
	void Run_End(void);

	//RunBs
	void RunBS_Init(void);
	void RunBS_Enter(void);
	void RunBS_Update(float deltaTime);
	void RunBS_End(void);

	//EvadeBackward
	void EvadeBackward_Init(void);
	void EvadeBackward_Enter(void);
	void EvadeBackward_Update(float deltaTime);
	void EvadeBackward_End(void);

	//EvadeForward
	void EvadeForward_Init(void);
	void EvadeForward_Enter(void);
	void EvadeForward_Update(float deltaTime);
	void EvadeForward_End(void);

	//Attack1
	void Attack1_Init(void);
	void Attack1_Enter(void);
	void Attack1_Update(float deltaTime);
	void Attack1_End(void);

	//Attack2
	void Attack2_Init(void);
	void Attack2_Enter(void);
	void Attack2_Update(float deltaTime);
	void Attack2_End(void);

	//Attack3
	void Attack3_Init(void);
	void Attack3_Enter(void);
	void Attack3_Update(float deltaTime);
	void Attack3_End(void);

	//Attack4
	void Attack4_Init(void);
	void Attack4_Enter(void);
	void Attack4_Update(float deltaTime);
	void Attack4_End(void);

	//Charge0
	void Charge0_Init(void);
	void Charge0_Enter(void);
	void Charge0_Update(float deltaTime);
	void Charge0_End(void);

	//Charge1
	void Charge1_Init(void);
	void Charge1_Enter(void);
	void Charge1_Update(float deltaTime);
	void Charge1_End(void);

	//Charge2
	void Charge2_Init(void);
	void Charge2_Enter(void);
	void Charge2_Update(float deltaTime);
	void Charge2_End(void);
	
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

	//Die
	void Die_Init(void);
	void Die_Enter(void);
	void Die_Update(float deltaTime);
	void Die_End(void);

	//Stun
	void Stun_Init(void);
	void Stun_Enter(void);
	void Stun_Update(float deltaTime);
	void Stun_End(void);

// 	//QTE_FY
// 	void QTE_FY_Init(void);
// 	void QTE_FY_Enter(void);
// 	void QTE_FY_Update(float deltaTime);
// 	void QTE_FY_End(void);

	//Hit_H
	void Hit_H_Init(void);
	void Hit_H_Enter(void);
	void Hit_H_Update(float deltaTime);
	void Hit_H_End(void);

	//Hit_L
	void Hit_L_Init(void);
	void Hit_L_Enter(void);
	void Hit_L_Update(float deltaTime);
	void Hit_L_End(void);
	
// 	//JUMP_2
// 	void JUMP_2_Init(void);
// 	void JUMP_2_Enter(void);
// 	void JUMP_2_Update(float deltaTime);
// 	void JUMP_2_End(void);
// 
// 	//JUMP_1
// 	void JUMP_1_Init(void);
// 	void JUMP_1_Enter(void);
// 	void JUMP_1_Update(float deltaTime);
// 	void JUMP_1_End(void);
// 
// 	//JUMP_0
// 	void JUMP_0_Init(void);
// 	void JUMP_0_Enter(void);
// 	void JUMP_0_Update(float deltaTime);
// 	void JUMP_0_End(void);

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

// 	//SwitchInAttack_YD
// 	void SwitchInAttack_YD_Init(void);
// 	void SwitchInAttack_YD_Enter(void);
// 	void SwitchInAttack_YD_Update(float deltaTime);
// 	void SwitchInAttack_YD_End(void);
// 
// 	//SwitchInAttack_TP
// 	void SwitchInAttack_TP_Init(void);
// 	void SwitchInAttack_TP_Enter(void);
// 	void SwitchInAttack_TP_Update(float deltaTime);
// 	void SwitchInAttack_TP_End(void);
// 
// 	//SwitchInAttack_FY
// 	void SwitchInAttack_FY_Init(void);
// 	void SwitchInAttack_FY_Enter(void);
// 	void SwitchInAttack_FY_Update(float deltaTime);
// 	void SwitchInAttack_FY_End(void);

	//Ultra
	void Ultra_Init(void);
	void Ultra_Enter(void);
	void Ultra_Update(float deltaTime);
	void Ultra_End(void);

	//CastCross
	void CastCross_Init(void);
	void CastCross_Enter(void);
	void CastCross_Update(float deltaTime);
	void CastCross_End(void);

	//RunStopRight
	void RunStopRight_Init(void);
	void RunStopRight_Enter(void);
	void RunStopRight_Update(float deltaTime);
	void RunStopRight_End(void);

	//RunStopLeft
	void RunStopLeft_Init(void);
	void RunStopLeft_Enter(void);
	void RunStopLeft_Update(float deltaTime);
	void RunStopLeft_End(void);

// 	//FASTRun
// 	void FASTRun_Init(void);
// 	void FASTRun_Enter(void);
// 	void FASTRun_Update(float deltaTime);
// 	void FASTRun_End(void);


private:
	void RegisterAllState();
};

