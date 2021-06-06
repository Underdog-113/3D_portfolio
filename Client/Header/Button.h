#ifndef BUTTON_H
#define BUTTON_H

#include "Object.h"
#include "DeleGate.h"
class CButton final : public Engine::CObject
{
public:
	enum EButton_Type { UP, Down, Press };
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

	void FunceActivation();
private:

private:
	static _uint m_s_uniqueID;
	GETTOR_SETTOR(EButton_Type, m_buttonType, EButton_Type::UP, ButtonType);

	Delegate<> m_functionGate;

};
#endif

/*
누군가는 특정상황에 델리게이트를 실행시켜줘야함
1. 버튼컴포넌트에 따라 실행되는조건이다름
2. 마우스 한번클릭당 하나의 오브젝트의 버튼만 실행됨
3.

버튼매니저가 모든 버튼컴포넌트를 가지고있는다.
마우스가 행동을하면 그에 맞게 함수를실행한다.
행동시작하고 버튼컴포넌트의 순위따라 실행한다.
*/