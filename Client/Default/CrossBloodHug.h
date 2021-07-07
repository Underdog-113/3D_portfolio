#pragma once
#ifndef CROSSBLOODHUG_H
#define CROSSBLOODHUG_H


class CCrossBloodHug final : public Engine::CObject
{
	SMART_DELETER_REGISTER

public:
	CCrossBloodHug();
	~CCrossBloodHug();
public:
	static			SP(CCrossBloodHug)		Create(_bool isStatic, Engine::CScene* pScene);

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
	_float m_activeTimer = 0.f;
	_float m_activeDuration = 1.5f;

private:
	_float m_fDissolveAlpha = 1.f;
};



#endif // CROSSBLOODHUG_H
