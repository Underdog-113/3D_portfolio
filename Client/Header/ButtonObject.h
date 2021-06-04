#pragma once
#include"DeleGate.h"

class CButtonObject final : public Engine::CObject
{
public:
	enum Button_Type { UP, Down};
private:
	void (*m_function)();

	_int m_buttonType = 0;
public:
	explicit CButtonObject();
	~CButtonObject();

	// CObject을(를) 통해 상속됨
	static	SP(CButtonObject) Create(_bool isStatic, Engine::CScene* pScene);
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

};

