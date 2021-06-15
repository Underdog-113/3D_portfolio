#ifndef SKYBOX_H
#define SKYBOX_H

#include "Object.h"

BEGIN(Engine)
class ENGINE_DLL CSkyBox final : public CObject
{
	SMART_DELETER_REGISTER
private:
	explicit						CSkyBox				(void);
								   ~CSkyBox				(void);

public:
	static		SP(CSkyBox)			Create				(_bool isStatic, CScene* pScene);

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

	GETTOR		(SP(CCubeTexC),		m_spCubeTex,		nullptr,	CubeTex)
	GETTOR		(SP(CTextureC),		m_spTexture,		nullptr,	Texture)
	GETTOR		(SP(CGraphicsC),	m_spGraphics,		nullptr,	Graphics)
	GETTOR		(SP(CShaderC),		m_spShader,			nullptr,	Shader)
};
END
#endif