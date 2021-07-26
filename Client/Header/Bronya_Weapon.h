#pragma once
#ifndef BRONYAWEAPON_H
#define BRONYAWEAPON_H

#include "Object.h"

class CBronya_Weapon : public Engine::CObject
{
	SMART_DELETER_REGISTER

public:
	CBronya_Weapon();
	~CBronya_Weapon();

	
public:
	static			SP(CBronya_Weapon)		Create(_bool isStatic, Engine::CScene* pScene);

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
					
public:
					void					SetBasicName		(void) override;

protected:
	static			_uint							m_s_uniqueID;
	GETTOR			(SP(Engine::CMeshC),			m_spMesh,			nullptr,	Mesh)
	GETTOR			(SP(Engine::CTextureC),			m_spTexture,		nullptr,	Texture)
	GETTOR			(SP(Engine::CGraphicsC),		m_spGraphics,		nullptr,	Graphics)
	GETTOR			(SP(Engine::CShaderC),			m_spShader,			nullptr,	Shader)
		
	GETTOR_SETTOR	(_mat*,							m_pParentMatrix,	nullptr,	ParentMatrix)
	GETTOR			(SP(Engine::CObject),			m_spSexdngud,		nullptr,	TestObj)

public:
	GETTOR_SETTOR(_float, m_fAlpha, 1.f, Alpha)
};



#endif
