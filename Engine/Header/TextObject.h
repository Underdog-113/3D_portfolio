#ifndef TEXT_H
#define TEXT_H

#include "Object.h"

BEGIN(Engine)
class ENGINE_DLL CTextObject final : public CObject
{
	SMART_DELETER_REGISTER
private:
	CTextObject();
	~CTextObject();

public:
	// CObject을(를) 통해 상속됨
	static	SP(CTextObject) Create(_bool isStatic, CScene* pScene);
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



private:
	void SetBasicName(void) override;
private:
	static _uint m_s_uniqueID;
	SP(CTextC) m_textC;
	GETTOR(SP(CGraphicsC), m_spGraphics, nullptr, Graphics)

};
END
#endif