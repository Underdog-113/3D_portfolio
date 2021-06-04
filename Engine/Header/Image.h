#ifndef IMAGE_H
#define IMAGE_H

#include "Object.h"

BEGIN(Engine)
class ENGINE_DLL CImage final : public CObject
{
	SMART_DELETER_REGISTER
public:
	CImage();
	~CImage();

	// CObject을(를) 통해 상속됨
	static	SP(CImage) Create(_bool isStatic, Engine::CScene* pScene);
	SP(Engine::CObject) MakeClone(void) override;
	void Awake(void) override;
	void Start(void) override;
	void FixedUpdate(void) override;
	void Update(void) override;
	void LateUpdate(void) override;
	void PreRender(void) override;
	void Render(void) override;
	void PostRender(void) override;
	void OnDestroy(void) override;
	void OnEnable(void) override;
	void OnDisable(void) override;
	void SetBasicName(void) override;

private:

private:
	static _uint m_s_uniqueID;

	GETTOR(SP(Engine::CGraphicsC), m_spGraphics, {}, Graphics);
	GETTOR(SP(Engine::CTextureC), m_spTexture, {}, Texture);
	GETTOR(SP(Engine::CRectTexC), m_spRectTex, {}, RectTex);
};
END
#endif