#pragma once
#include "Object.h"
class Kiana final : public Engine::CObject
{
	SMART_DELETER_REGISTER

public:
	Kiana();
	~Kiana();

public:
	virtual			SP(CObject)		MakeClone			(void) override;
		
	virtual			void			Awake				(void) override;
	virtual			void			Start				(void) override;
	
	virtual			void			FixedUpdate			(void) override;
	virtual			void			Update				(void) override;
	virtual			void			LateUpdate			(void) override;

	virtual			void			PreRender			(void) {}
	virtual			void			PreRender			(LPD3DXEFFECT pEffect) {}

	virtual			void			Render				(void) {}
	virtual			void			Render				(LPD3DXEFFECT pEffect) {}

	virtual			void			PostRender			(void) {}
	virtual			void			PostRender			(LPD3DXEFFECT pEffect) {}
	
	virtual			void			OnDestroy			(void) override;
	
	virtual			void			OnEnable			(void) override;
	virtual			void			OnDisable			(void) override;

public:
	virtual			void			SetBasicName		(void) override;
};