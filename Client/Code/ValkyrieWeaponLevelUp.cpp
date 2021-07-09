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
	if (CDataManager::GetInstance()->FindItemData(L"���� ��ȭ��")->GetCount() <= 0)
	{
		CValkyriegManager::GetInstance()->ChangeFSMWeapon();
		return;
	}

	m_scene = CValkyriegManager::GetInstance()->GetScene();
	g_itemCount = 0;

	CValkyriegManager::GetInstance()->GetScene()->FindObjectByName(L"WeaponLevelUpCanvas")->SetIsEnabled(true);

	// ���� ����
	CValkyriegManager::GetInstance()->GetScene()->FindObjectByName(L"WeaponLevelUpCanvas_Text_4")->GetComponent<Engine::CTextC>()->ChangeMessage(std::to_wstring(CDataManager::GetInstance()->FindInStockValkyrieData(CValkyriegManager::g_selectValkyrie)->GetWeaponData()->GetLevel()));
	// ���� ���ݷ�
	CValkyriegManager::GetInstance()->GetScene()->FindObjectByName(L"WeaponLevelUpCanvas_Text_9")->GetComponent<Engine::CTextC>()->ChangeMessage(std::to_wstring(CDataManager::GetInstance()->FindInStockValkyrieData(CValkyriegManager::g_selectValkyrie)->GetWeaponData()->GetDamage()));
	// ���� ȸ��
	CValkyriegManager::GetInstance()->GetScene()->FindObjectByName(L"WeaponLevelUpCanvas_Text_12")->GetComponent<Engine::CTextC>()->ChangeMessage(std::to_wstring(CDataManager::GetInstance()->FindInStockValkyrieData(CValkyriegManager::g_selectValkyrie)->GetWeaponData()->GetHoesim()));

	// ȹ�� ����ġ
	// ������
	ItemCountUp();
	CValkyriegManager::GetInstance()->GetScene()->FindObjectByName(L"WeaponLevelUpCanvas_Text_14")->GetComponent<Engine::CTextC>()->ChangeMessage(L"��" + std::to_wstring(CDataManager::GetInstance()->FindItemData(L"���� ��ȭ��")->GetCount()));
	std::static_pointer_cast<Engine::CSlider>(CValkyriegManager::GetInstance()->GetScene()->FindObjectByName(L"WeaponLevelUpCanvas_Slider_0"))->SetMaxValue((_float)CDataManager::GetInstance()->FindItemData(L"���� ��ȭ��")->GetCount());
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

	_int expSum = data->GetExperience() + (CDataManager::GetInstance()->FindItemData(L"���� ��ȭ��")->GetExperience() * g_itemCount);
	
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
	CDataManager::GetInstance()->FindItemData(L"���� ��ȭ��")->CountDown(g_itemCount);
	g_itemCount = 0;
	CValkyriegManager::GetInstance()->ChangeFSMWeapon();
}

void CValkyrieWeaponLevelUp::ItemCountUp()
{
	g_itemCount++;

	if (g_itemCount >= CDataManager::GetInstance()->FindItemData(L"���� ��ȭ��")->GetCount())
		g_itemCount = CDataManager::GetInstance()->FindItemData(L"���� ��ȭ��")->GetCount();


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
1. �������� ��ȭ��Ű�� ���� ��ᰡ�ִ���üũ�ؾߵȴ�.
*/