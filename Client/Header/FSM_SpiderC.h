#pragma once
#include "StateMachine.h"

class FSM_SpiderC : public Engine::CStateMachineC
{
public:
	FSM_SpiderC();
	virtual ~FSM_SpiderC() = default;

public:
	virtual void Awake(void) override;
	virtual void Start(SP(CComponent) spThis) override;

public:
	// <Animation List>
	// ATTACK_1
	void ATTACK_1_Init(void);
	void ATTACK_1_Enter(void);
	void ATTACK_1_Update(float deltaTime);
	void ATTACK_1_End(void);

	//// ATTACK_2
	//void 
};
