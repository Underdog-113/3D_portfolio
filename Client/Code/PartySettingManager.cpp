#include "stdafx.h"
#include "PartySettingManager.h"
#include "ButtonFunction.h"

#include "DataManager.h"
#include "ValkyrieStatusData.h"
#include "InStockValkyrieData.h"
#include "SquadData.h"
#include "WeaponData.h"
#include "ClientScene.h"

#include "ReadyToSortieScene.h"

IMPLEMENT_SINGLETON(CPartySettingManager)
std::wstring CPartySettingManager::m_selectValkyrie = L"";
std::wstring CPartySettingManager::m_oldSelectValkyrie = L"";

void CPartySettingManager::Start(Engine::CScene * pScene)
{
	MainCanvas(pScene);
	ValkyrieStatus(pScene);
}

void CPartySettingManager::Update(void)
{
	if(Engine::CInputManager::GetInstance()->KeyDown(KEY_1))
	{
		
	}

	// 스크롤바에 여러 버튼 오브젝트 생성
	// 해당 버튼을 클릭하면 
}

void CPartySettingManager::OnDestroy(void)
{

}

void CPartySettingManager::MainCanvas(Engine::CScene * pScene)
{
	_int squadValue = CButtonFunction::squadValue;
	CValkyrieStatusData* data;
	if (squadValue < CDataManager::GetInstance()->FindSquadData()->GetValkyriesList().size())
	{
		data = CDataManager::GetInstance()->FindSquadData()->GetValkyriesList()[squadValue];
		m_oldSelectValkyrie = data->GetSubName();
	}
	else
	{
		data = CDataManager::GetInstance()->FindInStockValkyrieData()->GetValkyriesList()[0];
		m_oldSelectValkyrie = L"";
	}
	
	pScene->FindObjectByName(L"ValkyrieCanvas_Image_3")->GetComponent<Engine::CTextureC>()->ChangeTexture(data->GetRank());
	pScene->FindObjectByName(L"ValkyrieCanvas_Image_4")->GetComponent<Engine::CTextureC>()->ChangeTexture(data->GetProperty());
	pScene->FindObjectByName(L"ValkyrieCanvas_Text_0")->GetComponent<Engine::CTextC>()->ChangeMessage(L"LV." + std::to_wstring(data->GetLevel()));
	//pScene->FindObjectByName(L"ValkyrieCanvas_Text_5")->GetComponent<Engine::CTextC>()->ChangeMessage(data->GetWeaponData()->GetName());
	pScene->FindObjectByName(L"ValkyrieCanvas_Text_2")->GetComponent<Engine::CTextC>()->ChangeMessage(data->GetSubName());
	pScene->FindObjectByName(L"ValkyrieCanvas_Text_3")->GetComponent<Engine::CTextC>()->ChangeMessage(data->GetName());

	if (data->GetProperty() == L"AvatarJiXie")
	{
		pScene->FindObjectByName(L"ValkyrieCanvas_Text_1")->GetComponent<Engine::CTextC>()->ChangeMessage(L"기계");
	}
	else if (data->GetProperty() == L"AvatarShengWu")
	{
		pScene->FindObjectByName(L"ValkyrieCanvas_Text_1")->GetComponent<Engine::CTextC>()->ChangeMessage(L"생물");
	}
	else if (data->GetProperty() == L"AvatarYiNeng")
	{
		pScene->FindObjectByName(L"ValkyrieCanvas_Text_1")->GetComponent<Engine::CTextC>()->ChangeMessage(L"이능");
	}



	Delegate<> delegate;
	if (data->GetSubName() == m_oldSelectValkyrie)
	{
		pScene->FindObjectByName(L"MainCanvas_Button_8")->GetComponent<Engine::CTextC>()->ChangeMessage(L"파티 탈퇴");
		delegate += std::bind(&CPartySettingManager::PartySecession, &CPartySettingManager());
	}
	else if (CDataManager::GetInstance()->FindSquadData(data->GetSubName())->GetName() != L"")
	{
		pScene->FindObjectByName(L"MainCanvas_Button_8")->GetComponent<Engine::CTextC>()->ChangeMessage(L"편성중");
		delegate += std::bind(&CPartySettingManager::Not, &CPartySettingManager());
	}
	else if (m_oldSelectValkyrie == L"") // 빈공간을 클릭
	{
		pScene->FindObjectByName(L"MainCanvas_Button_8")->GetComponent<Engine::CTextC>()->ChangeMessage(L"파티 가입");
		delegate += std::bind(&CPartySettingManager::PartyJoin, &CPartySettingManager());
	}
	else if (data->GetSubName() != m_oldSelectValkyrie) // 다른 맴버 클릭
	{
		pScene->FindObjectByName(L"MainCanvas_Button_8")->GetComponent<Engine::CTextC>()->ChangeMessage(L"파티 가입");
		delegate += std::bind(&CPartySettingManager::PartySwap, &CPartySettingManager());
	}

	std::static_pointer_cast<CButton>(pScene->FindObjectByName(L"MainCanvas_Button_8"))->
		AddFuncData(delegate);

}

void CPartySettingManager::ValkyrieStatus(Engine::CScene * pScene)
{
	CInStockValkyrieData* allValkyrie = CDataManager::GetInstance()->FindInStockValkyrieData();
	_size allValkrieSize = allValkyrie->GetValkyriesList().size();

	SP(CScrollViewObject) spScrollView = std::dynamic_pointer_cast<CScrollViewObject>(pScene->FindObjectByName(L"ValkyrieCanvas_ScrollView_0"));
	spScrollView->AddScrollViewData(999, _float2(215.0f, 0.0f), _float2(-581, 0));

	for (int i = 0; i < allValkrieSize; i++)
	{
		spScrollView->
			AddButtonObjectData<void(CPartySettingManager::*)(), CPartySettingManager*>(&CPartySettingManager::ValkyrieStatusSetting, &CPartySettingManager(),
				_float2(210.0f, 217.0f), allValkyrie->GetValkyriesList()[i]->GetSubName(), L"AttrShengWu1", L"AttrShengWu1");

		spScrollView->
			AddImageObjectData(i, allValkyrie->GetValkyriesList()[i]->GetListTextureKey(), _float3(170.0f, 153.0f, 0.0f), _float2(0, 26))->
			AddImageObjectData(i, allValkyrie->GetValkyriesList()[i]->GetRank(), _float3(47.0f, 47.0f, 0.0f), _float2(-68,-77));
	}
}

void CPartySettingManager::ValkyrieStatusSetting()
{
	CPartySettingManager::m_selectValkyrie = CButtonManager::GetInstance()->GetActivationButton()->GetName();
	DataSetting(CPartySettingManager::m_selectValkyrie);
}

void CPartySettingManager::DataSetting(std::wstring keyValue)
{
	CValkyrieStatusData* data;

	data = CDataManager::GetInstance()->FindInStockValkyrieData(keyValue);

	GET_CUR_CLIENT_SCENE->FindObjectByName(L"ValkyrieCanvas_Image_3")->GetComponent<Engine::CTextureC>()->ChangeTexture(data->GetRank());
	GET_CUR_CLIENT_SCENE->FindObjectByName(L"ValkyrieCanvas_Image_4")->GetComponent<Engine::CTextureC>()->ChangeTexture(data->GetProperty());
	GET_CUR_CLIENT_SCENE->FindObjectByName(L"ValkyrieCanvas_Text_0")->GetComponent<Engine::CTextC>()->ChangeMessage(L"LV." + std::to_wstring(data->GetLevel()));
	//GET_CUR_CLIENT_SCENE->FindObjectByName(L"ValkyrieCanvas_Text_5")->GetComponent<Engine::CTextC>()->ChangeMessage(data->GetWeaponData()->GetName());
	GET_CUR_CLIENT_SCENE->FindObjectByName(L"ValkyrieCanvas_Text_2")->GetComponent<Engine::CTextC>()->ChangeMessage(data->GetSubName());
	GET_CUR_CLIENT_SCENE->FindObjectByName(L"ValkyrieCanvas_Text_3")->GetComponent<Engine::CTextC>()->ChangeMessage(data->GetName());

	if (data->GetProperty() == L"AvatarJiXie")
	{
		GET_CUR_CLIENT_SCENE->FindObjectByName(L"ValkyrieCanvas_Text_1")->GetComponent<Engine::CTextC>()->ChangeMessage(L"기계");
	}
	else if (data->GetProperty() == L"AvatarShengWu")
	{
		GET_CUR_CLIENT_SCENE->FindObjectByName(L"ValkyrieCanvas_Text_1")->GetComponent<Engine::CTextC>()->ChangeMessage(L"생물");
	}
	else if (data->GetProperty() == L"AvatarYiNeng")
	{
		GET_CUR_CLIENT_SCENE->FindObjectByName(L"ValkyrieCanvas_Text_1")->GetComponent<Engine::CTextC>()->ChangeMessage(L"이능");
	}

	Delegate<> delegate;
	if (keyValue == m_oldSelectValkyrie)
	{
		GET_CUR_CLIENT_SCENE->FindObjectByName(L"MainCanvas_Button_8")->GetComponent<Engine::CTextC>()->ChangeMessage(L"파티 탈퇴");
		delegate += std::bind(&CPartySettingManager::PartySecession, &CPartySettingManager());
	}
	else if (CDataManager::GetInstance()->FindSquadData(keyValue)->GetName() != L"")
	{
		GET_CUR_CLIENT_SCENE->FindObjectByName(L"MainCanvas_Button_8")->GetComponent<Engine::CTextC>()->ChangeMessage(L"편성중");
		delegate += std::bind(&CPartySettingManager::Not, &CPartySettingManager());
	}
	else if (m_oldSelectValkyrie == L"") // 빈공간을 클릭
	{
		GET_CUR_CLIENT_SCENE->FindObjectByName(L"MainCanvas_Button_8")->GetComponent<Engine::CTextC>()->ChangeMessage(L"파티 가입");
		delegate += std::bind(&CPartySettingManager::PartyJoin, &CPartySettingManager());
	}
	else if (keyValue != m_oldSelectValkyrie) // 다른 맴버 클릭
	{
		GET_CUR_CLIENT_SCENE->FindObjectByName(L"MainCanvas_Button_8")->GetComponent<Engine::CTextC>()->ChangeMessage(L"파티 가입");
		delegate += std::bind(&CPartySettingManager::PartySwap, &CPartySettingManager());
	}


 	std::static_pointer_cast<CButton>(GET_CUR_CLIENT_SCENE->FindObjectByName(L"MainCanvas_Button_8"))->
		AddFuncData(delegate);
}

void CPartySettingManager::PartyJoin()
{
	CDataManager::GetInstance()->SquadInit(CPartySettingManager::m_selectValkyrie);
	SceneChange();
}

void CPartySettingManager::PartySwap()
{
	CDataManager::GetInstance()->SquadInit(CButtonFunction::squadValue,CPartySettingManager::m_selectValkyrie);

	SceneChange();
}

void CPartySettingManager::PartySecession()
{
	CDataManager::GetInstance()->SquadDelete(m_oldSelectValkyrie);
	SceneChange();
}

void CPartySettingManager::Not()
{
	std::cout << "파티낫" << std::endl;
}

void CPartySettingManager::SceneChange()
{
	Engine::CSoundManager::GetInstance()->StopSound((_uint)Engine::EChannelID::UI_ButtonUI);
	Engine::CSoundManager::GetInstance()->StartSound(L"ButtonClick.waw", (_uint)Engine::EChannelID::UI_ButtonUI);
	CButtonManager::GetInstance()->OnDestroy();
	GET_CUR_CLIENT_SCENE->ChangeScene(CReadyToSortieScene::Create());
}
