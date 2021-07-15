#include "stdafx.h"
#include "SupplyOut.h"

CSupplyOut::CSupplyOut()
{

}

CSupplyOut::~CSupplyOut()
{
}

void CSupplyOut::Start()
{
	_int a = CSupplyManager::GetInstance()->GetOutCount();
	_int b = CSupplyManager::GetInstance()->GetSupplyOldState();

	Engine::GET_CUR_SCENE->FindObjectByName(L"MainCanvas_Button_2")->SetIsEnabled(false);
	Engine::GET_CUR_SCENE->FindObjectByName(L"MainCanvas_Button_3")->SetIsEnabled(false);
}

void CSupplyOut::End()
{
	Engine::GET_CUR_SCENE->FindObjectByName(L"MainCanvas_Button_2")->SetIsEnabled(true);
	Engine::GET_CUR_SCENE->FindObjectByName(L"MainCanvas_Button_3")->SetIsEnabled(true);
}

_uint CSupplyOut::FixedUpdate()
{
	return _uint();
}

_uint CSupplyOut::Update()
{
	return _uint();
}

_uint CSupplyOut::LateUpdate()
{
	return _uint();
}

void CSupplyOut::OnDestroy(void)
{
}
void CSupplyOut::RandomBox()
{
	m_timer -= GET_DT;
	if (m_timer <= 0)
	{
		//ItemInit(L"하급 학습 칩", 50);
	}
}
void CSupplyOut::RandoBoxList()
{
}
/*
0은 무기
1은 재료

count만큼 소환
*/