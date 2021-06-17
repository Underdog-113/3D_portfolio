#include "Stdafx.h"
#include "BattleRenunciationC.h"
#include "Object.h"
#include "MainRoomScene.h"

CBattleRenunciationC::CBattleRenunciationC()
{
}

CBattleRenunciationC::~CBattleRenunciationC()
{
	OnDestroy();
}

SP(Engine::CComponent) CBattleRenunciationC::MakeClone(Engine::CObject *pObject)
{
	SP(CBattleRenunciationC) spClone(new CBattleRenunciationC);
	__super::InitClone(spClone, pObject);

	return spClone;
}

void CBattleRenunciationC::Awake()
{
	__super::Awake();

	m_componentID = (_int)m_s_componentID;
}

void CBattleRenunciationC::Start(SP(CComponent) spThis)
{
	__super::Start(spThis);
}

void CBattleRenunciationC::FixedUpdate(SP(CComponent) spThis)
{

}

void CBattleRenunciationC::Update(SP(CComponent) spThis)
{
	// 배경 점점 검은색으로 만들고 a값이 1이되면 씬체인지

	CButtonManager::GetInstance()->OnDestroy();
	GET_CUR_CLIENT_SCENE->ChangeScene(CMainRoomScene::Create());
	SetIsEnabled(false);
}

void CBattleRenunciationC::LateUpdate(SP(CComponent) spThis)
{

}

void CBattleRenunciationC::OnDestroy()
{
}

void CBattleRenunciationC::OnEnable()
{
	__super::OnEnable();
}

void CBattleRenunciationC::OnDisable()
{
	__super::OnDisable();
}
