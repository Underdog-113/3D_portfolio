#include "stdafx.h"
#include "TextObject.h"

CTextObject::CTextObject()
{
}


CTextObject::~CTextObject()
{
}

SP(CTextObject) CTextObject::Create(_bool isStatic, Engine::CScene * pScene)
{
	SP(CTextObject) spInstance(new CTextObject, Engine::SmartDeleter<CTextObject>);
	spInstance->SetIsStatic(isStatic);
	spInstance->SetScene(pScene);
	spInstance->Awake();

	return spInstance;
}

SP(Engine::CObject) CTextObject::MakeClone(void)
{
	SP(CTextObject) spClone(new CTextObject);
	__super::InitClone(spClone);

	spClone->m_spTransform = spClone->GetComponent<Engine::CTransformC>();
	spClone->m_spGraphics = spClone->AddComponent<Engine::CGraphicsC>();
	spClone->m_spTexture = spClone->AddComponent<Engine::CTextureC>();
	spClone->m_spBitmap = spClone->AddComponent<Engine::CBitmapC>();

	return spClone;
	return SP(CObject)();
}

void CTextObject::Awake(void)
{
	__super::Awake();
	m_layerID = (_int)ELayerID::UI;
}

void CTextObject::Start(void)
{
	__super::Start();
}

void CTextObject::FixedUpdate(void)
{
}

void CTextObject::Update(void)
{

}

void CTextObject::LateUpdate(void)
{
}

void CTextObject::OnDestroy(void)
{
}

void CTextObject::OnEnable(void)
{
}

void CTextObject::OnDisable(void)
{
}

void CTextObject::SetBasicName(void)
{
}
