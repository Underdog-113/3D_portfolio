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
#include "BattleEndScene.h"

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
	Engine::CSoundManager::GetInstance()->StartSound(L"ButtonClick.waw", (_uint)Engine::EChannelID::UI_ButtonUI);

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
	Engine::CSoundManager::GetInstance()->StartSound(L"ButtonClick.waw", (_uint)Engine::EChannelID::UI_ButtonUI);

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

	CButtonManager::GetInstance()->OnDestroy();
	GET_CUR_CLIENT_SCENE->ChangeScene(CReadyToSortieScene::Create());
}

void CButtonFunction::PartySettingScene()
{
	Engine::CSoundManager::GetInstance()->StopSound((_uint)Engine::EChannelID::UI_ButtonUI);
	Engine::CSoundManager::GetInstance()->StartSound(L"ButtonClick.waw", (_uint)Engine::EChannelID::UI_ButtonUI);

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

void CButtonFunction::Sally()
{
	Engine::CSoundManager::GetInstance()->StopSound((_uint)Engine::EChannelID::UI_ButtonUI);
	Engine::CSoundManager::GetInstance()->StartSound(L"ButtonClick.waw", (_uint)Engine::EChannelID::UI_ButtonUI);

	// 해당씬이 아니라 저장한 씬으로 이동하게 만들어야한다.
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
	default:
		break;
	}

}

void CButtonFunction::BattleEndScene()
{
	Engine::CSoundManager::GetInstance()->StopSound((_uint)Engine::EChannelID::UI_ButtonUI);
	Engine::CSoundManager::GetInstance()->StartSound(L"ButtonClick.waw", (_uint)Engine::EChannelID::UI_ButtonUI);

	CButtonManager::GetInstance()->OnDestroy();
	GET_CUR_CLIENT_SCENE->ChangeScene(CBattleEndScene::Create());
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
	// 캔버스닫고
	// 화면 점점 검은색으로 만들고 완전 검은색이되면 씬 체인지하는 오브젝트를 켜준다.
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