#pragma once
#include "Monster.h"
#include "FSM_SpiderC.h"

class CMO_Spider : public CMonster
{
	SMART_DELETER_REGISTER

private:
	CMO_Spider();
	virtual ~CMO_Spider() = default;

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


private:
	void Chase_Target(_float DeltaTime);

public:
	static		SP(CMO_Spider)			Create(_bool isStatic, Engine::CScene* pScene);

private:
	static		_uint				m_s_uniqueID;

private:
	GETTOR(SP(FSM_SpiderC), m_spFSM, nullptr, FSM)
};

