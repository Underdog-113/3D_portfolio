#include "stdafx.h"
#include "ImageObject.h"

CImageObject::CImageObject()
{
}

CImageObject::~CImageObject()
{
}

SP(CImageObject) CImageObject::Create(_bool isStatic, Engine::CScene * pScene)
{
	SP(CImageObject) spInstance(new CImageObject, Engine::SmartDeleter<CImageObject>);
	spInstance->SetIsStatic(isStatic);
	spInstance->SetScene(pScene);
	spInstance->Awake();

	return spInstance;
}

SP(Engine::CObject) CImageObject::MakeClone(void)
{
	SP(CImageObject) spClone(new CImageObject);
	__super::InitClone(spClone);

	spClone->m_spTransform = spClone->GetComponent<Engine::CTransformC>();

	return spClone;
	return SP(CObject)();
}

void CImageObject::Awake(void)
{
	__super::Awake();
	m_layerID = (_int)ELayerID::UI;	
	m_addExtra = true;
	
	AddComponent<Engine::CBitmapC>();
	AddComponent<Engine::CGraphicsC>()->SetRenderID((_int)Engine::ERenderID::UI);
	AddComponent<Engine::CTextureC>();
}

void CImageObject::Start(void)
{
	__super::Start();
}

void CImageObject::FixedUpdate(void)
{
	__super::FixedUpdate();
}

void CImageObject::Update(void)
{
	__super::Update();
}

void CImageObject::LateUpdate(void)
{
	__super::LateUpdate();
}

void CImageObject::OnDestroy(void)
{
	__super::OnDestroy();
}

void CImageObject::OnEnable(void)
{
	__super::OnEnable();
}

void CImageObject::OnDisable(void)
{
	__super::OnDisable();
}

void CImageObject::SetBasicName(void)
{
}
