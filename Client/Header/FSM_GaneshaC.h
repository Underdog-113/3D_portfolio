#pragma once
#include "StateMachineC.h"

class CFSM_GaneshaC final : public Engine::CStateMachineC
{
public:
	CFSM_GaneshaC();
	~CFSM_GaneshaC() = default;

public:
	SP(Engine::CComponent) MakeClone(Engine::CObject* pObject) override;
	void Awake(void) override;
	void Start(SP(CComponent) spThis) override;

private:
	void RegisterAllStage();
	void FixRootMotionOffset(_uint index);

private:
	GETTOR_SETTOR(Engine::CDynamicMeshData*, m_pDM, nullptr, DM)

public:
	// <Animation List>

	// ActivateRampage
	void ActivateRampage_Init(void);
	void ActivateRampage_Enter(void);
	void ActivateRampage_Update(float deltaTime);
	void ActivateRampage_End(void);

	// Attack01
	void Attack01_Init(void);
	void Attack01_Enter(void);
	void Attack01_Update(float deltaTime);
	void Attack01_End(void);

	// Born
	void Born_Init(void);
	void Born_Enter(void);
	void Born_Update(float deltaTime);
	void Born_End(void);

	// Burst01
	void Burst01_Init(void);
	void Burst01_Enter(void);
	void Burst01_Update(float deltaTime);
	void Burst01_End(void);

	// Burst02
	void Burst02_Init(void);
	void Burst02_Enter(void);
	void Burst02_Update(float deltaTime);
	void Burst02_End(void);

	// Die
	void Die_Init(void);
	void Die_Enter(void);
	void Die_Update(float deltaTime);
	void Die_End(void);

	// Jump_Back
	void Jump_Back_Init(void);
	void Jump_Back_Enter(void);
	void Jump_Back_Update(float deltaTime);
	void Jump_Back_End(void);

	// Jump_Turn
	void Jump_Turn_Init(void);
	void Jump_Turn_Enter(void);
	void Jump_Turn_Update(float deltaTime);
	void Jump_Turn_End(void);

	// Roll01
	void Roll01_Init(void);
	void Roll01_Enter(void);
	void Roll01_Update(float deltaTime);
	void Roll01_End(void);

	// Roll02
	void Roll02_Init(void);
	void Roll02_Enter(void);
	void Roll02_Update(float deltaTime);
	void Roll02_End(void);

	// Run
	void Run_Init(void);
	void Run_Enter(void);
	void Run_Update(float deltaTime);
	void Run_End(void);

	// Stamp
	void Stamp_Init(void);
	void Stamp_Enter(void);
	void Stamp_Update(float deltaTime);
	void Stamp_End(void);

	// StandBy
	void StandBy_Init(void);
	void StandBy_Enter(void);
	void StandBy_Update(float deltaTime);
	void StandBy_End(void);

	// Weak
	void Weak_Init(void);
	void Weak_Enter(void);
	void Weak_Update(float deltaTime);
	void Weak_End(void);

	// Weak_End
	void Weak_End_Init(void);
	void Weak_End_Enter(void);
	void Weak_End_Update(float deltaTime);
	void Weak_End_End(void);

	// Weak_Hit
	void Weak_Hit_Init(void);
	void Weak_Hit_Enter(void);
	void Weak_Hit_Update(float deltaTime);
	void Weak_Hit_End(void);

	// Weak_Loop
	void Weak_Loop_Init(void);
	void Weak_Loop_Enter(void);
	void Weak_Loop_Update(float deltaTime);
	void Weak_Loop_End(void);

	// Weak_Start
	void Weak_Start_Init(void);
	void Weak_Start_Enter(void);
	void Weak_Start_Update(float deltaTime);
	void Weak_Start_End(void);
};

