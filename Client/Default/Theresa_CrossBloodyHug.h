#pragma once
#ifndef CROSSBLOODHUG_H
#define CROSSBLOODHUG_H

#include "Object.h"

class CTheresa_CrossBlade;
class CTheresa_CrossBloodyHug final : public Engine::CObject
{
	SMART_DELETER_REGISTER

public:
	CTheresa_CrossBloodyHug();
	~CTheresa_CrossBloodyHug();
public:
	static			SP(CTheresa_CrossBloodyHug)		Create(_bool isStatic, Engine::CScene* pScene);

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
	GETTOR			(SP(Engine::CObject),			m_spCrossBlade,		nullptr,	CrossBlade)

	_float m_activeTimer = 0.f;
	_float m_activeDuration = 2.f;

private:
	_float m_fDissolveAlpha = 1.f;
};



#endif // CROSSBLOODHUG_H
