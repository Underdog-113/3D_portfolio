#include "stdafx.h"
#include "ButtonFunction.h"
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

CButtonFunction::CButtonFunction()
{
}


CButtonFunction::~CButtonFunction()
{
}

void CButtonFunction::ChangeJongScene()
{
	Engine::CSceneManager::GetInstance()->SceneChange(CChangmoScene::Create());
}

void CButtonFunction::MainRoomScene()
{
	Engine::CSceneManager::GetInstance()->SceneChange(CMainRoomScene::Create());
}

void CButtonFunction::StageSelectionScene()
{
	CLoading::Create(CStageSelectionScene::Create(), false);

	//Engine::CSceneManager::GetInstance()->SceneChange(CStageSelectionScene::Create());
}

void CButtonFunction::ReadyToSortieScene()
{
	// 들어가는 씬의정보 저장 (이름으로 비교하면될듯하다)
	Engine::CSceneManager::GetInstance()->SceneChange(CReadyToSortieScene::Create());
}

void CButtonFunction::PartySettingScene()
{
	Engine::CSceneManager::GetInstance()->SceneChange(CPartySettingScene::Create());
}

void CButtonFunction::Sally()
{
	// 해당씬이 아니라 저장한 씬으로 이동하게 만들어야한다.

	Engine::CSceneManager::GetInstance()->SceneChange(COneStageScene::Create());
	Engine::CSceneManager::GetInstance()->SceneChange(CTwoStageScene::Create());
	Engine::CSceneManager::GetInstance()->SceneChange(CThreeStageScene::Create());
}
