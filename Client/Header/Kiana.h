#pragma once
#ifndef KIANA_H
#define KIANA_H

#include "Valkyrie.h"

class CFSM_KianaC;
class CKiana final : public CValkyrie
{
	SMART_DELETER_REGISTER

private:
	CKiana();
	~CKiana();

public:
	static		SP(CKiana)			Create(_bool isStatic, Engine::CScene* pScene);

public:
					SP(Engine::CObject)		MakeClone			(void) override;
		
					void			Awake				(void) override;
					void			Start				(void) override;
		
					void			FixedUpdate			(void) override;
					void			Update				(void) override;
					void			LateUpdate			(void) override;

					void			PreRender			(void);
					void			PreRender			(LPD3DXEFFECT pEffect);

					void			Render				(void);
					void			Render				(LPD3DXEFFECT pEffect);

					void			PostRender			(void);
					void			PostRender			(LPD3DXEFFECT pEffect);
		
					void			OnDestroy			(void) override;
		
					void			OnEnable			(void) override;
					void			OnDisable			(void) override;

public:
					void			SetBasicName		(void) override;

};

#endif