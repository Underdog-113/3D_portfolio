#ifndef BUTTON_H
#define BUTTON_H

#include "Object.h"
#include "DeleGate.h"
BEGIN(Engine)
class ENGINE_DLL CButton final : public CObject
{
	SMART_DELETER_REGISTER
public:
	enum EButton_Type { UP, Down };
public:
	explicit CButton();
	~CButton();

	// CObject을(를) 통해 상속됨
	static	SP(CButton) Create(_bool isStatic, Engine::CScene* pScene);
	SP(Engine::CObject) MakeClone(void) override;
	void Awake(void) override;
	void Start(void) override;
	void FixedUpdate(void) override;
	void Update(void) override;
	void LateUpdate(void) override;
	void OnDestroy(void) override;
	void OnEnable(void) override;
	void OnDisable(void) override;
	void SetBasicName(void) override;
	void aa();
private:

private:
	static _uint m_s_uniqueID;

	/*template<typename T>
	Delegate<const T&> m_functionGate;*/


	EButton_Type m_buttonType = EButton_Type::UP;
};
END
#endif