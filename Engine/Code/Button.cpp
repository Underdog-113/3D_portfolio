#include "EngineStdafx.h"
#include "Button.h"

USING(Engine)
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

void ss()
{
	_int a = 10;
}

void CButton::Start(void)
{
	__super::Start();

	Delegate<> m_functionGatee;
	
	m_functionGatee += std::bind(&CButton::aa, &CButton());
	m_functionGatee += ss;

	m_functionGatee();

	m_functionGatee -= ss;

	m_functionGatee();
}

void CButton::FixedUpdate(void)
{
	__super::FixedUpdate();
}

void CButton::Update(void)
{
	__super::Update();
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

void CButton::aa()
{
	_int a = 10;
}