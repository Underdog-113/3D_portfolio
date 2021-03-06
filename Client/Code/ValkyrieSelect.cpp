#include "stdafx.h"
#include "ValkyrieSelect.h"

#include "ButtonFunction.h"

#include "ClientScene.h"

#include "ValkyrieSelect.h"
#include "ValkyrieProperty.h"
#include "ValkyrieWeapon.h"

#include "DynamicMeshData.h"
#include "AniCtrl.h"
#include "ReadyToSortieScene.h"

#include "KianaUIAnim.h"

SP(Engine::CObject) CValkyrieSelect::m_vPlayer = nullptr;
CValkyrieSelect::CValkyrieSelect()
{

}

CValkyrieSelect::~CValkyrieSelect()
{
}

void CValkyrieSelect::Start()
{
	/*m_vValkyrie[0] = GET_CUR_CLIENT_SCENE->GetObjectFactory()->AddClone(L"KianaUIAnim", true, (_int)ELayerID::Player, L"").get();
	m_vValkyrie[0]->GetComponent<Engine::CTransformC>()->SetPosition(_float3(-0.31f, -0.64f, -3.5f));
	m_vValkyrie[0]->GetComponent<Engine::CTransformC>()->SetRotation(_float3(0, 110, 0));
	m_vValkyrie[0]->GetComponent<Engine::CTransformC>()->SetSize(_float3(0.5f, 0.5f, 0.5f));
	m_vValkyrie[0]->SetIsEnabled(false);*/

	CValkyriegManager::GetInstance()->GetScene()->FindObjectByName(L"PropertyCanvas")->SetIsEnabled(false);
	CValkyriegManager::GetInstance()->GetScene()->FindObjectByName(L"LevelUpCanvas")->SetIsEnabled(false);
	CValkyriegManager::GetInstance()->GetScene()->FindObjectByName(L"WeaponCanvas")->SetIsEnabled(false);
	CValkyriegManager::GetInstance()->GetScene()->FindObjectByName(L"WeaponSwapCanvas")->SetIsEnabled(false);
	CValkyriegManager::GetInstance()->GetScene()->FindObjectByName(L"WeaponLevelUpCanvas")->SetIsEnabled(false);

	if (m_init)
	{
		MainCanvas();
		ValkyrieStatus();

		if (CButtonFunction::squadValue >= CDataManager::GetInstance()->FindSquadData()->GetValkyriesList().size())
		{
			CValkyriegManager::g_selectValkyrie = L"투예복·백련";
		}
		else
			CValkyriegManager::g_selectValkyrie = CDataManager::GetInstance()->FindSquadData()->GetValkyriesList()[CButtonFunction::squadValue]->GetSubName();

		m_init = false;
	}
	else
	{
		Delegate<> delegate;
		delegate += std::bind(&CButtonFunction::ReadyToSortieScene, &CButtonFunction());

		std::static_pointer_cast<CButton>(CValkyriegManager::GetInstance()->GetScene()->FindObjectByName(L"MainCanvas_Button_1"))->
			AddFuncData(delegate);

		CValkyriegManager::GetInstance()->GetScene()->FindObjectByName(L"MainCanvas")->SetIsEnabled(true);
		CValkyriegManager::GetInstance()->GetScene()->FindObjectByName(L"ValkyrieCanvas")->SetIsEnabled(true);

		CInStockValkyrieData* allValkyrie = CDataManager::GetInstance()->FindInStockValkyrieData();

		_int count = 0;
		for (auto& data : allValkyrie->GetValkyriesList())
		{
			_int level = data->GetLevel();
			static_cast<CScrollViewObject*>(CValkyriegManager::GetInstance()->GetScene()->FindObjectByName(L"ValkyrieCanvas_ScrollView_0").get())->
				GetTextObject()[count].m_text->GetComponent<Engine::CTextC>()->ChangeMessage(L"LV." + std::to_wstring(level));

			count++;
		}
		DataSetting(CValkyriegManager::g_selectValkyrie);
	}

}

void CValkyrieSelect::End()
{
	_int end = 10;
	CValkyriegManager::GetInstance()->GetScene()->FindObjectByName(L"ValkyrieCanvas")->SetIsEnabled(false);

	if (m_vPlayer != nullptr)
		m_vPlayer->SetDeleteThis(true);

}

_uint CValkyrieSelect::FixedUpdate()
{
	return _uint();
}

_uint CValkyrieSelect::Update()
{
	if (Engine::CInputManager::GetInstance()->KeyPress(KEY_W))
	{
		m_vPlayer->GetComponent<Engine::CTransformC>()->AddPositionY(0.005f);
	}
	if (Engine::CInputManager::GetInstance()->KeyPress(KEY_S))
	{
		m_vPlayer->GetComponent<Engine::CTransformC>()->AddPositionY(-0.005f);
	}
	if (Engine::CInputManager::GetInstance()->KeyPress(KEY_A))
	{
		m_vPlayer->GetComponent<Engine::CTransformC>()->AddPositionX(0.005f);
	}
	if (Engine::CInputManager::GetInstance()->KeyPress(KEY_D))
	{
		m_vPlayer->GetComponent<Engine::CTransformC>()->AddPositionX(-0.005f);
	}
	if (Engine::CInputManager::GetInstance()->KeyPress(KEY_Q))
	{
		m_vPlayer->GetComponent<Engine::CTransformC>()->AddPositionZ(0.005f);
	}
	if (Engine::CInputManager::GetInstance()->KeyPress(KEY_E))
	{
		m_vPlayer->GetComponent<Engine::CTransformC>()->AddPositionZ(-0.005f);
	}

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
		CValkyriegManager::g_oldSelectValkyrie = data->GetSubName();
	}
	else
	{
		data = CDataManager::GetInstance()->FindInStockValkyrieData()->GetValkyriesList()[0];
		CValkyriegManager::g_oldSelectValkyrie = L"";
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

		spScrollView->AddTextObjectData(i, _float2(33.4f, -84.92f), 35, D3DXCOLOR(0.1960784f, 0.1960784f, 0.1960784f, 1), L"LV." + std::to_wstring(allValkyrie->GetValkyriesList()[i]->GetLevel()));
	}
}

void CValkyrieSelect::ValkyrieStatusSetting()
{
	CValkyriegManager::g_selectValkyrie = CButtonManager::GetInstance()->GetActivationButton()->GetName();
	DataSetting(CValkyriegManager::g_selectValkyrie);
}

void CValkyrieSelect::DataSetting(std::wstring keyValue)
{
	CValkyrieStatusData* data;

	data = CDataManager::GetInstance()->FindInStockValkyrieData(keyValue);
	Engine::CScene* scene = CValkyriegManager::GetInstance()->GetScene();

	scene->FindObjectByName(L"ValkyrieCanvas_Image_3")->GetComponent<Engine::CTextureC>()->ChangeTexture(data->GetRank());
	scene->FindObjectByName(L"ValkyrieCanvas_Image_4")->GetComponent<Engine::CTextureC>()->ChangeTexture(data->GetProperty());
	scene->FindObjectByName(L"ValkyrieCanvas_Text_0")->GetComponent<Engine::CTextC>()->ChangeMessage(L"LV." + std::to_wstring(data->GetLevel()));
	scene->FindObjectByName(L"ValkyrieCanvas_Text_5")->GetComponent<Engine::CTextC>()->ChangeMessage(data->GetWeaponData()->GetName());
	scene->FindObjectByName(L"ValkyrieCanvas_Text_2")->GetComponent<Engine::CTextC>()->ChangeMessage(data->GetSubName());
	scene->FindObjectByName(L"ValkyrieCanvas_Text_3")->GetComponent<Engine::CTextC>()->ChangeMessage(data->GetName());
	T = scene->FindObjectByName(L"BackGroundCanvas_BackGround_0").get();
	T->GetTransform()->SetPosition(_float3(0,0,500));
	T->GetComponent<Engine::CTextureC>()->ChangeTexture(L"SpaceShipBridge_City");
	// 케릭터 메쉬 띄우기


	if (m_vPlayer != nullptr)
		m_vPlayer->SetDeleteThis(true);

	std::wstring name = data->GetName();
	if (name == L"키아나·카스라나")
	{
		// 키아나 오브젝트 생성 -> IDLE로 변경
		m_vPlayer = scene->GetObjectFactory()->AddClone(L"KianaUIAnim", true, (_int)ELayerID::Player, L"");
		m_vPlayer->GetComponent<Engine::CTransformC>()->SetPosition(_float3(0.200000063f, -2.75000310f, -1.07500005f));
		m_vPlayer->GetComponent<Engine::CTransformC>()->SetRotation(_float3(0, D3DXToRadian(180.0f), 0));
		m_vPlayer->GetComponent<Engine::CTransformC>()->SetSize(_float3(2.f, 2.f, 2.f));

		SP(Engine::CShaderC) spShader = m_vPlayer->GetComponent<Engine::CShaderC>();
		spShader->AddShader((_int)EShaderID::OutlineShader);

		spShader->ResizeShaderPerSubset(3);
		spShader->AddShaderPerSubset((_int)EShaderID::KianaBodyShader, 0);
		spShader->AddShaderPerSubset((_int)EShaderID::FaceShader, 1);
		spShader->AddShaderPerSubset((_int)EShaderID::KianaBodyShader, 2);
	}
	else if (name == L"테레사·아포칼립스")
	{
		// 테레사 오브젝트 생성 -> IDLE로 변경
		m_vPlayer = scene->GetObjectFactory()->AddClone(L"KianaUIAnim", true, (_int)ELayerID::Player, L"");
		static_cast<CKianaUIAnim*>(m_vPlayer.get())->SetTextureName(L"Theresa_NoWp"); 
		m_vPlayer->GetComponent<Engine::CTransformC>()->SetPosition(_float3(0.0400000326f, -0.799999893f, -3.64999032f));
		m_vPlayer->GetComponent<Engine::CTransformC>()->SetRotation(_float3(0, D3DXToRadian(180.0f), 0));
		m_vPlayer->GetComponent<Engine::CTransformC>()->SetSize(_float3(1.f, 1.f, 1.f));

		SP(Engine::CShaderC) spShader = m_vPlayer->GetComponent<Engine::CShaderC>();
		spShader->AddShader((_int)EShaderID::OutlineShader);
		spShader->AddShader((_int)EShaderID::CharacterShader);
	}
	else if (name == L"야에 사쿠라")
	{
		// 사쿠라 오브젝트 생성 -> IDLE로 변경
		m_vPlayer = scene->GetObjectFactory()->AddClone(L"KianaUIAnim", true, (_int)ELayerID::Player, L"");
		static_cast<CKianaUIAnim*>(m_vPlayer.get())->SetTextureName(L"Sakura_Wp");
		m_vPlayer->GetComponent<Engine::CTransformC>()->SetPosition(_float3(0.0500006266f, -0.534999609f, -4.30503416f));
		m_vPlayer->GetComponent<Engine::CTransformC>()->SetRotation(_float3(0, D3DXToRadian(180.0f), 0));
		m_vPlayer->GetComponent<Engine::CTransformC>()->SetSize(_float3(1.f, 1.f, 1.f));
		SP(Engine::CShaderC) spShader = m_vPlayer->GetComponent<Engine::CShaderC>();
		spShader->AddShader((_int)EShaderID::OutlineShader);
		spShader->AddShader((_int)EShaderID::CharacterShader);
	}

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
	if (keyValue == CValkyriegManager::g_oldSelectValkyrie)
	{
		scene->FindObjectByName(L"ValkyrieCanvas_Button_0")->GetComponent<Engine::CTextC>()->ChangeMessage(L"파티 탈퇴");
		delegate += std::bind(&CValkyrieSelect::PartySecession, &CValkyrieSelect());
	}
	else if (CDataManager::GetInstance()->FindSquadData(keyValue)->GetName() != L"")
	{
		scene->FindObjectByName(L"ValkyrieCanvas_Button_0")->GetComponent<Engine::CTextC>()->ChangeMessage(L"편성중");
		delegate += std::bind(&CValkyrieSelect::Not, &CValkyrieSelect());
	}
	else if (CValkyriegManager::g_oldSelectValkyrie == L"") // 빈공간을 클릭
	{
		scene->FindObjectByName(L"ValkyrieCanvas_Button_0")->GetComponent<Engine::CTextC>()->ChangeMessage(L"파티 가입");
		delegate += std::bind(&CValkyrieSelect::PartyJoin, &CValkyrieSelect());
	}
	else if (keyValue != CValkyriegManager::g_oldSelectValkyrie) // 다른 맴버 클릭
	{
		scene->FindObjectByName(L"ValkyrieCanvas_Button_0")->GetComponent<Engine::CTextC>()->ChangeMessage(L"파티 가입");
		delegate += std::bind(&CValkyrieSelect::PartySwap, &CValkyrieSelect());
	}


	std::static_pointer_cast<CButton>(scene->FindObjectByName(L"ValkyrieCanvas_Button_0"))->
		AddFuncData(delegate);
}

void CValkyrieSelect::PartyJoin()
{
	CDataManager::GetInstance()->SquadInit(CValkyriegManager::g_selectValkyrie);
	SceneChange();
}

void CValkyrieSelect::PartySwap()
{
	CDataManager::GetInstance()->SquadInit(CButtonFunction::squadValue, CValkyriegManager::g_selectValkyrie);

	SceneChange();
}

void CValkyrieSelect::PartySecession()
{
	CDataManager::GetInstance()->SquadDelete(CValkyriegManager::g_oldSelectValkyrie);
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
2. g_selectValkyrie값을 가지고 데이터를 받아와서 셋팅시작
3. 뒤로가기 버튼도 다시 셋팅해줘야함
*/
