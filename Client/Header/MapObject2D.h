#ifndef MAPOBJECT2D_H
#define MAPOBJECT2D_H

#include "Object.h"

class CMapObject2D final : public Engine::CObject
{
	SMART_DELETER_REGISTER
private:
	explicit						CMapObject2D		(void);
								   ~CMapObject2D		(void);

public:
	static		SP(CMapObject2D)	Create				(_bool isStatic, Engine::CScene* pScene);

				SP(CObject)			MakeClone			(void) override;
		
				void				Awake				(void) override;
				void				Start				(void) override;
		
				void				FixedUpdate			(void) override;
				void				Update				(void) override;
				void				LateUpdate			(void) override;
		
				void				PreRender			(LPD3DXEFFECT pEffect) override;
				void				Render				(LPD3DXEFFECT pEffect) override;
				void				PostRender			(LPD3DXEFFECT pEffect) override;

				void				OnDestroy			(void) override;
		
				void				OnEnable			(void) override;
				void				OnDisable			(void) override;

private:
				void				SetBasicName		(void) override;
private:
	static		_uint				m_s_uniqueID;

	GETTOR		(SP(Engine::CRectTexC),		m_spRectTex,		nullptr,	RectTex)
	GETTOR		(SP(Engine::CTextureC),		m_spTexture,		nullptr,	Texture)
	GETTOR		(SP(Engine::CGraphicsC),	m_spGraphics,		nullptr,	Graphics)
	GETTOR		(SP(Engine::CCollisionC),	m_spCollision,		nullptr,	Collision)
	GETTOR		(SP(Engine::CShaderC),		m_spShader,			nullptr,	Shader)
};
#endif