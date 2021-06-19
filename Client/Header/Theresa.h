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
	static			SP(CTheresa)				Create(_bool isStatic, Engine::CScene* pScene);

public:
					SP(Engine::CObject)		MakeClone			(void) override;
		
					void					Awake				(void) override;
					void					Start				(void) override;
		
					void					FixedUpdate			(void) override;
					void					Update				(void) override;
					void					LateUpdate			(void) override;

					void					PreRender			(LPD3DXEFFECT pEffect) override;
					void					Render				(LPD3DXEFFECT pEffect) override;
					void					PostRender			(LPD3DXEFFECT pEffect) override;
		
					void					OnDestroy			(void) override;
		
					void					OnEnable			(void) override;
					void					OnDisable			(void) override;

					void					SetBasicName		(void) override;
					
public:


private:
	_float m_ultraTimer = 0.f;
	_float m_ultraDuration = 8.f;
};

#endif