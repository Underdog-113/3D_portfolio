#pragma once
#include "Monster.h"
#include "FSM_SpiderC.h"

class CMO_Spider : public CMonster
{
	SMART_DELETER_REGISTER

private:
	CMO_Spider();
	~CMO_Spider();

public:
	virtual			SP(CObject)				MakeClone		(void) override;

	virtual			void					Awake			(void) override;
	virtual			void					Start			(void) override;

	virtual			void					FixedUpdate		(void) override;
	virtual			void					Update			(void) override;
	virtual			void					LateUpdate		(void) override;

	virtual			void					PreRender		(void) override;
	virtual			void					PreRender		(LPD3DXEFFECT pEffect) override;

	virtual			void					Render			(void) override;
	virtual			void					Render			(LPD3DXEFFECT pEffect) override;

	virtual			void					PostRender		(void) override;
	virtual			void					PostRender		(LPD3DXEFFECT pEffect) override;

	virtual			void					OnDestroy		(void) override;
	virtual			void					OnEnable		(void) override;
	virtual			void					OnDisable		(void) override;

	virtual			void					SetBasicName	(void) override;


private:
	void Chase_Target(_float3 targetPos);

public:
	static		SP(CMO_Spider)			Create(_bool isStatic, Engine::CScene* pScene);

private:
	static		_uint				m_s_uniqueID;

//private:
//	GETTOR(SP(FSM_SpiderC), m_spFSM, nullptr, FSM)//이거 나중에 지워 알게찌?
};

