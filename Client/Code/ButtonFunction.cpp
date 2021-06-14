#include "stdafx.h"
#include "ButtonFunction.h"
#include "ButtonManager.h"
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

void CButtonFunction::MainRoomScene()
{
	CButtonManager::GetInstance()->OnDestroy();
	GET_CUR_CLIENT_SCENE->ChangeScene(CMainRoomScene::Create());
}

void CButtonFunction::StageSelectionScene()
{
	CButtonManager::GetInstance()->OnDestroy();
	GET_CUR_CLIENT_SCENE->ChangeScene(CStageSelectionScene::Create());
}

void CButtonFunction::ReadyToSortieScene()
{
	// ���� �������� ���� (�̸����� ���ϸ�ɵ��ϴ�)
	CButtonManager::GetInstance()->OnDestroy();
	GET_CUR_CLIENT_SCENE->ChangeScene(CReadyToSortieScene::Create());
}

void CButtonFunction::PartySettingScene()
{
	CButtonManager::GetInstance()->OnDestroy();
	GET_CUR_CLIENT_SCENE->ChangeScene(CPartySettingScene::Create());
}

void CButtonFunction::Sally()
{
	// �ش���� �ƴ϶� ������ ������ �̵��ϰ� �������Ѵ�.
	CButtonManager::GetInstance()->OnDestroy();
	GET_CUR_CLIENT_SCENE->ChangeScene(COneStageScene::Create());
	/*Engine::CSceneManager::GetInstance()->SceneChange(CTwoStageScene::Create());
	Engine::CSceneManager::GetInstance()->SceneChange(CThreeStageScene::Create());*/
}
