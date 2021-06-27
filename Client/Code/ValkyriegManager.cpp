#include "stdafx.h"
#include "ValkyriegManager.h"
#include "ValkyrieFSM.h"
#include "ValkyrieSelect.h"
#include "ValkyrieProperty.h"
#include "ValkyrieWeapon.h"

IMPLEMENT_SINGLETON(CValkyriegManager)
std::wstring CValkyriegManager::m_selectValkyrie = L"";
std::wstring CValkyriegManager::m_oldSelectValkyrie = L"";

void CValkyriegManager::Start(Engine::CScene * pScene)
{
	m_scene = pScene;
	FSMCreate();
}

void CValkyriegManager::Update(void)
{
	/*if(m_valkyrieFSM[m_valkyrieState])
		m_valkyrieFSM[m_valkyrieState]->Update();*/
	// 씬을 넘겨도 해당 부분이 돌고 해당 부분이 댕글리포인터가되서 문제가생김
}

void CValkyriegManager::OnDestroy(void)
{

}

void CValkyriegManager::ChangeFSM(STATE state)
{
	m_valkyrieFSM[m_valkyrieState]->End();
	m_valkyrieOldState = m_valkyrieState;
	m_valkyrieState = state;
	m_valkyrieFSM[m_valkyrieState]->Start();
}

void CValkyriegManager::ChangeFSMProperty()
{
	ChangeFSM(STATE::Property);
}

void CValkyriegManager::FSMCreate()
{
	m_valkyrieFSM[STATE::Select] = new CValkyrieSelect();
	m_valkyrieFSM[STATE::Property] = new CValkyrieProperty();
	m_valkyrieFSM[STATE::Weapon] = new CValkyrieWeapon();

	m_valkyrieFSM[STATE::Select]->Start();
}