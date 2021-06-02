#include "stdafx.h"
#include "CanvaseComponent.h"
#include "Layer.h"
#include "Object.h"

CCanvaseComponent::CCanvaseComponent()
{
}


CCanvaseComponent::~CCanvaseComponent()
{
}

SP(Engine::CComponent) CCanvaseComponent::MakeClone(Engine::CObject *pObject)
{
	SP(CCanvaseComponent) spClone(new CCanvaseComponent);
	__super::InitClone(spClone, pObject);

	return spClone;
}

void CCanvaseComponent::Awake()
{
	__super::Awake();
	m_componentID = 0;
}

void CCanvaseComponent::Start(SP(Engine::CComponent) spThis)
{
	__super::Start(spThis);
	FindUi();
}

void CCanvaseComponent::FixedUpdate(SP(Engine::CComponent) spThis)
{
}

void CCanvaseComponent::Update(SP(Engine::CComponent) spThis)
{
}

void CCanvaseComponent::LateUpdate(SP(Engine::CComponent) spThis)
{
}

void CCanvaseComponent::OnDestroy()
{
}

void CCanvaseComponent::OnEnable()
{
	__super::OnEnable();

}

void CCanvaseComponent::OnDisable()
{
	__super::OnDisable();
}

void CCanvaseComponent::FindUi()
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
