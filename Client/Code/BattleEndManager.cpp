#include "stdafx.h"
#include "BattleEndManager.h"
#include "ValkyrieFSM.h"

#include "WaponItem.h"
#include "stuffItem.h"

IMPLEMENT_SINGLETON(CBattleEndManager)
void CBattleEndManager::Start(Engine::CScene * pScene)
{
	m_scene = pScene;
	m_addCaptainExp = 0;
	m_addValkryieExp = 0;

	m_itemList = CStageControlTower::GetInstance()->GetItemList();
	m_gold = CStageControlTower::GetInstance()->GetGold();
	m_captainExp = CStageControlTower::GetInstance()->GetCaptainExp();
	m_valkyrieExp = CStageControlTower::GetInstance()->GetValkyrieExp();


	ItemSave T;
	T.itemName = L"특급 학습 칩";
	T.count = 40;
	m_itemList.emplace_back(T);

	ValkyrieUI();
	CaptainUI();
	ItemUI();
}
void CBattleEndManager::Update(void)
{
	DataUpdate();
}

void CBattleEndManager::OnDestroy(void)
{

}

void CBattleEndManager::ValkyrieUI()
{
	// 현재 스쿼드에 맞게 그림을 변경
	std::vector<CValkyrieStatusData*> valkyrieStatus = CDataManager::GetInstance()->FindSquadData()->GetValkyriesList();
	m_squadSize = valkyrieStatus.size();

	for (_int i = 0; i < 3; i++)
	{
		if (m_squadSize <= i)
		{
			m_scene->FindObjectByName(L"PlayerIS" + std::to_wstring(i + 1))->SetIsEnabled(false);
		}
		else
		{
			m_scene->FindObjectByName(L"PlayerIS" + std::to_wstring(i + 1) + L"_Image_0")->GetComponent<Engine::CTextureC>()->ChangeTexture(valkyrieStatus[i]->GetPartyTextureKey());
			m_scene->FindObjectByName(L"PlayerIS" + std::to_wstring(i + 1) + L"_Image_1")->GetComponent<Engine::CTextureC>()->ChangeTexture(valkyrieStatus[i]->GetRank());
			m_scene->FindObjectByName(L"PlayerIS" + std::to_wstring(i + 1) + L"_Text_11")->GetComponent<Engine::CTextC>()->ChangeMessage(L"LV." + std::to_wstring(valkyrieStatus[i]->GetLevel()));

			Engine::CSlider* slider = static_cast<Engine::CSlider*>(m_scene->FindObjectByName(L"PlayerIS" + std::to_wstring(i + 1) + L"_Slider_10").get());
			slider->SetValue((_float)valkyrieStatus[i]->GetExperience());
			slider->SetMaxValue((_float)valkyrieStatus[i]->GetMaxExperience());

			m_scene->FindObjectByName(L"PlayerIS" + std::to_wstring(i + 1) + L"_Text_13")->GetComponent<Engine::CTextC>()->ChangeMessage(std::to_wstring(m_valkyrieExp));
		}
	}

	m_scene->FindObjectByName(L"MainCanvas_Text_2")->GetComponent<Engine::CTextC>()->ChangeMessage(std::to_wstring(m_gold));
	m_scene->FindObjectByName(L"MainCanvas_Text_1")->GetComponent<Engine::CTextC>()->ChangeMessage(L"LV." + std::to_wstring(CDataManager::GetInstance()->FindCaptainData()->GetLevel()));
	m_scene->FindObjectByName(L"MainCanvas_Text_4")->GetComponent<Engine::CTextC>()->ChangeMessage(std::to_wstring((_int)CDataManager::GetInstance()->FindCaptainData()->GetExperience()) + L" / " + std::to_wstring((_int)CDataManager::GetInstance()->FindCaptainData()->GetMaxExperience()));
	m_scene->FindObjectByName(L"MainCanvas_Text_3")->GetComponent<Engine::CTextC>()->ChangeMessage(std::to_wstring(m_captainExp));
}

void CBattleEndManager::CaptainUI()
{
 	_float maxVlaue = CDataManager::GetInstance()->FindCaptainData()->GetMaxExperience();
	_float TminValue = maxVlaue / 10;
	_float minValue = 0;

	for (int i = 0; i < 10; i++)
	{
		Engine::CSlider* slider = static_cast<Engine::CSlider*>(m_scene->FindObjectByName(L"MainCanvas_Slider_" + std::to_wstring(i)).get());
		slider->SetValue(CDataManager::GetInstance()->FindCaptainData()->GetExperience());

		slider->SetMinValue(minValue);
		minValue += TminValue;
		slider->SetMaxValue(minValue);
	}
}

void CBattleEndManager::ItemUI()
{
	CScrollViewObject* spScrollView = static_cast<CScrollViewObject*>(m_scene->FindObjectByName(L"MainCanvas_ScrollView_0").get());
	size_t size = m_itemList.size();

	_int count = 0;
	for (auto& item : m_itemList)
	{
		CDataManager::GetInstance()->ItemInit(item.itemName, item.count);

		// 아이템을 추가할 메모장의 이름과 텍스처이름
		spScrollView->AddButtonObjectData<void(CStuffItem::*)(), CStuffItem*>(&CStuffItem::InformationWindow, &CStuffItem(),
				_float2(114.5f, 136.4f), item.itemName, L"UI_4", L"UI_4");

		spScrollView->AddImageObjectData(count, CDataManager::GetInstance()->FindItemData(item.itemName)->GetTextureKey(), _float3(108.0f, 94.4f, 0), _float2(0.0f, 12.5f));

		_int rank = CDataManager::GetInstance()->FindItemData(item.itemName)->GetRank();
		_float2 offset = _float2(-18.0f * (_int)(rank * 0.5f), -34.4f);

		for (int i = 0; i < rank; i++)
		{
			spScrollView->
				AddImageObjectData(count, L"StarBig", _float3(22.3f, 22.3f, 0.0f), offset , 0.01f);
			offset.x += 25.0f;
		}

		spScrollView->AddTextObjectData(count, _float2(-15.1f, -56.0f), 25, D3DXCOLOR(0.1960784f, 0.1960784f, 0.1960784f, 1), L"×" + std::to_wstring(item.count));

		count++;
	}

	
	// 획득 아이템 리스트를 받으면 해당 아이템리스트의 텍스처를 스크롤뷰에띄운다 다만 스크롤뷰에 해당 아이템이 존재하면 그냥 갯수만 올린다.
}

void CBattleEndManager::PlayerIS()
{
}

void CBattleEndManager::DataUpdate()
{
	std::vector<CValkyrieStatusData*> valkyrieStatus = CDataManager::GetInstance()->FindSquadData()->GetValkyriesList();

	if (m_valkyrieExp > m_addValkryieExp)
	{
		for (int i = 0; i < m_squadSize; i++)
		{
			Engine::CSlider* slider = static_cast<Engine::CSlider*>(m_scene->FindObjectByName(L"PlayerIS" + std::to_wstring(i +1)  + L"_Slider_10").get());
			slider->SetValue(slider->GetValue() + 1);

			if (slider->GetValue() == slider->GetMaxValue())
			{
				valkyrieStatus[i]->SetLevel(valkyrieStatus[i]->GetLevel() + 1);
				valkyrieStatus[i]->SetMaxExperience(((_int)(valkyrieStatus[i]->GetMaxExperience() * 1.5f)));
				slider->SetValue(0);
				slider->SetMaxValue((_float)valkyrieStatus[i]->GetMaxExperience());

				m_scene->FindObjectByName(L"PlayerIS" + std::to_wstring(i + 1) + L"_Text_11")->GetComponent<Engine::CTextC>()->ChangeMessage(L"LV." + std::to_wstring(valkyrieStatus[i]->GetLevel()));

			}
		}
		m_addValkryieExp++;
	}

	if (m_captainExp > m_addCaptainExp)
	{
		for (int i = 0; i < 10; i++)
		{
			Engine::CSlider* slider = static_cast<Engine::CSlider*>(m_scene->FindObjectByName(L"MainCanvas_Slider_" + std::to_wstring(i)).get());
			slider->SetValue(slider->GetValue() + 1);

			if (slider->GetValue() == CDataManager::GetInstance()->FindCaptainData()->GetMaxExperience())
			{
				CDataManager::GetInstance()->FindCaptainData()->SetLevel(CDataManager::GetInstance()->FindCaptainData()->GetLevel() + 1);
				CDataManager::GetInstance()->FindCaptainData()->SetMaxExperience(CDataManager::GetInstance()->FindCaptainData()->GetMaxExperience() * 1.5f);

				_float maxVlaue = CDataManager::GetInstance()->FindCaptainData()->GetMaxExperience();
				_float TminValue = maxVlaue / 10;
				_float minValue = 0;

				for (int j = 0; j < 10; j++)
				{
					Engine::CSlider* slider = static_cast<Engine::CSlider*>(m_scene->FindObjectByName(L"MainCanvas_Slider_" + std::to_wstring(j)).get());
					slider->SetValue(0);

					slider->SetMinValue(minValue);
					minValue += TminValue;
					slider->SetMaxValue(minValue);
				}

				m_addCaptainExp++;
				return;
			}
		}

		m_addCaptainExp++;
	}
}