#pragma once
#include "StateMachine.h"




class FSM_SpiderC final : public Engine::CStateMachineC
{
public:
	FSM_SpiderC();
	~FSM_SpiderC() = default;

public:
	SP(Engine::CComponent)		MakeClone		(Engine::CObject* pOwner) override;
	void Awake(void) override;
	void Start(SP(CComponent) spThis) override;

public:
	// <Animation List>
	// ATTACK_1
	void ATTACK_1_Init(void);
	void ATTACK_1_Enter(void);
	void ATTACK_1_Update(float deltaTime);
	void ATTACK_1_End(void);

	//// ATTACK_2

	void ATTACK_2_Init(void);
	void ATTACK_2_Enter(void);
	void ATTACK_2_Update(float deltaTime);
	void ATTACK_2_End(void);
	//void


public:
	void RUN_Init(void);
	void RUN_Enter(void);
	void RUN_Update(float deltaTime);
	void RUN_End(void);

public:
	void StandBy_Init(void);
	void StandBy_Enter(void);
	void StandBy_Update(float deltaTime);
	void StandBy_End(void);
};
