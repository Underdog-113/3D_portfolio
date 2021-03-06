#include "stdafx.h"
#include "MainRoomManager.h"
#include "DataManager.h"
#include "CaptainData.h"

IMPLEMENT_SINGLETON(CMainRoomManager)
void CMainRoomManager::Start(Engine::CScene * pScene)
{

	m_vPlayer = pScene->GetObjectFactory()->AddClone(L"KianaUIAnim", true, (_int)ELayerID::Player, L"");
	m_vPlayer->GetComponent<Engine::CTransformC>()->SetPosition(_float3(-0.81f, -1.05f, -1.4f));
	m_vPlayer->GetComponent<Engine::CTransformC>()->SetRotation(_float3(0, 109.78f, 0));
	m_vPlayer->GetComponent<Engine::CTransformC>()->SetSize(_float3(1.f, 1.f, 1.f));

	SP(Engine::CShaderC) spShader = m_vPlayer->GetComponent<Engine::CShaderC>();
	spShader->AddShader((_int)EShaderID::OutlineShader);

	spShader->ResizeShaderPerSubset(3);
	spShader->AddShaderPerSubset((_int)EShaderID::KianaBodyShader, 0);
	spShader->AddShaderPerSubset((_int)EShaderID::FaceShader, 1);
	spShader->AddShaderPerSubset((_int)EShaderID::KianaBodyShader, 2);

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
	CDropItemManager::GetInstance()->AllDelete();
}
