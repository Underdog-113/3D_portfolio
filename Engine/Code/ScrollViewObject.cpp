#include "EngineStdafx.h"
#include "ScrollViewObject.h"
#include "DeviceManager.h"
USING(Engine)
_uint CScrollViewObject::m_s_uniqueID = 0;
CScrollViewObject::CScrollViewObject()
{
}


CScrollViewObject::~CScrollViewObject()
{
}

SP(CScrollViewObject) CScrollViewObject::Create(_bool isStatic, CScene * pScene)
{
	SP(CScrollViewObject) spInstance(new CScrollViewObject, SmartDeleter<CScrollViewObject>);
	spInstance->SetIsStatic(isStatic);
	spInstance->SetScene(pScene);
	spInstance->Awake();

	return spInstance;
}

SP(Engine::CObject) CScrollViewObject::MakeClone(void)
{
	SP(CScrollViewObject) spClone(new CScrollViewObject, SmartDeleter<CScrollViewObject>);
	__super::InitClone(spClone);

	spClone->m_spTransform = spClone->GetComponent<CTransformC>();

	return spClone;
}

void CScrollViewObject::Awake(void)
{
	__super::Awake();
	m_layerID = (_int)ELayerID::UI;
	m_addExtra = true;

}

void CScrollViewObject::Start(void)
{
	__super::Start();
}

void CScrollViewObject::FixedUpdate(void)
{
	__super::FixedUpdate();
}

void CScrollViewObject::Update(void)
{
	__super::Update();
}

void CScrollViewObject::LateUpdate(void)
{
	__super::LateUpdate();
}

void CScrollViewObject::PreRender(void)
{

}

void CScrollViewObject::Render(void)
{

}

void CScrollViewObject::PostRender(void)
{
}

void CScrollViewObject::OnDestroy(void)
{
	__super::OnDestroy();
}

void CScrollViewObject::OnEnable(void)
{
	__super::OnEnable();
}

void CScrollViewObject::OnDisable(void)
{
	__super::OnDisable();
}

void CScrollViewObject::SetBasicName(void)
{
	m_name = m_objectKey + std::to_wstring(m_s_uniqueID++);
}

// 처음 지정위치에서 시작해서 간격만큼 이미지추가
