#include "stdafx.h"
#include "MainRoomManager.h"
#include "DataManager.h"
#include "CaptainData.h"

IMPLEMENT_SINGLETON(CMainRoomManager)
void CMainRoomManager::Start(Engine::CScene * pScene)
{
	Engine::CObject* aa = pScene->GetObjectFactory()->AddClone(L"KianaUIAnim", true, (_int)ELayerID::Player, L"").get();
	aa->GetComponent<Engine::CTransformC>()->SetPosition(_float3(-0.31f, -0.64f, -2.9f));
	aa->GetComponent<Engine::CTransformC>()->SetRotation(_float3(0, 110, 0));
	aa->GetComponent<Engine::CTransformC>()->SetSize(_float3(0.5f, 0.5f, 0.5f));

	pScene->FindObjectByName(L"MainCanvas_Text_0")->GetComponent<Engine::CTextC>()->ChangeMessage(L"LV." + std::to_wstring(CDataManager::GetInstance()->FindCaptainData()->GetLevel()));
	pScene->FindObjectByName(L"MainCanvas_Text_1")->GetComponent<Engine::CTextC>()->ChangeMessage(CDataManager::GetInstance()->FindCaptainData()->GetName());

	// 멕스 벨류 받는다.
	_float maxExp = CDataManager::GetInstance()->FindCaptainData()->GetMaxExperience() / 8;
	_float maxValue = maxExp;
	_float value = CDataManager::GetInstance()->FindCaptainData()->GetExperience();
	for (int i = 0; i <= 7; i++)
	{
		Engine::CSlider* slider = static_cast<Engine::CSlider*>(pScene->FindObjectByName(L"MainCanvas_Slider_" + std::to_wstring(i)).get());
		slider->SetValue(value);

		slider->SetMinValue(maxValue);
		maxValue += maxExp;
		slider->SetMaxValue(maxValue);
	}

	std::wstring stamina = std::to_wstring(CDataManager::GetInstance()->FindCaptainData()->GetStamina()) + L"/" + std::to_wstring(CDataManager::GetInstance()->FindCaptainData()->GetMaxStamina());
	pScene->FindObjectByName(L"MainCanvas_Text_2")->GetComponent<Engine::CTextC>()->ChangeMessage(stamina);
	pScene->FindObjectByName(L"MainCanvas_Text_3")->GetComponent<Engine::CTextC>()->ChangeMessage(std::to_wstring(CDataManager::GetInstance()->FindCaptainData()->GetGold()));
	pScene->FindObjectByName(L"MainCanvas_Text_4")->GetComponent<Engine::CTextC>()->ChangeMessage(std::to_wstring(CDataManager::GetInstance()->FindCaptainData()->GetDiamond()));

	pScene->FindObjectByName(L"MainCanvas_Image_21")->AddComponent<CSizeUpC>()->SetSize(197.118f);
	pScene->FindObjectByName(L"MainCanvas_Image_21")->GetComponent<CSizeUpC>()->SetSpeed(100.0f);
	pScene->FindObjectByName(L"MainCanvas_Image_21")->GetComponent<CSizeUpC>()->SetStopTime(0.5f);

	pScene->FindObjectByName(L"MainCanvas_Image_22")->AddComponent<CSizeUpC>()->SetSize(197.118f);
	pScene->FindObjectByName(L"MainCanvas_Image_22")->GetComponent<CSizeUpC>()->SetSpeed(100.0f);
}

void CMainRoomManager::Update(void)
{
}

void CMainRoomManager::OnDestroy(void)
{
}
