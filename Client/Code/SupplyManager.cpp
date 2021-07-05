#include "stdafx.h"
#include "SupplyManager.h"
#include "ValkyrieFSM.h"

#include "SupplyWapon.h"
#include "SupplyItem.h"

IMPLEMENT_SINGLETON(CSupplyManager)
void CSupplyManager::Start(Engine::CScene * pScene)
{
	m_scene = pScene;
	FSMCreate();

	std::wstring stamina = std::to_wstring(CDataManager::GetInstance()->FindCaptainData()->GetStamina()) + L"/" + std::to_wstring(CDataManager::GetInstance()->FindCaptainData()->GetMaxStamina());
	pScene->FindObjectByName(L"MainCanvas_Text_2")->GetComponent<Engine::CTextC>()->ChangeMessage(stamina);
	pScene->FindObjectByName(L"MainCanvas_Text_3")->GetComponent<Engine::CTextC>()->ChangeMessage(std::to_wstring(CDataManager::GetInstance()->FindCaptainData()->GetGold()));
	pScene->FindObjectByName(L"MainCanvas_Text_4")->GetComponent<Engine::CTextC>()->ChangeMessage(std::to_wstring(CDataManager::GetInstance()->FindCaptainData()->GetDiamond()));

}

void CSupplyManager::Update(void)
{
	
}

void CSupplyManager::OnDestroy(void)
{
	for (auto& obj : m_supplyFSM)
	{
		delete(obj);
	}
}

void CSupplyManager::WeaponFSM()
{
	ChangeFSM(STATE::Weapon);
}

void CSupplyManager::ItemFSM()
{
	ChangeFSM(STATE::Item);
}

void CSupplyManager::ChangeFSM(STATE state)
{
	m_supplyFSM[m_supplyState]->End();
	m_supplyOldState = m_supplyState;
	m_supplyState = state;
	m_supplyFSM[m_supplyState]->Start();
}

void CSupplyManager::FSMCreate()
{
	m_supplyFSM[STATE::Weapon] = new CSupplyWapon;
	m_supplyFSM[STATE::Item] = new CSupplyItem;
	m_supplyFSM[STATE::Weapon]->Start();
}