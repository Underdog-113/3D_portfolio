#pragma once
#ifndef THERESA_H
#define THERESA_H


#include "Valkyrie.h"
class CTheresa final : public CValkyrie
{
	SMART_DELETER_REGISTER

private:
	CTheresa();
	~CTheresa();

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

					void					SetBasicName		(void) override;
					
public:
					void					Update_WeaponTransform(void);

					void					CreatePistol		(void);
					void					CreateCatPaw		(void);
					void					UltraAtk			(UltraAttack index);
					void					UltraAtk_Ring		(UltraAttack index);


private:
	_float m_ultraTimer = 0.f;
	_float m_ultraDuration = 8.f;
};

#endif