#include "stdafx.h"
#include "ValkyriegManager.h"
#include "ValkyrieFSM.h"
#include "ValkyrieSelect.h"
#include "ValkyrieProperty.h"
#include "ValkyrieWeapon.h"
#include "ValkyrieLevelUp.h"
#include "ValkyrieWeaponSwap.h"

IMPLEMENT_SINGLETON(CValkyriegManager)
std::wstring CValkyriegManager::g_selectValkyrie = L"";
std::wstring CValkyriegManager::g_oldSelectValkyrie = L"";

void CValkyriegManager::Start(Engine::CScene * pScene)
{
	m_scene = pScene;
	FSMCreate();

	std::wstring stamina = std::to_wstring(CDataManager::GetInstance()->FindCaptainData()->GetStamina()) + L"/" + std::to_wstring(CDataManager::GetInstance()->FindCaptainData()->GetMaxStamina());
	pScene->FindObjectByName(L"MainCanvas_Text_0")->GetComponent<Engine::CTextC>()->ChangeMessage(stamina);
	pScene->FindObjectByName(L"MainCanvas_Text_1")->GetComponent<Engine::CTextC>()->ChangeMessage(std::to_wstring(CDataManager::GetInstance()->FindCaptainData()->GetGold()));
	pScene->FindObjectByName(L"MainCanvas_Text_2")->GetComponent<Engine::CTextC>()->ChangeMessage(std::to_wstring(CDataManager::GetInstance()->FindCaptainData()->GetDiamond()));

}

void CValkyriegManager::Update(void)
{
	/*if(m_valkyrieFSM[m_valkyrieState])
		m_valkyrieFSM[m_valkyrieState]->Update();*/
	// 씬을 넘겨도 해당 부분이 돌고 해당 부분이 댕글리포인터가되서 문제가생김
}

void CValkyriegManager::OnDestroy(void)
{
	for (auto& obj : m_valkyrieFSM)
	{
		delete(obj);
	}
}

void CValkyriegManager::ChangeFSM(STATE state)
{
	m_valkyrieFSM[m_valkyrieState]->End();
	m_valkyrieOldState = m_valkyrieState;
	m_valkyrieState = state;
	m_valkyrieFSM[m_valkyrieState]->Start();
}

void CValkyriegManager::ChangeFSMSelect()
{
	ChangeFSM(STATE::Select);
}

void CValkyriegManager::ChangeFSMProperty()
{
	ChangeFSM(STATE::Property);
}

void CValkyriegManager::ChangeFSMLevelUp()
{
	ChangeFSM(STATE::LevelUp);
}

void CValkyriegManager::ChangeFSMWeapon()
{
	ChangeFSM(STATE::Weapon);
}

void CValkyriegManager::changeFSMWeaponSwap()
{
	ChangeFSM(STATE::WeaponSwap);
}

void CValkyriegManager::FSMCreate()
{
	m_valkyrieFSM[STATE::Select] = new CValkyrieSelect();
	m_valkyrieFSM[STATE::Property] = new CValkyrieProperty();
	m_valkyrieFSM[STATE::Weapon] = new CValkyrieWeapon();
	m_valkyrieFSM[STATE::LevelUp] = new CValkyrieLevelUp();
	m_valkyrieFSM[STATE::WeaponSwap] = new CValkyrieWeaponSwap();
	m_valkyrieFSM[STATE::Select]->Start();
}