#ifndef BUTTON_H
#define BUTTON_H

#include "Object.h"
#include "DeleGate.h"

template <typename T = float>
class CButton final : public Engine::CObject
{
	SMART_DELETER_REGISTER
public:
	enum EButton_Type { UP, Down, Press };
public:
	explicit CButton() {};
	~CButton() {};
private:

private:
	static _uint m_s_uniqueID;
	GETTOR_SETTOR(EButton_Type, m_buttonType, EButton_Type::UP, ButtonType);

public:
	Delegate<> m_functionGateVoid;
	Delegate<const T&> m_functionGate;
	GETTOR_SETTOR(T, m_functionDate, {}, FunctionDate);

public:
	// CObject을(를) 통해 상속됨
	static	SP(CButton<T>) Create(_bool isStatic, Engine::CScene* pScene)
	{
		SP(CButton<T>) spInstance(new CButton<T>, Engine::SmartDeleter<CButton<>>);
		spInstance->SetIsStatic(isStatic);
		spInstance->SetScene(pScene);
		spInstance->Awake();

		return spInstance;
	}

	SP(Engine::CObject) MakeClone(void) override
	{
		SP(CButton<T>) spClone(new CButton<T>);
		__super::InitClone(spClone);

		spClone->m_spTransform = spClone->GetComponent<Engine::CTransformC>();

		return spClone;
		return SP(CObject)();
	}
	 
	void Awake(void) override
	{
		__super::Awake();
		m_layerID = (_int)ELayerID::UI;
		m_addExtra = true;
	}

	void Start(void) override
	{
		__super::Start();
	}
	void FixedUpdate(void) override
	{
		__super::FixedUpdate();
	}

	void Update(void) override
	{
		__super::Update();
	}

	void LateUpdate(void) override
	{
		__super::LateUpdate();

		Function();
	}

	void OnDestroy(void) override
	{
		__super::OnDestroy();
	}

	void OnEnable(void) override
	{
		__super::OnEnable();
	}

	void OnDisable(void) override
	{
		__super::OnDisable();
	}

	void SetBasicName(void) override
	{

	}

	void Function()
	{
		if (m_functionDate)
			m_functionGateVoid();
		else
			m_functionGate(m_functionDate);
	}

	void FuncitionInit(T funcition)
	{

	}

	void FuncitionInit()
	{

	}
};
#endif

/*
m_functionGate 외부에서 델리게이트 다시정의해서 넣어준다.
m_functionData 외부에서 델리게이트의 맞는 값을 넣어준다. 잘못넣어주면 주옥된다.
*/