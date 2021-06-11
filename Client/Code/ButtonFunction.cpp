#include "stdafx.h"
#include "ButtonFunction.h"
#include "JongScene.h"
#include "ChangmoScene.h"


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
}

void CButtonFunction::StageSelectionScene()
{
}

void CButtonFunction::ReadyToSortieScene()
{
}

void CButtonFunction::PartySettingScene()
{
}