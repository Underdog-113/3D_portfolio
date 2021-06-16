#include "EngineStdafx.h"
#include "TextObject.h"

USING(Engine)
_uint CTextObject::m_s_uniqueID = 0;
CTextObject::CTextObject()
{
}

CTextObject::~CTextObject()
{
	OnDestroy();
}

SP(CTextObject) CTextObject::Create(_bool isStatic, CScene * pScene)
{
	SP(CTextObject) spInstance(new CTextObject, SmartDeleter<CTextObject>);
	spInstance->SetIsStatic(isStatic);
	spInstance->SetScene(pScene);
	spInstance->Awake();

	return spInstance;
}

SP(Engine::CObject) CTextObject::MakeClone(void)
{
	SP(CTextObject) spClone(new CTextObject, SmartDeleter<CTextObject>);
	__super::InitClone(spClone);

	spClone->m_spTransform = spClone->GetComponent<CTransformC>();
	spClone->m_spGraphics = spClone->GetComponent<CGraphicsC>();

	return spClone;
}

void CTextObject::Awake(void)
{
	__super::Awake();
	m_layerID = (_int)ELayerID::Decoration;
	m_dataID = UNDEFINED;
	m_addExtra = true;

	(m_spGraphics = AddComponent<CGraphicsC>())->SetRenderID((_int)ERenderID::UI);

}

void CTextObject::Start(void)
{
	__super::Start();
	m_textC = GetComponent<CTextC>();
}

void CTextObject::FixedUpdate(void)
{
	__super::FixedUpdate();
}

void CTextObject::Update(void)
{
	__super::Update();
}

void CTextObject::LateUpdate(void)
{
	__super::LateUpdate();
}

void CTextObject::PreRender(void)
{
	m_textC->PreRender(m_spGraphics);
}

void CTextObject::Render(void)
{
	m_textC->Render(m_spGraphics);
}

void CTextObject::PostRender(void)
{
	m_textC->PostRender(m_spGraphics);
}

void CTextObject::OnDestroy(void)
{
	__super::OnDestroy();
}

void CTextObject::OnEnable(void)
{
	__super::OnEnable();
}

void CTextObject::OnDisable(void)
{
	__super::OnDisable();
}

void CTextObject::SetBasicName(void)
{
	m_name = m_objectKey + std::to_wstring(m_s_uniqueID++);
}
