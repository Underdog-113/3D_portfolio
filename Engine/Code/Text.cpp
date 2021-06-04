#include "EngineStdafx.h"
#include "Text.h"

USING(Engine)
_uint CText::m_s_uniqueID = 0;
CText::CText()
{
}

CText::~CText()
{
}

SP(CText) CText::Create(_bool isStatic, CScene * pScene)
{
	SP(CText) spInstance(new CText, SmartDeleter<CText>);
	spInstance->SetIsStatic(isStatic);
	spInstance->SetScene(pScene);
	spInstance->Awake();

	return spInstance;
}

SP(Engine::CObject) CText::MakeClone(void)
{
	SP(CText) spClone(new CText);
	__super::InitClone(spClone);

	spClone->m_spTransform = spClone->GetComponent<CTransformC>();
	spClone->m_spText = spClone->GetComponent<CTextC>();

	return spClone;
	return SP(CObject)();
}

void CText::Awake(void)
{
	__super::Awake();
	m_layerID = (_int)ELayerID::UI;	
	m_addExtra = true;
	
	AddComponent<CTextC>();
	AddComponent<CGraphicsC>()->SetRenderID((_int)ERenderID::UI);
}

void CText::Start(void)
{
	__super::Start();
}

void CText::FixedUpdate(void)
{
	__super::FixedUpdate();
}

void CText::Update(void)
{
	__super::Update();
}

void CText::LateUpdate(void)
{
	__super::LateUpdate();
}

void CText::PreRender(void)
{
}

void CText::Render(void)
{
	SP(CTextC) text = GetComponent<CTextC>();
	if (text)
	{
		text->RenderText();
	}
}

void CText::PostRender(void)
{
}

void CText::OnDestroy(void)
{
	__super::OnDestroy();
}

void CText::OnEnable(void)
{
	__super::OnEnable();
}

void CText::OnDisable(void)
{
	__super::OnDisable();
}

void CText::SetBasicName(void)
{
}
