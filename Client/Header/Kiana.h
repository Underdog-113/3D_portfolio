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
	static			SP(CKiana)				Create(_bool isStatic, Engine::CScene* pScene);

public:
					SP(Engine::CObject)		MakeClone			(void) override;
		
					void					Awake				(void) override;
					void					Start				(void) override;
		
					void					FixedUpdate			(void) override;
					void					Update				(void) override;
					void					LateUpdate			(void) override;

					void					PreRender			(void) override;
					void					PreRender			(LPD3DXEFFECT pEffect) override;

					void					Render				(void) override;
					void					Render				(LPD3DXEFFECT pEffect) override;

					void					PostRender			(void) override;
					void					PostRender			(LPD3DXEFFECT pEffect) override;
		
					void					OnDestroy			(void) override;
		
					void					OnEnable			(void) override;
					void					OnDisable			(void) override;

public:
					void					SetBasicName		(void) override;

private:
	GETTOR			(SP(Engine::CObject),	m_CatPaw_Atk01,		nullptr, CatPaw_Atk01)

};

#endif