#ifndef CLIENTMACRO_H
#define CLIENTMACRO_H

//SceneMangager Macro
#define GET_CUR_CLIENT_SCENE static_cast<CClientScene*>(Engine::CSceneManager::GetInstance()->GetCurScene())

#define GET_PLAYER_DT CStageControlTower::GetInstance()->GetPlayerDeltaTime()

#endif // ! MACRO_H	

