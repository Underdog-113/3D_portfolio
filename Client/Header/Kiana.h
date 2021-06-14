#pragma once
#ifndef KIANA_H
#define KIANA_H

#include "Valkyrie.h"

class CFSM_KianaC;
class CKiana final : public CValkyrie
{
	SMART_DELETER_REGISTER

public:
	enum UltraAttack { 
		ATK01, ATK02, ATK03, ATK04, ATK05,
		Branch_ATK01, Branch_ATK02,
		QTE_ATK
	};
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
					void					CreateCatPaw		(void);
					void					SetBasicName		(void) override;

public:
					void					UltraAtk			(UltraAttack index);

private:
	GETTOR			(SP(Engine::CObject),	m_CatPaw_Atk01,		nullptr, CatPaw_Atk01)
	GETTOR			(SP(Engine::CObject),	m_CatPaw_Atk02,		nullptr, CatPaw_Atk02)
	GETTOR			(SP(Engine::CObject),	m_CatPaw_Atk03,		nullptr, CatPaw_Atk03)
	GETTOR			(SP(Engine::CObject),	m_CatPaw_Atk04,		nullptr, CatPaw_Atk04)
	GETTOR			(SP(Engine::CObject),	m_CatPaw_Atk05,		nullptr, CatPaw_Atk05)

	GETTOR_SETTOR	(_bool,					m_ultraMode,		false, UltraMode)

private:

	_float m_ultraTimer = 0.f;
	_float m_ultraDuration = 8.f;
};

#endif