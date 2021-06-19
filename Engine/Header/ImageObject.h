#ifndef IMAGE_H
#define IMAGE_H

#include "Object.h"

BEGIN(Engine)
class ENGINE_DLL CImageObject final : public CObject
{
	SMART_DELETER_REGISTER
private:
	CImageObject();
	~CImageObject();

public:
	// CObject을(를) 통해 상속됨
	static	SP(CImageObject) Create(_bool isStatic, CScene* pScene);
	SP(Engine::CObject) MakeClone(void) override;

	void Awake(void) override;
	void Start(void) override;

	void FixedUpdate(void) override;
	void Update(void) override;
	void LateUpdate(void) override;

	void PreRender(LPD3DXEFFECT pEffect) override;
	void Render(LPD3DXEFFECT pEffect) override;
	void PostRender(LPD3DXEFFECT pEffect) override;

	void OnDestroy(void) override;

	void OnEnable(void) override;
	void OnDisable(void) override;

	

private:
	void SetBasicName(void) override;
private:
	static _uint m_s_uniqueID;

	GETTOR(SP(CGraphicsC), m_spGraphics, nullptr, Graphics)
	GETTOR(SP(CTextureC), m_spTexture, nullptr, Texture)
	GETTOR(SP(CRectTexC), m_spRectTex, nullptr, RectTex)
	GETTOR(SP(CShaderC), m_spShader, nullptr, Shader)
};
END
#endif