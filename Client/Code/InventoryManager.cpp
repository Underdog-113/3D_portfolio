#include "stdafx.h"
#include "InventoryManager.h"
#include "ValkyrieFSM.h"

#include "WaponItem.h"
#include "stuffItem.h"

IMPLEMENT_SINGLETON(CInventoryManager)
void CInventoryManager::Start(Engine::CScene * pScene)
{
	m_scene = pScene;
	FSMCreate();

	std::wstring stamina = std::to_wstring(CDataManager::GetInstance()->FindCaptainData()->GetStamina()) + L"/" + std::to_wstring(CDataManager::GetInstance()->FindCaptainData()->GetMaxStamina());
	pScene->FindObjectByName(L"MainCanvas_Text_2")->GetComponent<Engine::CTextC>()->ChangeMessage(stamina);
	pScene->FindObjectByName(L"MainCanvas_Text_3")->GetComponent<Engine::CTextC>()->ChangeMessage(std::to_wstring(CDataManager::GetInstance()->FindCaptainData()->GetGold()));
	pScene->FindObjectByName(L"MainCanvas_Text_4")->GetComponent<Engine::CTextC>()->ChangeMessage(std::to_wstring(CDataManager::GetInstance()->FindCaptainData()->GetDiamond()));

}

void CInventoryManager::Update(void)
{
	/*if(m_valkyrieFSM[m_valkyrieState])
	m_valkyrieFSM[m_valkyrieState]->Update();*/
	// 씬을 넘겨도 해당 부분이 돌고 해당 부분이 댕글리포인터가되서 문제가생김
}

void CInventoryManager::OnDestroy(void)
{
	for (auto& obj : m_inventoryFSM)
	{
		delete(obj);
	}
}

void CInventoryManager::WeaponFSM()
{
	ChangeFSM(STATE::Weapon);
}

void CInventoryManager::ItemFSM()
{
	ChangeFSM(STATE::Item);
}

void CInventoryManager::ChangeFSM(STATE state)
{
	m_inventoryFSM[m_inventoryState]->End();
	m_inventoryOldState = m_inventoryState;
	m_inventoryState = state;
	m_inventoryFSM[m_inventoryState]->Start();
}

void CInventoryManager::FSMCreate()
{
	m_inventoryFSM[STATE::Weapon] = new CWaponItem;
	m_inventoryFSM[STATE::Item] = new CStuffItem;
	m_inventoryFSM[STATE::Weapon]->Start();
}