#pragma once
#include "Monster.h"

class CMO_Robot : public CMonster
{
	SMART_DELETER_REGISTER

private:
	CMO_Robot();
	virtual ~CMO_Robot() = default;

public:
	virtual SP(CObject) MakeClone(void) override;

	virtual void Awake(void) override;

	virtual void Start(void) override;

	virtual void FixedUpdate(void) override;

	virtual void Update(void) override;

	virtual void LateUpdate(void) override;

	virtual void PreRender(void) override;
	virtual void Render(void) override;
	virtual void PostRender(void) override;

	virtual void OnDestroy(void) override;

	virtual void OnEnable(void) override;

	virtual void OnDisable(void) override;

	virtual void SetBasicName(void) override;

public:
	static		SP(CMO_Robot)			Create(_bool isStatic, Engine::CScene* pScene);

};

