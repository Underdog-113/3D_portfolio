#pragma once
#ifndef KIANA_PISTOL_H
#define KIANA_PISTOL_H

#include "Object.h"

class CKiana_Pistol : public Engine::CObject
{
	SMART_DELETER_REGISTER

public:
	CKiana_Pistol();
	~CKiana_Pistol();

	
public:
	static			SP(CKiana_Pistol)		Create(_bool isStatic, Engine::CScene* pScene);

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

};



#endif
