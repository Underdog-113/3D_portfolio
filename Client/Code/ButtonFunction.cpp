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
	// ���� �������� ���� (�̸����� ���ϸ�ɵ��ϴ�)
	Engine::CSceneManager::GetInstance()->SceneChange(CReadyToSortieScene::Create());
}

void CButtonFunction::PartySettingScene()
{
	Engine::CSceneManager::GetInstance()->SceneChange(CPartySettingScene::Create());
}

void CButtonFunction::Sally()
{
	// �ش���� �ƴ϶� ������ ������ �̵��ϰ� �������Ѵ�.

	Engine::CSceneManager::GetInstance()->SceneChange(COneStageScene::Create());
	Engine::CSceneManager::GetInstance()->SceneChange(CTwoStageScene::Create());
	Engine::CSceneManager::GetInstance()->SceneChange(CThreeStageScene::Create());
}
