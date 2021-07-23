#include "stdafx.h"
#include "..\Header\DropItemManager.h"

IMPLEMENT_SINGLETON(CDropItemManager)

void CDropItemManager::Start(Engine::CScene * pScene)
{

}

void CDropItemManager::Update(void)
{

}

void CDropItemManager::OnDestroy(void)
{

}

void CDropItemManager::AllDelete()
{
	m_itemList.clear();
	m_gold = 0;
	m_captainExp = 0;
	m_valkyrieExp = 0;
}

void CDropItemManager::AddItemList(ItemSave item)
{
	for (auto& obj : m_itemList)
	{
		if (obj.itemName == item.itemName)
		{
			obj.count++;
			return;
		}
	}
	m_itemList.emplace_back(item);
}
