#include "stdafx.h"
#include "ReadyToSortieManager.h"
#include "DataManager.h"
#include "CaptainData.h"
#include "InStockValkyrieData.h"
#include "SquadData.h"
#include "ValkyrieStatusData.h"

IMPLEMENT_SINGLETON(CReadyToSortieManager)
void CReadyToSortieManager::Start(Engine::CScene * pScene)
{
	mainCanvas(pScene);
	PlayerIS(pScene);
}

void CReadyToSortieManager::Update(void)
{
}

void CReadyToSortieManager::OnDestroy(void)
{
}

void CReadyToSortieManager::mainCanvas(Engine::CScene * pScene)
{
	std::wstring stamina = std::to_wstring(CDataManager::GetInstance()->FindCaptainData()->GetStamina()) + L"/" + std::to_wstring(CDataManager::GetInstance()->FindCaptainData()->GetMaxStamina());
	static_cast<Engine::CCanvas*>(pScene->FindObjectByName(L"EndCanvas").get())->AddObjectFind();
	pScene->FindObjectByName(L"EndCanvas")->SetIsEnabled(false);

	pScene->FindObjectByName(L"MainCanvas_Text_2")->GetComponent<Engine::CTextC>()->ChangeMessage(stamina);
	pScene->FindObjectByName(L"MainCanvas_Text_3")->GetComponent<Engine::CTextC>()->ChangeMessage(std::to_wstring(CDataManager::GetInstance()->FindCaptainData()->GetGold()));
	pScene->FindObjectByName(L"MainCanvas_Text_4")->GetComponent<Engine::CTextC>()->ChangeMessage(std::to_wstring(CDataManager::GetInstance()->FindCaptainData()->GetDiamond()));

}

void CReadyToSortieManager::PlayerIS(Engine::CScene * pScene)
{
	// 현재 스쿼드에 맞게 그림을 변경
	std::vector<CValkyrieStatusData*> valkyrieStatus = CDataManager::GetInstance()->FindSquadData()->GetValkyriesList();
	_size squadSize = valkyrieStatus.size();

	for (_int i = 0; i < 3; i++)
	{
		if (squadSize <= i)
		{
			// 십자가빼고 전부다 끈다.
			pScene->FindObjectByName(L"PlayerIS" + std::to_wstring(i + 1) + L"_Image_0")->SetIsEnabled(false);
			pScene->FindObjectByName(L"PlayerIS" + std::to_wstring(i + 1) + L"_Image_1")->SetIsEnabled(false);
			pScene->FindObjectByName(L"PlayerIS" + std::to_wstring(i + 1) + L"_Image_2")->SetIsEnabled(false);
			pScene->FindObjectByName(L"PlayerIS" + std::to_wstring(i + 1) + L"_Text_11")->SetIsEnabled(false);
			pScene->FindObjectByName(L"PlayerIS" + std::to_wstring(i + 1) + L"_Image_3")->SetIsEnabled(true);
		}
		else
		{
			pScene->FindObjectByName(L"PlayerIS" + std::to_wstring(i + 1) + L"_Image_0")->GetComponent<Engine::CTextureC>()->ChangeTexture(valkyrieStatus[i]->GetPartyTextureKey());
			pScene->FindObjectByName(L"PlayerIS" + std::to_wstring(i + 1) + L"_Image_1")->GetComponent<Engine::CTextureC>()->ChangeTexture(valkyrieStatus[i]->GetRank());
			pScene->FindObjectByName(L"PlayerIS" + std::to_wstring(i + 1) + L"_Image_2")->SetIsEnabled(false);
			pScene->FindObjectByName(L"PlayerIS" + std::to_wstring(i + 1) + L"_Image_3")->SetIsEnabled(false);
			pScene->FindObjectByName(L"PlayerIS" + std::to_wstring(i + 1) + L"_Text_11")->SetIsEnabled(true);
			pScene->FindObjectByName(L"PlayerIS" + std::to_wstring(i + 1) + L"_Text_11")->GetComponent<Engine::CTextC>()->ChangeMessage(L"LV." + std::to_wstring(valkyrieStatus[i]->GetLevel()));

			if (i == 0)
			{
				pScene->FindObjectByName(L"PlayerIS" + std::to_wstring(i + 1) + L"_Image_2")->SetIsEnabled(true);
			}

		}
	}

}
