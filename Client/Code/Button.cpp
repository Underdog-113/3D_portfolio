#include "Stdafx.h"
#include "ButtonManager.h"
#include "Button.h"

_uint CButton::m_s_uniqueID = 0;
CButton::CButton()
{
}

CButton::~CButton()
{
	OnDestroy();
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
	SP(CButton) spClone(new CButton, Engine::SmartDeleter<CButton>);
	__super::InitClone(spClone);

	spClone->m_spTransform = spClone->GetComponent<Engine::CTransformC>();
	spClone->m_spGraphics = spClone->GetComponent<Engine::CGraphicsC>();
	spClone->m_spTexture = spClone->GetComponent<Engine::CTextureC>();
	spClone->m_spRectTex = spClone->GetComponent<Engine::CRectTexC>();

	return spClone;
}

void CButton::Awake(void)
{
	__super::Awake();
	m_layerID = (_int)ELayerID::UI;
	m_addExtra = true;

	(m_spRectTex = AddComponent<Engine::CRectTexC>())->SetIsOrtho(true);
	(m_spGraphics = AddComponent<Engine::CGraphicsC>())->SetRenderID((_int)Engine::ERenderID::UI);
	m_spTexture = AddComponent<Engine::CTextureC>();
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
}

void CButton::LateUpdate(void)
{
	__super::LateUpdate();
}

void CButton::PreRender(void)
{
	if (!m_spTexture->GetTexData().empty())
	{
		m_spRectTex->PreRender(m_spGraphics);
	}
}

void CButton::Render(void)
{
	if (!m_spTexture->GetTexData().empty())
	{
		m_spRectTex->Render(m_spGraphics);
	}

	SP(Engine::CTextC) spTextC = GetComponent<Engine::CTextC>();

	if (spTextC)
	{
		spTextC->Render(m_spGraphics);
	}
}

void CButton::PostRender(void)
{
	if (!m_spTexture->GetTexData().empty())
	{
		m_spRectTex->PostRender(m_spGraphics);
	}
}

void CButton::OnDestroy(void)
{
	__super::OnDestroy();
	m_functionGate.clear();
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
	m_name = m_objectKey + std::to_wstring(m_s_uniqueID++);
}

void CButton::FuncActivation()
{
	m_functionGate();
}