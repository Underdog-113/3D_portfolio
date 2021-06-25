#pragma once
#include "StateMachine.h"
#define Cool_Attack				0.25f
#define Cool_Evade				0.2f
#define Cool_End				0.75f

#define Cool_HitPenalty			0.5f
#define Cool_RunOnAttack		0.5f

class CTheresa;
class CStageControlTower;
class CFSM_TheresaC : public Engine::CStateMachineC
{
	enum Appear_Option { None, QTE };
public:
	CFSM_TheresaC();
	~CFSM_TheresaC() = default;

public:
	SP(Engine::CComponent)		MakeClone(Engine::CObject* pObject) override;
	void Awake(void) override;
	void Start(SP(CComponent) spThis) override;

private:
	void FixRootMotionOffset(_uint index);
	void ResetCheckMembers();

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

private: /* Special Actions */

private:
	CTheresa* m_pTheresa = nullptr;
	Engine::CDynamicMeshData* m_pDM = nullptr;
	CStageControlTower* m_pStageControlTower = nullptr;

	Appear_Option m_appearOption = None;

public:
	//IDLE
	void IDLE_Init(void);
	void IDLE_Enter(void);
	void IDLE_Update(float deltaTime);
	void IDLE_End(void);

	//APPEAR
	void APPEAR_Init(void);
	void APPEAR_Enter(void);
	void APPEAR_Update(float deltaTime);
	void APPEAR_End(void);

	//RUN
	void RUN_Init(void);
	void RUN_Enter(void);
	void RUN_Update(float deltaTime);
	void RUN_End(void);

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

	//ATTACK1
	void ATTACK1_Init(void);
	void ATTACK1_Enter(void);
	void ATTACK1_Update(float deltaTime);
	void ATTACK1_End(void);

	//ATTACK2
	void ATTACK2_Init(void);
	void ATTACK2_Enter(void);
	void ATTACK2_Update(float deltaTime);
	void ATTACK2_End(void);

	//ATTACK3
	void ATTACK3_Init(void);
	void ATTACK3_Enter(void);
	void ATTACK3_Update(float deltaTime);
	void ATTACK3_End(void);

	//ATTACK4
	void ATTACK4_Init(void);
	void ATTACK4_Enter(void);
	void ATTACK4_Update(float deltaTime);
	void ATTACK4_End(void);

	//CHARGE0
	void CHARGE0_Init(void);
	void CHARGE0_Enter(void);
	void CHARGE0_Update(float deltaTime);
	void CHARGE0_End(void);

	//CHARGE1
	void CHARGE1_Init(void);
	void CHARGE1_Enter(void);
	void CHARGE1_Update(float deltaTime);
	void CHARGE1_End(void);

	//CHARGE2
	void CHARGE2_Init(void);
	void CHARGE2_Enter(void);
	void CHARGE2_Update(float deltaTime);
	void CHARGE2_End(void);
	
	//VICTORY
	void VICTORY_Init(void);
	void VICTORY_Enter(void);
	void VICTORY_Update(float deltaTime);
	void VICTORY_End(void);

	//Die
	void Die_Init(void);
	void Die_Enter(void);
	void Die_Update(float deltaTime);
	void Die_End(void);

	//STUN
	void STUN_Init(void);
	void STUN_Enter(void);
	void STUN_Update(float deltaTime);
	void STUN_End(void);

	//QTE_FY
	void QTE_FY_Init(void);
	void QTE_FY_Enter(void);
	void QTE_FY_Update(float deltaTime);
	void QTE_FY_End(void);

	//HIT_H
	void HIT_H_Init(void);
	void HIT_H_Enter(void);
	void HIT_H_Update(float deltaTime);
	void HIT_H_End(void);

	//HIT_L
	void HIT_L_Init(void);
	void HIT_L_Enter(void);
	void HIT_L_Update(float deltaTime);
	void HIT_L_End(void);
	
	//JUMP_2
	void JUMP_2_Init(void);
	void JUMP_2_Enter(void);
	void JUMP_2_Update(float deltaTime);
	void JUMP_2_End(void);

	//JUMP_1
	void JUMP_1_Init(void);
	void JUMP_1_Enter(void);
	void JUMP_1_Update(float deltaTime);
	void JUMP_1_End(void);

	//JUMP_0
	void JUMP_0_Init(void);
	void JUMP_0_Enter(void);
	void JUMP_0_Update(float deltaTime);
	void JUMP_0_End(void);

	//SWITCHIN
	void SWITCHIN_Init(void);
	void SWITCHIN_Enter(void);
	void SWITCHIN_Update(float deltaTime);
	void SWITCHIN_End(void);

	//SWITCHOUT
	void SWITCHOUT_Init(void);
	void SWITCHOUT_Enter(void);
	void SWITCHOUT_Update(float deltaTime);
	void SWITCHOUT_End(void);

	//SWITCHINATTACK_YD
	void SWITCHINATTACK_YD_Init(void);
	void SWITCHINATTACK_YD_Enter(void);
	void SWITCHINATTACK_YD_Update(float deltaTime);
	void SWITCHINATTACK_YD_End(void);

	//SWITCHINATTACK_TP
	void SWITCHINATTACK_TP_Init(void);
	void SWITCHINATTACK_TP_Enter(void);
	void SWITCHINATTACK_TP_Update(float deltaTime);
	void SWITCHINATTACK_TP_End(void);

	//SWITCHINATTACK_FY
	void SWITCHINATTACK_FY_Init(void);
	void SWITCHINATTACK_FY_Enter(void);
	void SWITCHINATTACK_FY_Update(float deltaTime);
	void SWITCHINATTACK_FY_End(void);

	//Ult
	void Ult_Init(void);
	void Ult_Enter(void);
	void Ult_Update(float deltaTime);
	void Ult_End(void);

	//CROSSSKILL
	void CROSSSKILL_Init(void);
	void CROSSSKILL_Enter(void);
	void CROSSSKILL_Update(float deltaTime);
	void CROSSSKILL_End(void);

	//RUNSTOPRIGHT
	void RUNSTOPRIGHT_Init(void);
	void RUNSTOPRIGHT_Enter(void);
	void RUNSTOPRIGHT_Update(float deltaTime);
	void RUNSTOPRIGHT_End(void);

	//RUNSTOPLEFT
	void RUNSTOPLEFT_Init(void);
	void RUNSTOPLEFT_Enter(void);
	void RUNSTOPLEFT_Update(float deltaTime);
	void RUNSTOPLEFT_End(void);

	//FASTRUN
	void FASTRUN_Init(void);
	void FASTRUN_Enter(void);
	void FASTRUN_Update(float deltaTime);
	void FASTRUN_End(void);


private:
	void RegisterAllState();
};

