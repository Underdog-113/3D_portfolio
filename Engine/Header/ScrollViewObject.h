#ifndef SCROLLVIEW_H
#define SCROLLVIEW_H

#include "Object.h"

BEGIN(Engine)
class CScrollViewObject final : public CObject
{
	SMART_DELETER_REGISTER
public:
	CScrollViewObject();
	~CScrollViewObject();

public:
	// CObject을(를) 통해 상속됨
	static	SP(CScrollViewObject) Create(_bool isStatic, CScene* pScene);
	SP(CObject) MakeClone(void) override;

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

};
END
#endif