#pragma once
#include "Monster.h"

class CUhlan : public CMonster
{
	SMART_DELETER_REGISTER

private:
	CUhlan();
	virtual ~CUhlan() = default;

public:
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
};

