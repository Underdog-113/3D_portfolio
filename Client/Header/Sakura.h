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
					void					On8SliceAttack		(void);
					void					Act8SliceAttack		(void);

					void					ActCyclone			(void);
					void					CycloneAttackballUpdate();
public:
	
	GETTOR			(_mat*,					m_pHand_World,		nullptr,	HandWorldMatrix)
	Engine::D3DXFRAME_DERIVED*	m_pHand_Frame = nullptr;
	
	GETTOR			(CAttackBall*,			m_pSubAttackBall,		nullptr, SubAttackBall)

	GETTOR_SETTOR	(_bool,					m_infernoMode,			false,	InfernoMode)
	GETTOR_SETTOR	(_float,				m_infernoTimer,			0.f,	InfernoTimer)

private:
	_uint idx = 0;

private:
	GETTOR			(_bool,					m_8SliceAttack,			false,  8SliceAttack)
	_uint m_8sliceCount = 0;
	_float m_8sliceTimer = 0.f;

	SP(Engine::CObject) m_spCyclone = nullptr;
	_float m_cycloneAttackTimer = 0.f;
	_bool m_cycloneActive = false;
};

#endif