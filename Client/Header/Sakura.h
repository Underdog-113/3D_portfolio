#pragma once
#ifndef SAKURA_H
#define SAKURA_H


#include "Valkyrie.h"
class CSakura final : public CValkyrie
{
	SMART_DELETER_REGISTER

private:
	CSakura();
	~CSakura();

public:
	static			SP(CSakura)				Create(_bool isStatic, Engine::CScene* pScene);

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

					void					ApplyHitInfo		(HitInfo info) override;
					
public:
					void					UseSkill			(void) override;
					void					UseUltra			(void) override;
public:
	
	GETTOR			(_mat*,					m_pHand_World,		nullptr,	HandWorldMatrix)
	Engine::D3DXFRAME_DERIVED*	m_pHand_Frame = nullptr;

private:
	_uint idx = 0;
};

#endif