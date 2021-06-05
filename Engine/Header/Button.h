#ifndef BUTTON_H
#define BUTTON_H

#include "Object.h"
#include "DeleGate.h"
#include "EngineStdafx.h"

BEGIN(Engine)
template<typename T>
class ENGINE_DLL CButton final : public CObject
{
	SMART_DELETER_REGISTER
public:
	enum EButton_Type { UP, Down, Press };
public:
	explicit CButton() {};
	~CButton() {};

private:
	static _uint m_s_uniqueID;

	GETTOR_SETTOR(T, m_functionData, {}, FunctionData);
	Delegate<const int*> m_functionGate;

	GETTOR_SETTOR(EButton_Type, m_buttonType, EButton_Type::UP, ButtonType)

public:
	static SP(CButton<T>) Create(_bool isStatic, CScene* pScene)
	{
		SP(CButton<T>) spInstance(new CButton, SmartDeleter<CButton<T>>);
		spInstance->SetIsStatic(isStatic);
		spInstance->SetScene(pScene);
		spInstance->Awake();

		return spInstance;
	}

	SP(CObject) MakeClone(void) override
	{
		SP(CButton) spClone(new CButton);
		__super::InitClone(spClone);

		spClone->m_spTransform = spClone->GetComponent<CTransformC>();

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

		//CButtonManager::GetInstance()->AddButtonList(this);
	}

	void FixedUpdate(void) override
	{
		__super::FixedUpdate();
	}

	void Update(void) override
	{
		__super::Update();

		FunceActivation();
	}

	void LateUpdate(void) override
	{
		__super::LateUpdate();
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

	void FunceActivation()
	{
	//	m_functionGate(m_functionData);
	}
};
END
#endif
