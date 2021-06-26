#include "stdafx.h"
#include "ValkyrieSelect.h"

#include "ButtonFunction.h"

#include "ClientScene.h"

#include "ValkyrieSelect.h"
#include "ValkyrieProperty.h"
#include "ValkyrieWeapon.h"

#include "ReadyToSortieScene.h"

CValkyrieSelect::CValkyrieSelect()
{

}


CValkyrieSelect::~CValkyrieSelect()
{
}

void CValkyrieSelect::Start()
{
	CValkyriegManager::GetInstance()->GetScene()->FindObjectByName(L"PropertyCanvas")->SetIsEnabled(false);
	MainCanvas();
	ValkyrieStatus();
}

void CValkyrieSelect::End()
{
	_int end = 10;
}

_uint CValkyrieSelect::FixedUpdate()
{
	return _uint();
}

_uint CValkyrieSelect::Update()
{
	return _uint();
}

_uint CValkyrieSelect::LateUpdate()
{
	return _uint();
}

void CValkyrieSelect::OnDestroy(void)
{
}


void CValkyrieSelect::MainCanvas()
{
	_int squadValue = CButtonFunction::squadValue;
	CValkyrieStatusData* data;

	if (squadValue < CDataManager::GetInstance()->FindSquadData()->GetValkyriesList().size())
	{
		data = CDataManager::GetInstance()->FindSquadData()->GetValkyriesList()[squadValue];
		CValkyriegManager::m_oldSelectValkyrie = data->GetSubName();
	}
	else
	{
		data = CDataManager::GetInstance()->FindInStockValkyrieData()->GetValkyriesList()[0];
		CValkyriegManager::m_oldSelectValkyrie = L"";
	}

	DataSetting(data->GetSubName());
}

void CValkyrieSelect::ValkyrieStatus()
{
	CInStockValkyrieData* allValkyrie = CDataManager::GetInstance()->FindInStockValkyrieData();
	_size allValkrieSize = allValkyrie->GetValkyriesList().size();

	SP(CScrollViewObject) spScrollView = std::dynamic_pointer_cast<CScrollViewObject>(CValkyriegManager::GetInstance()->GetScene()->FindObjectByName(L"ValkyrieCanvas_ScrollView_0"));
	spScrollView->AddScrollViewData(999, _float2(215.0f, 0.0f), _float2(-581, 0));

	for (int i = 0; i < allValkrieSize; i++)
	{
		spScrollView->
			AddButtonObjectData<void(CValkyrieSelect::*)(), CValkyrieSelect*>(&CValkyrieSelect::ValkyrieStatusSetting, &CValkyrieSelect(),
				_float2(210.0f, 217.0f), allValkyrie->GetValkyriesList()[i]->GetSubName(), L"AttrShengWu1", L"AttrShengWu1");

		spScrollView->
			AddImageObjectData(i, allValkyrie->GetValkyriesList()[i]->GetListTextureKey(), _float3(170.0f, 153.0f, 0.0f), _float2(0, 26))->
			AddImageObjectData(i, allValkyrie->GetValkyriesList()[i]->GetRank(), _float3(47.0f, 47.0f, 0.0f), _float2(-68, -77));
	}
}

void CValkyrieSelect::ValkyrieStatusSetting()
{
	CValkyriegManager::m_selectValkyrie = CButtonManager::GetInstance()->GetActivationButton()->GetName();
	DataSetting(CValkyriegManager::m_selectValkyrie);
}

void CValkyrieSelect::DataSetting(std::wstring keyValue)
{
	CValkyrieStatusData* data;

	data = CDataManager::GetInstance()->FindInStockValkyrieData(keyValue);
	Engine::CScene* scene = CValkyriegManager::GetInstance()->GetScene();

	scene->FindObjectByName(L"ValkyrieCanvas_Image_3")->GetComponent<Engine::CTextureC>()->ChangeTexture(data->GetRank());
	scene->FindObjectByName(L"ValkyrieCanvas_Image_4")->GetComponent<Engine::CTextureC>()->ChangeTexture(data->GetProperty());
	scene->FindObjectByName(L"ValkyrieCanvas_Text_0")->GetComponent<Engine::CTextC>()->ChangeMessage(L"LV." + std::to_wstring(data->GetLevel()));
	//m_scene->FindObjectByName(L"ValkyrieCanvas_Text_5")->GetComponent<Engine::CTextC>()->ChangeMessage(data->GetWeaponData()->GetName());
	scene->FindObjectByName(L"ValkyrieCanvas_Text_2")->GetComponent<Engine::CTextC>()->ChangeMessage(data->GetSubName());
	scene->FindObjectByName(L"ValkyrieCanvas_Text_3")->GetComponent<Engine::CTextC>()->ChangeMessage(data->GetName());

	if (data->GetProperty() == L"AvatarJiXie")
	{
		scene->FindObjectByName(L"ValkyrieCanvas_Text_1")->GetComponent<Engine::CTextC>()->ChangeMessage(L"기계");
	}
	else if (data->GetProperty() == L"AvatarShengWu")
	{
		scene->FindObjectByName(L"ValkyrieCanvas_Text_1")->GetComponent<Engine::CTextC>()->ChangeMessage(L"생물");
	}
	else if (data->GetProperty() == L"AvatarYiNeng")
	{
		scene->FindObjectByName(L"ValkyrieCanvas_Text_1")->GetComponent<Engine::CTextC>()->ChangeMessage(L"이능");
	}

	Delegate<> delegate;
	if (keyValue == CValkyriegManager::m_oldSelectValkyrie)
	{
		scene->FindObjectByName(L"ValkyrieCanvas_Button_0")->GetComponent<Engine::CTextC>()->ChangeMessage(L"파티 탈퇴");
		delegate += std::bind(&CValkyrieSelect::PartySecession, &CValkyrieSelect());
	}
	else if (CDataManager::GetInstance()->FindSquadData(keyValue)->GetName() != L"")
	{
		scene->FindObjectByName(L"ValkyrieCanvas_Button_0")->GetComponent<Engine::CTextC>()->ChangeMessage(L"편성중");
		delegate += std::bind(&CValkyrieSelect::Not, &CValkyrieSelect());
	}
	else if (CValkyriegManager::m_oldSelectValkyrie == L"") // 빈공간을 클릭
	{
		scene->FindObjectByName(L"ValkyrieCanvas_Button_0")->GetComponent<Engine::CTextC>()->ChangeMessage(L"파티 가입");
		delegate += std::bind(&CValkyrieSelect::PartyJoin, &CValkyrieSelect());
	}
	else if (keyValue != CValkyriegManager::m_oldSelectValkyrie) // 다른 맴버 클릭
	{
		scene->FindObjectByName(L"ValkyrieCanvas_Button_0")->GetComponent<Engine::CTextC>()->ChangeMessage(L"파티 가입");
		delegate += std::bind(&CValkyrieSelect::PartySwap, &CValkyrieSelect());
	}


	std::static_pointer_cast<CButton>(scene->FindObjectByName(L"ValkyrieCanvas_Button_0"))->
		AddFuncData(delegate);
}

void CValkyrieSelect::PartyJoin()
{
	CDataManager::GetInstance()->SquadInit(CValkyriegManager::m_selectValkyrie);
	SceneChange();
}

void CValkyrieSelect::PartySwap()
{
	CDataManager::GetInstance()->SquadInit(CButtonFunction::squadValue, CValkyriegManager::m_selectValkyrie);

	SceneChange();
}

void CValkyrieSelect::PartySecession()
{
	CDataManager::GetInstance()->SquadDelete(CValkyriegManager::m_oldSelectValkyrie);
	SceneChange();
}

void CValkyrieSelect::Not()
{
	std::cout << "파티낫" << std::endl;
}

void CValkyrieSelect::SceneChange()
{
	Engine::CSoundManager::GetInstance()->StopSound((_uint)Engine::EChannelID::UI_ButtonUI);
	Engine::CSoundManager::GetInstance()->StartSound(L"ButtonClick.waw", (_uint)Engine::EChannelID::UI_ButtonUI);
	CButtonManager::GetInstance()->OnDestroy();
	GET_CUR_CLIENT_SCENE->ChangeScene(CReadyToSortieScene::Create());
}

/*
1. 버튼을누르면 버튼쪽으로 이동하는 함수실행
2. m_selectValkyrie값을 가지고 데이터를 받아와서 셋팅시작
3. 뒤로가기 버튼도 다시 셋팅해줘야함
*/