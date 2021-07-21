#ifndef CANVAS_H
#define CANVAS_H

#include "Object.h"

BEGIN(Engine)
class ENGINE_DLL CCanvas final : public CObject
{
public:
	SMART_DELETER_REGISTER
private:
	CCanvas();
	~CCanvas();

public:
	// CObject을(를) 통해 상속됨
	static	SP(CCanvas) Create(_bool isStatic, CScene* pScene);
	SP(CObject) MakeClone(void) override;

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

	void AddObjectFind();
	void SetEnableCanvasMember(std::wstring name, _bool value);
private:
	void SetBasicName(void) override;
private:
	static _uint m_s_uniqueID;

	GETTOR(std::list<CObject*>, m_spObjectList, {}, ObjectList);
};
END
#endif