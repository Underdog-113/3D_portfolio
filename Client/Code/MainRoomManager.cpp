#include "stdafx.h"
#include "MainRoomManager.h"
#include "DataManager.h"
#include "CaptainData.h"

IMPLEMENT_SINGLETON(CMainRoomManager)
void CMainRoomManager::Start(Engine::CScene * pScene)
{
	pScene->FindObjectByName(L"MainCanvas_Text_0")->GetComponent<Engine::CTextC>()->ChangeMessage(L"LV." + std::to_wstring(CDataManager::GetInstance()->FindCaptainData()->GetLevel()));
	pScene->FindObjectByName(L"MainCanvas_Text_1")->GetComponent<Engine::CTextC>()->ChangeMessage(CDataManager::GetInstance()->FindCaptainData()->GetName());
}

void CMainRoomManager::Update(void)
{
}

void CMainRoomManager::OnDestroy(void)
{
}
