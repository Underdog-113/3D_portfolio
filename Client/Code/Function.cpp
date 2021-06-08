#include "stdafx.h"
#include "Function.h"
#include "JongScene.h"


CFunction::CFunction()
{
}


CFunction::~CFunction()
{
}

void CFunction::ChangeJongScene()
{
	Engine::CSceneManager::GetInstance()->SceneChange(CJongScene::Create());
}
