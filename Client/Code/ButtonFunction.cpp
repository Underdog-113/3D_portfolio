#include "stdafx.h"
#include "ButtonFunction.h"
#include "ButtonManager.h"
#include "WndApp.h"

#include "Loading.h"
#include "JongScene.h"
#include "ChangmoScene.h"
#include "MainRoomScene.h"
#include "ReadyToSortieScene.h"
#include "PartySettingScene.h"
#include "StageSelectionScene.h"
#include "OneStageScene.h"
#include "TwoStageScene.h"
#include "ThreeStageScene.h"
#include "ThreeStageScene.h"
#include "BattleEndScene.h"
#include "InventoryScene.h"
#include "SupplyScene.h"
#include "BossStageScene.h"


#include "BattleRenunciationC.h"
#include "SoundManager.h"
_int CButtonFunction::stageValue = 0;
_int CButtonFunction::squadValue = 0;
CButtonFunction::CButtonFunction()
{
}


CButtonFunction::~CButtonFunction()
{
}

void CButtonFunction::MainRoomScene()
{
	Engine::CSoundManager::GetInstance()->StopSound((_uint)Engine::EChannelID::UI_ButtonUI);
	Engine::CSoundManager::GetInstance()->StartSound(L"ButtonClick.wav", (_uint)Engine::EChannelID::UI_ButtonUI);

	CButtonManager::GetInstance()->OnDestroy();
	GET_CUR_CLIENT_SCENE->ChangeScene(CMainRoomScene::Create());
}

void CButtonFunction::StageSelectionScene()
{
	Engine::CSoundManager::GetInstance()->StopSound((_uint)Engine::EChannelID::UI_ButtonUI);
	Engine::CSoundManager::GetInstance()->StartSound(L"ButtonClick.wav", (_uint)Engine::EChannelID::UI_ButtonUI);

	CButtonManager::GetInstance()->OnDestroy();
	GET_CUR_CLIENT_SCENE->ChangeScene(CStageSelectionScene::Create());
}

void CButtonFunction::ReadyToSortieScene()
{
	Engine::CSoundManager::GetInstance()->StopSound((_uint)Engine::EChannelID::UI_ButtonUI);
	Engine::CSoundManager::GetInstance()->StartSound(L"ButtonClick.wav", (_uint)Engine::EChannelID::UI_ButtonUI);

	if (CButtonManager::GetInstance()->GetActivationButton()->GetName() == L"MainCanvas_Attack_4")
	{
		CButtonFunction::stageValue = 0;
	}
	else if (CButtonManager::GetInstance()->GetActivationButton()->GetName() == L"MainCanvas_Attack_5")
	{
		CButtonFunction::stageValue = 1;
	}
	else if (CButtonManager::GetInstance()->GetActivationButton()->GetName() == L"MainCanvas_Attack_6")
	{
		CButtonFunction::stageValue = 2;
	}
	else if (CButtonManager::GetInstance()->GetActivationButton()->GetName() == L"MainCanvas_Attack_7")
	{
		CButtonFunction::stageValue = 3;
	}

	CButtonManager::GetInstance()->OnDestroy();
	GET_CUR_CLIENT_SCENE->ChangeScene(CReadyToSortieScene::Create());
}

void CButtonFunction::PartySettingScene()
{
	Engine::CSoundManager::GetInstance()->StopSound((_uint)Engine::EChannelID::UI_ButtonUI);
	Engine::CSoundManager::GetInstance()->StartSound(L"ButtonClick.wav", (_uint)Engine::EChannelID::UI_ButtonUI);

	if (CButtonManager::GetInstance()->GetActivationButton()->GetName() == L"PlayerIS1_Button_0")
	{
		CButtonFunction::squadValue = 0;
	}
	else if (CButtonManager::GetInstance()->GetActivationButton()->GetName() == L"PlayerIS2_Button_0")
	{
		CButtonFunction::squadValue = 1;
	}
	else if (CButtonManager::GetInstance()->GetActivationButton()->GetName() == L"PlayerIS3_Button_0")
	{
		CButtonFunction::squadValue = 2;
	}

	CButtonManager::GetInstance()->OnDestroy();
	GET_CUR_CLIENT_SCENE->ChangeScene(CPartySettingScene::Create());
}

void CButtonFunction::InventoryScene()
{
	Engine::CSoundManager::GetInstance()->StopSound((_uint)Engine::EChannelID::UI_ButtonUI);
	Engine::CSoundManager::GetInstance()->StartSound(L"ButtonClick.wav", (_uint)Engine::EChannelID::UI_ButtonUI);

	CButtonManager::GetInstance()->OnDestroy();
	GET_CUR_CLIENT_SCENE->ChangeScene(CInventoryScene::Create());

}

void CButtonFunction::Sally()
{
	Engine::CSoundManager::GetInstance()->StopSound((_uint)Engine::EChannelID::UI_ButtonUI);
	Engine::CSoundManager::GetInstance()->StartSound(L"ButtonClick.wav", (_uint)Engine::EChannelID::UI_ButtonUI);

	GET_CUR_CLIENT_SCENE->FindObjectByName(L"MainCanvas")->SetIsEnabled(false);
	GET_CUR_CLIENT_SCENE->FindObjectByName(L"PlayerIS1")->SetIsEnabled(false);
	GET_CUR_CLIENT_SCENE->FindObjectByName(L"PlayerIS2")->SetIsEnabled(false);
	GET_CUR_CLIENT_SCENE->FindObjectByName(L"PlayerIS3")->SetIsEnabled(false);
	GET_CUR_CLIENT_SCENE->FindObjectByName(L"EndCanvas")->SetIsEnabled(true);

	CButtonManager::GetInstance()->OnDestroy();
	switch (CButtonFunction::stageValue)
	{
	case 0:
		GET_CUR_CLIENT_SCENE->ChangeScene(COneStageScene::Create());
		break;
	case 1:
		GET_CUR_CLIENT_SCENE->ChangeScene(CTwoStageScene::Create());
		break;
	case 2:
		GET_CUR_CLIENT_SCENE->ChangeScene(CThreeStageScene::Create());
		break;
	case 3:
		GET_CUR_CLIENT_SCENE->ChangeScene(CBossStageScene::Create());
	default:
		break;
	}

}

void CButtonFunction::BattleEndScene()
{
	Engine::CSoundManager::GetInstance()->StopSound((_uint)Engine::EChannelID::UI_ButtonUI);
	Engine::CSoundManager::GetInstance()->StartSound(L"ButtonClick.wav", (_uint)Engine::EChannelID::UI_ButtonUI);

	CButtonManager::GetInstance()->OnDestroy();
	GET_CUR_CLIENT_SCENE->ChangeScene(CBattleEndScene::Create());
}

void CButtonFunction::SupplyScene()
{
	Engine::CSoundManager::GetInstance()->StopSound((_uint)Engine::EChannelID::UI_ButtonUI);
	Engine::CSoundManager::GetInstance()->StartSound(L"ButtonClick.wav", (_uint)Engine::EChannelID::UI_ButtonUI);

	CButtonManager::GetInstance()->OnDestroy();
	GET_CUR_CLIENT_SCENE->ChangeScene(CSupplyScene::Create());
}

void CButtonFunction::BattleRenunciation()
{


	GET_CUR_CLIENT_SCENE->FindObjectByName(L"GiveUpCanvas")->SetIsEnabled(false);

	SP(Engine::CImageObject) spEmpty =
		std::dynamic_pointer_cast<Engine::CImageObject>(GET_CUR_CLIENT_SCENE->GetObjectFactory()->AddClone(L"ImageObject", true, (_int)Engine::ELayerID::UI, L""));
	spEmpty->GetTransform()->SetPosition(_float3(0, 0, 1));
	spEmpty->GetTransform()->SetSize((_float)Engine::CWndApp::GetInstance()->GetWndWidth(), (_float)Engine::CWndApp::GetInstance()->GetWndHeight(), 0.0f);

	//spEmpty->GetTexture()->AddTexture(L"FadeInOut", 0);

	spEmpty->AddComponent<CBattleRenunciationC>();
	//spEmpty->AddComponent<Engine::CFadeInOutC>();
	// ??????????
	// ???? ???? ?????????? ?????? ???? ???????????? ?? ?????????? ?????????? ??????.
}

void CButtonFunction::ObjectOn()
{
	Engine::CSoundManager::GetInstance()->StopSound((_uint)Engine::EChannelID::UI_ButtonUI);
	Engine::CSoundManager::GetInstance()->StartSound(L"PopUpIn.waw", (_uint)Engine::EChannelID::UI_ButtonUI);

	std::wstring findObjectName;
	GET_CUR_CLIENT_SCENE->GetDataStore()->GetValue(false, (_int)EDataID::UI, L"ChangeNameDataFile", CButtonManager::GetInstance()->GetActivationButton()->GetName() , findObjectName);
	GET_CUR_CLIENT_SCENE->FindObjectByName(findObjectName)->SetIsEnabled(true);
}

void CButtonFunction::ObjectOff()
{
	Engine::CSoundManager::GetInstance()->StopSound((_uint)Engine::EChannelID::UI_ButtonUI);
	Engine::CSoundManager::GetInstance()->StartSound(L"PopUpOut.waw", (_uint)Engine::EChannelID::UI_ButtonUI);

	std::wstring findObjectName;
	GET_CUR_CLIENT_SCENE->GetDataStore()->GetValue(false, (_int)EDataID::UI, L"ChangeNameDataFile", CButtonManager::GetInstance()->GetActivationButton()->GetName(), findObjectName);
	GET_CUR_CLIENT_SCENE->FindObjectByName(findObjectName)->SetIsEnabled(false);
}