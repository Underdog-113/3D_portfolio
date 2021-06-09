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

	void PreRender(void) override;
	void Render(void) override;
	void PostRender(void) override;

	void OnDestroy(void) override;

	void OnEnable(void) override;
	void OnDisable(void) override;

private:
	void SetBasicName(void) override;
	void AddObjectFind();
private:
	static _uint m_s_uniqueID;

	std::list<SP(CObject)> m_spObjectList;
};
END
#endif