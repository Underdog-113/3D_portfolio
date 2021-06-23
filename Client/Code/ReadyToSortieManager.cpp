#include "stdafx.h"
#include "ReadyToSortieManager.h"
#include "DataManager.h"
#include "CaptainData.h"

IMPLEMENT_SINGLETON(CReadyToSortieManager)
void CReadyToSortieManager::Start(Engine::CScene * pScene)
{
	pScene->FindObjectByName(L"MainCanvas_Text_2")->GetComponent<Engine::CTextC>()->ChangeMessage(std::to_wstring(CDataManager::GetInstance()->FindCaptainData()->GetStamina()));
	pScene->FindObjectByName(L"MainCanvas_Text_3")->GetComponent<Engine::CTextC>()->ChangeMessage(std::to_wstring(CDataManager::GetInstance()->FindCaptainData()->GetGold()));
	pScene->FindObjectByName(L"MainCanvas_Text_4")->GetComponent<Engine::CTextC>()->ChangeMessage(std::to_wstring(CDataManager::GetInstance()->FindCaptainData()->GetDiamond()));
}

void CReadyToSortieManager::Update(void)
{
}

void CReadyToSortieManager::OnDestroy(void)
{
}
