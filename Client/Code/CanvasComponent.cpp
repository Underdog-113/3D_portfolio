#include "stdafx.h"
#include "CanvasComponent.h"
#include "Layer.h"
#include "Object.h"

CCanvasComponent::CCanvasComponent()
{
}


CCanvasComponent::~CCanvasComponent()
{
}

SP(Engine::CComponent) CCanvasComponent::MakeClone(Engine::CObject *pObject)
{
	SP(CCanvasComponent) spClone(new CCanvasComponent);
	__super::InitClone(spClone, pObject);

	return spClone;
}

void CCanvasComponent::Awake()
{
	__super::Awake();
	m_componentID = 0;
}

void CCanvasComponent::Start(SP(Engine::CComponent) spThis)
{
	__super::Start(spThis);
	FindUi();
}

void CCanvasComponent::FixedUpdate(SP(Engine::CComponent) spThis)
{
}

void CCanvasComponent::Update(SP(Engine::CComponent) spThis)
{
}

void CCanvasComponent::LateUpdate(SP(Engine::CComponent) spThis)
{
}

void CCanvasComponent::OnDestroy()
{
}

void CCanvasComponent::OnEnable()
{
	__super::OnEnable();

}

void CCanvasComponent::OnDisable()
{
	__super::OnDisable();
}

void CCanvasComponent::FindUi()
{
	std::vector<SP(Engine::CObject)> objectlist =  Engine::CSceneManager::GetInstance()->GetCurScene()->GetLayers()[0]->GetGameObjects();
	std::wstring curName = GetOwner()->GetName();
	for (auto object : objectlist)
	{
		std::wstring name = object->GetName();
		// 현재 나의 이름의 크기만큼 name에서 읽어들이자.
		char* ptr = strstr((char*)name.c_str(), (char*)curName.c_str());

		if (ptr[0] == '_')
		{
			m_objectList.emplace_back(object);
		}
	}
}
