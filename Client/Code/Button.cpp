#include "Stdafx.h"
#include "ButtonManager.h"
#include "Button.h"

_uint CButton::m_s_uniqueID = 0;
CButton::CButton()
{
}

CButton::~CButton()
{
}

SP(CButton) CButton::Create(_bool isStatic, Engine::CScene * pScene)
{
	SP(CButton) spInstance(new CButton, Engine::SmartDeleter<CButton>);
	spInstance->SetIsStatic(isStatic);
	spInstance->SetScene(pScene);
	spInstance->Awake();

	return spInstance;
}

SP(Engine::CObject) CButton::MakeClone(void)
{
	SP(CButton) spClone(new CButton);
	__super::InitClone(spClone);

	spClone->m_spTransform = spClone->GetComponent<Engine::CTransformC>();

	return spClone;
	return SP(CObject)();
}

void CButton::Awake(void)
{
	__super::Awake();
	m_layerID = (_int)ELayerID::UI;
	m_addExtra = true;

}

void CButton::Start(void)
{
	__super::Start();

	CButtonManager::GetInstance()->AddButtonList(this);
}


void CButton::FixedUpdate(void)
{
	__super::FixedUpdate();
}

void CButton::Update(void)
{
	__super::Update();

	// 키가눌렸는지 체크
	// 자기 타입에 맞게 키가눌리면 실행
	// 한번 
}

void CButton::LateUpdate(void)
{
	__super::LateUpdate();
}


void CButton::OnDestroy(void)
{
	__super::OnDestroy();
}

void CButton::OnEnable(void)
{
	__super::OnEnable();
}

void CButton::OnDisable(void)
{
	__super::OnDisable();
}

void CButton::SetBasicName(void)
{
}

void CButton::FunceActivation()
{
	m_functionGate();
}

/*
Delegate<> m_functionGatee;

m_functionGatee += std::bind(&CButton::aa, &CButton());
m_functionGatee += ss;

m_functionGatee();

m_functionGatee -= ss;

m_functionGatee();
*/