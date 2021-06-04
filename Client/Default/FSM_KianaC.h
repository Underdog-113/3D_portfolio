#ifndef FSM_KIANA_H
#define FSM_KIANA_H

#include "StateMachine.h"

class CFSM_KianaC :	public Engine::CStateMachineC
{
public:
	explicit	CFSM_KianaC();
				~CFSM_KianaC();

public:
	virtual void Awake(void) override;
	virtual void Start(SP(CComponent) spThis) override;

public:
	void Anim1_Init(void);
	void Anim1_Enter(void);
	void Anim1_Update(float deltaTime);
	void Anim1_End(void);
	
public:
	void Anim2_Init(void);
	void Anim2_Enter(void);
	void Anim2_Update(float deltaTime);
	void Anim2_End(void);

public:
	void Anim3_Init(void);
	void Anim3_Start(void);
	void Anim3_Update(float deltaTime);
	void Anim3_End(void);
};


#endif // !FSM_KIANA_H