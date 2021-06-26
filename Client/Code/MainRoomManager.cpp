#include "stdafx.h"
#include "MainRoomManager.h"
#include "DataManager.h"
#include "CaptainData.h"

IMPLEMENT_SINGLETON(CMainRoomManager)
void CMainRoomManager::Start(Engine::CScene * pScene)
{
	pScene->FindObjectByName(L"MainCanvas_Text_0")->GetComponent<Engine::CTextC>()->ChangeMessage(L"LV." + std::to_wstring(CDataManager::GetInstance()->FindCaptainData()->GetLevel()));
	pScene->FindObjectByName(L"MainCanvas_Text_1")->GetComponent<Engine::CTextC>()->ChangeMessage(CDataManager::GetInstance()->FindCaptainData()->GetName());

	// 멕스 벨류 받는다.
	_float maxExp = CDataManager::GetInstance()->FindCaptainData()->GetMaxExperience() / 8;
	_float maxValue = maxExp;
	_float value = CDataManager::GetInstance()->FindCaptainData()->GetExperience();
	for (int i = 0; i <= 7; i++)
	{
		Engine::CSlider* slider = static_cast<Engine::CSlider*>(pScene->FindObjectByName(L"MainCanvas_Slider_" + std::to_wstring(i)).get());
		slider->SetMaxValue(maxValue);
		slider->SetValue(value);
		maxValue += maxExp;
	}

	pScene->FindObjectByName(L"MainCanvas_Text_2")->GetComponent<Engine::CTextC>()->ChangeMessage(std::to_wstring(CDataManager::GetInstance()->FindCaptainData()->GetStamina()));
	pScene->FindObjectByName(L"MainCanvas_Text_3")->GetComponent<Engine::CTextC>()->ChangeMessage(std::to_wstring(CDataManager::GetInstance()->FindCaptainData()->GetGold()));
	pScene->FindObjectByName(L"MainCanvas_Text_4")->GetComponent<Engine::CTextC>()->ChangeMessage(std::to_wstring(CDataManager::GetInstance()->FindCaptainData()->GetDiamond()));
}

void CMainRoomManager::Update(void)
{
}

void CMainRoomManager::OnDestroy(void)
{
}
