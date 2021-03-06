#pragma once
#ifndef KIANA_CatPaw_Ring_ATK01_H
#define KIANA_CatPaw_Ring_ATK01_H

#include "Object.h"

class CKiana_CatPaw_Ring_Atk01 final : public Engine::CObject
{
	SMART_DELETER_REGISTER

private:
	CKiana_CatPaw_Ring_Atk01();
	~CKiana_CatPaw_Ring_Atk01();
	
public:
	static			SP(CKiana_CatPaw_Ring_Atk01)		Create(_bool isStatic, Engine::CScene* pScene);

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

};


#endif // KIANA_CatPaw_Ring_ATK01_H


