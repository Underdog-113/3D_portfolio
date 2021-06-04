#pragma once
#include "Monster.h"

class CMineMonster : public CMonster
{
	SMART_DELETER_REGISTER

public:
	enum MINE_STATE {
		WALK_RIGHT,
		WALK_LEFT,
		WALK_FORWARD,
		THROW_BLOW,
		THROW_02,
		THROW_01,
		IDLE,
		KNOCK_DOWN,
		HIT_THROW_L,
		HIT_THROW,
		HIT_L_EARLY,
		HIT_H,
		BURY_LOOP,
		BURY_BS,
		BURY_AS,
		BORN,
		ATTACK_DIE,
		ATTACK_3_BS,
		ATTACK_3_AS,
		ATTACK_3,
		ATTACK_2_RUN,
		ATTACK_2_BS,
		ATTACK_2,
		ATTACK_1,
		STATE_END
	    };

private:
	CMineMonster();
	virtual ~CMineMonster() = default;

	virtual SP(CObject) MakeClone(void) override;

	virtual void Awake(void) override;
	virtual void Start(void) override;

	virtual void FixedUpdate(void) override;
	virtual void Update(void) override;
	virtual void LateUpdate(void) override;

	virtual void OnDestroy(void) override;
	virtual void OnEnable(void) override;
	virtual void OnDisable(void) override;

	virtual void SetBasicName(void) override;


private:
	void Chase_Target(_float DeltaTime);
	void Change_State();

	

private:
	MINE_STATE m_eCurState;
	MINE_STATE m_ePreState;

private:
	_float m_fDelay;
};

