#pragma once
#ifndef KIANA_CATPAW_ATK05_H
#define KIANA_CATPAW_ATK05_H

#include "Object.h"

class CKiana_CatPaw_Atk05 final : public Engine::CObject
{
	SMART_DELETER_REGISTER

private:
	CKiana_CatPaw_Atk05();
	~CKiana_CatPaw_Atk05();
	
public:
	static			SP(CKiana_CatPaw_Atk05)		Create(_bool isStatic, Engine::CScene* pScene);

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

private:
	_float m_tempTimer = 0.f;
	_float m_tempDuration = 1.5f;
};


#endif // KIANA_CATPAW_ATK05_H


