#include "stdafx.h"
#include "PartySettingManager.h"
#include "ButtonFunction.h"
#include "ValkyrieStatusData.h"
#include "SquadData.h"
#include "WeaponData.h"
#include "InStockValkyrieData.h"

IMPLEMENT_SINGLETON(CPartySettingManager)
void CPartySettingManager::Start(Engine::CScene * pScene)
{
	_int squadValue = CButtonFunction::squadValue;
	CValkyrieStatusData* data;
	if (squadValue < CDataManager::GetInstance()->FindSquadData()->GetValkyriesList().size())
	{
		data = CDataManager::GetInstance()->FindSquadData()->GetValkyriesList()[squadValue];
	}
	else
	{
		data = CDataManager::GetInstance()->FindInStockValkyrieData()->GetValkyriesList()[0];
	}
	
	pScene->FindObjectByName(L"PlayerCanvas_Image_2")->GetComponent<Engine::CTextureC>()->ChangeTexture(data->GetRank());
	pScene->FindObjectByName(L"PlayerCanvas_Image_4")->GetComponent<Engine::CTextureC>()->ChangeTexture(data->GetProperty());
	pScene->FindObjectByName(L"PlayerCanvas_Text_1")->GetComponent<Engine::CTextC>()->ChangeMessage(L"LV." + std::to_wstring(data->GetLevel()));
	//pScene->FindObjectByName(L"PlayerCanvas_Text_2")->GetComponent<Engine::CTextC>()->ChangeMessage(data->GetWeaponData()->GetName());
	pScene->FindObjectByName(L"PlayerCanvas_Text_5")->GetComponent<Engine::CTextC>()->ChangeMessage(data->GetSubName());
	pScene->FindObjectByName(L"PlayerCanvas_Text_6")->GetComponent<Engine::CTextC>()->ChangeMessage(data->GetName());

	if (data->GetProperty() == L"AvatarJiXie")
	{
		pScene->FindObjectByName(L"PlayerCanvas_Text_4")->GetComponent<Engine::CTextC>()->ChangeMessage(L"���");
	}
	else if (data->GetProperty() == L"AvatarShengWu")
	{
		pScene->FindObjectByName(L"PlayerCanvas_Text_4")->GetComponent<Engine::CTextC>()->ChangeMessage(L"����");
	}
	else if (data->GetProperty() == L"AvatarYiNeng")
	{
		pScene->FindObjectByName(L"PlayerCanvas_Text_4")->GetComponent<Engine::CTextC>()->ChangeMessage(L"�̴�");
	}
}

void CPartySettingManager::Update(void)
{
	if(Engine::CInputManager::GetInstance()->KeyDown(KEY_1))
	{
		
	}

	// ��ũ�ѹٿ� ���� ��ư ������Ʈ ����
	// �ش� ��ư�� Ŭ���ϸ� 
}

void CPartySettingManager::OnDestroy(void)
{

}
