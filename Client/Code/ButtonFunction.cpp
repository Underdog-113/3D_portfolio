#include "stdafx.h"
#include "ButtonFunction.h"
#include "JongScene.h"


CButtonFunction::CButtonFunction()
{
}


CButtonFunction::~CButtonFunction()
{
}

void CButtonFunction::ChangeJongScene()
{
	Engine::CSceneManager::GetInstance()->SceneChange(CJongScene::Create());
}
