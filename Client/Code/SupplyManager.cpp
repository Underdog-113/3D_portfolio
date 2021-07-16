#include "stdafx.h"
#include "SupplyManager.h"
#include "ValkyrieFSM.h"

#include "SupplyWapon.h"
#include "SupplyItem.h"
#include "SupplyOut.h"

IMPLEMENT_SINGLETON(CSupplyManager)
void CSupplyManager::Start(Engine::CScene * pScene)
{
	m_scene = pScene;
	FSMCreate();

	std::wstring stamina = std::to_wstring(CDataManager::GetInstance()->FindCaptainData()->GetStamina()) + L"/" + std::to_wstring(CDataManager::GetInstance()->FindCaptainData()->GetMaxStamina());
	pScene->FindObjectByName(L"MainCanvas_Text_2")->GetComponent<Engine::CTextC>()->ChangeMessage(stamina);
	pScene->FindObjectByName(L"MainCanvas_Text_3")->GetComponent<Engine::CTextC>()->ChangeMessage(std::to_wstring(CDataManager::GetInstance()->FindCaptainData()->GetGold()));
	pScene->FindObjectByName(L"MainCanvas_Text_4")->GetComponent<Engine::CTextC>()->ChangeMessage(std::to_wstring(CDataManager::GetInstance()->FindCaptainData()->GetDiamond()));

	pScene->FindObjectByName(L"OutCanvas")->SetIsEnabled(false);
	pScene->FindObjectByName(L"SelectCanvas")->SetIsEnabled(false);
}

void CSupplyManager::Update(void)
{
	if(m_supplyFSM[m_supplyState] != NULL)
		m_supplyFSM[m_supplyState]->Update();
}

void CSupplyManager::OnDestroy(void)
{
	for (auto& obj : m_supplyFSM)
	{
		delete(obj);
	}
}

void CSupplyManager::SupplyWeaponFSM()
{
	ChangeFSM(STATE::Weapon);
}

void CSupplyManager::SupplyItemFSM()
{
	ChangeFSM(STATE::Item);
}

void CSupplyManager::SupplyOutFSM()
{
	Engine::GET_CUR_SCENE->FindObjectByName(L"SelectCanvas")->SetIsEnabled(false);
	ChangeFSM(STATE::Out);
}

void CSupplyManager::SelectCanvasOff()
{
	Engine::GET_CUR_SCENE->FindObjectByName(L"SelectCanvas")->SetIsEnabled(false);
}

void CSupplyManager::ChangeFSM(STATE state)
{
	if (state == m_supplyState)
		return;

	m_supplyFSM[m_supplyState]->End();
	m_supplyOldState = m_supplyState;
	m_supplyState = state;
	m_supplyFSM[m_supplyState]->Start();
}

void CSupplyManager::FSMCreate()
{
	m_supplyFSM[STATE::Weapon] = new CSupplyWapon;
	m_supplyFSM[STATE::Item] = new CSupplyItem;
	m_supplyFSM[STATE::Out] = new CSupplyOut;
	m_supplyFSM[STATE::Weapon]->Start();
}