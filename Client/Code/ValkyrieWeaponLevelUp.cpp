#include "stdafx.h"
#include "ValkyrieWeaponLevelUp.h"

_int CValkyrieWeaponLevelUp::g_itemCount = 0;
CValkyrieWeaponLevelUp::CValkyrieWeaponLevelUp()
{
}

CValkyrieWeaponLevelUp::~CValkyrieWeaponLevelUp()
{
}

void CValkyrieWeaponLevelUp::Start()
{
	if (CDataManager::GetInstance()->FindItemData(L"무기 강화제")->GetCount() <= 0)
	{
		CValkyriegManager::GetInstance()->ChangeFSMWeapon();
		return;
	}

	m_scene = CValkyriegManager::GetInstance()->GetScene();
	g_itemCount = 0;

	CValkyriegManager::GetInstance()->GetScene()->FindObjectByName(L"WeaponLevelUpCanvas")->SetIsEnabled(true);

	// 현재 레벨
	CValkyriegManager::GetInstance()->GetScene()->FindObjectByName(L"WeaponLevelUpCanvas_Text_4")->GetComponent<Engine::CTextC>()->ChangeMessage(std::to_wstring(CDataManager::GetInstance()->FindInStockValkyrieData(CValkyriegManager::g_selectValkyrie)->GetWeaponData()->GetLevel()));
	// 현제 공격력
	CValkyriegManager::GetInstance()->GetScene()->FindObjectByName(L"WeaponLevelUpCanvas_Text_9")->GetComponent<Engine::CTextC>()->ChangeMessage(std::to_wstring(CDataManager::GetInstance()->FindInStockValkyrieData(CValkyriegManager::g_selectValkyrie)->GetWeaponData()->GetDamage()));
	// 현제 회심
	CValkyriegManager::GetInstance()->GetScene()->FindObjectByName(L"WeaponLevelUpCanvas_Text_12")->GetComponent<Engine::CTextC>()->ChangeMessage(std::to_wstring(CDataManager::GetInstance()->FindInStockValkyrieData(CValkyriegManager::g_selectValkyrie)->GetWeaponData()->GetHoesim()));

	// 획득 경험치
	// 사용수량
	ItemCountUp();
	CValkyriegManager::GetInstance()->GetScene()->FindObjectByName(L"WeaponLevelUpCanvas_Text_14")->GetComponent<Engine::CTextC>()->ChangeMessage(L"×" + std::to_wstring(CDataManager::GetInstance()->FindItemData(L"무기 강화제")->GetCount()));
	std::static_pointer_cast<Engine::CSlider>(CValkyriegManager::GetInstance()->GetScene()->FindObjectByName(L"WeaponLevelUpCanvas_Slider_0"))->SetMaxValue((_float)CDataManager::GetInstance()->FindItemData(L"무기 강화제")->GetCount());
}

void CValkyrieWeaponLevelUp::End()
{
	CValkyriegManager::GetInstance()->GetScene()->FindObjectByName(L"WeaponLevelUpCanvas")->SetIsEnabled(false);
}

_uint CValkyrieWeaponLevelUp::FixedUpdate()
{
	return _uint();
}

_uint CValkyrieWeaponLevelUp::Update()
{
	return _uint();
}

_uint CValkyrieWeaponLevelUp::LateUpdate()
{
	return _uint();
}

void CValkyrieWeaponLevelUp::OnDestroy(void)
{
}

void CValkyrieWeaponLevelUp::LevelUp()
{
	CWeaponData* data = CDataManager::GetInstance()->FindInStockValkyrieData(CValkyriegManager::g_selectValkyrie)->GetWeaponData();

	_int expSum = data->GetExperience() + (CDataManager::GetInstance()->FindItemData(L"무기 강화제")->GetExperience() * g_itemCount);
	
	while (true)
	{
		if (expSum >= data->GetMaxExperience())
		{
			data->LevelUp();
			expSum -= data->GetMaxExperience();
			data->SetMaxExperience((_int)(data->GetMaxExperience() * 1.5));
			continue;
		}

		break;
	}

	data->SetExperience(expSum);
	CDataManager::GetInstance()->FindItemData(L"무기 강화제")->CountDown(g_itemCount);
	g_itemCount = 0;
	CValkyriegManager::GetInstance()->ChangeFSMWeapon();
}

void CValkyrieWeaponLevelUp::ItemCountUp()
{
	g_itemCount++;

	if (g_itemCount >= CDataManager::GetInstance()->FindItemData(L"무기 강화제")->GetCount())
		g_itemCount = CDataManager::GetInstance()->FindItemData(L"무기 강화제")->GetCount();


	CValkyriegManager::GetInstance()->GetScene()->FindObjectByName(L"WeaponLevelUpCanvas_Text_7")->GetComponent<Engine::CTextC>()->ChangeMessage(std::to_wstring(g_itemCount));
	std::static_pointer_cast<Engine::CSlider>(CValkyriegManager::GetInstance()->GetScene()->FindObjectByName(L"WeaponLevelUpCanvas_Slider_0"))->SetValue((_float)g_itemCount);


	ItemCountUiHelp();

}

void CValkyrieWeaponLevelUp::ItemCountDown()
{
	g_itemCount--;

	if (g_itemCount <= 0)
		g_itemCount = 1;

	CValkyriegManager::GetInstance()->GetScene()->FindObjectByName(L"WeaponLevelUpCanvas_Text_7")->GetComponent<Engine::CTextC>()->ChangeMessage(std::to_wstring(g_itemCount));
	std::static_pointer_cast<Engine::CSlider>(CValkyriegManager::GetInstance()->GetScene()->FindObjectByName(L"WeaponLevelUpCanvas_Slider_0"))->SetValue((_float)g_itemCount);


	ItemCountUiHelp();

}

void CValkyrieWeaponLevelUp::ItemCountUiHelp()
{
	CWeaponData* data = CDataManager::GetInstance()->FindInStockValkyrieData(CValkyriegManager::g_selectValkyrie)->GetWeaponData();

	_int expSum = data->GetExperience() + (500 * g_itemCount);
	_int levalUpSum = data->GetLevel();
	_int nextExp = data->GetMaxExperience();
	_int damage = data->GetDamage();
	_int hoesim = data->GetHoesim();

	CValkyriegManager::GetInstance()->GetScene()->FindObjectByName(L"WeaponLevelUpCanvas_Text_2")->GetComponent<Engine::CTextC>()->ChangeMessage(std::to_wstring(expSum - data->GetExperience()));
	while (true)
	{
		if (expSum >= nextExp)
		{
			levalUpSum++;
			expSum -= nextExp;
			nextExp = (int)(nextExp  * 1.5);
			damage += data->GetDamageIncrease();
			hoesim += data->GetHoesimIncrease();
			continue;
		}

		break;
	}

	CValkyriegManager::GetInstance()->GetScene()->FindObjectByName(L"WeaponLevelUpCanvas_Text_5")->GetComponent<Engine::CTextC>()->ChangeMessage(std::to_wstring(levalUpSum));
	CValkyriegManager::GetInstance()->GetScene()->FindObjectByName(L"WeaponLevelUpCanvas_Text_10")->GetComponent<Engine::CTextC>()->ChangeMessage(std::to_wstring(damage));
	CValkyriegManager::GetInstance()->GetScene()->FindObjectByName(L"WeaponLevelUpCanvas_Text_13")->GetComponent<Engine::CTextC>()->ChangeMessage(std::to_wstring(hoesim));

}


/*
1. 아이템을 강화시키기 위한 재료가있는지체크해야된다.
*/