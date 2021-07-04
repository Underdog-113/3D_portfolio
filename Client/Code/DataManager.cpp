#include "stdafx.h"
#include "DataManager.h"


#include "ClientScene.h"

IMPLEMENT_SINGLETON(CDataManager)

void CDataManager::Start()
{
	// 함장, 발키리정보 넣어주기
	m_pInStockValkyrieData = new CInStockValkyrieData();
	m_pSquadData = new CSquadData();

	CaptainInit();
	
	ItemInit(L"하급 학습 칩",50);
	ItemInit(L"특급 학습 칩",30);
	ItemInit(L"고급 학습 칩",10);

	WeaponInit(L"Weapon_Pistol_1");
	WeaponInit(L"Weapon_Pistol_2");
	WeaponInit(L"Weapon_Pistol_3");
	WeaponInit(L"Weapon_Pistol_4");
	WeaponInit(L"Weapon_Pistol_5");
	WeaponInit(L"Weapon_Pistol_6");
	WeaponInit(L"Weapon_Pistol_7");
	WeaponInit(L"Weapon_Pistol_8");
	WeaponInit(L"Weapon_Pistol_9");
	WeaponInit(L"Weapon_Pistol_10");

	WeaponInit(L"Weapon_Cross_1");
	WeaponInit(L"Weapon_Cross_2");
	WeaponInit(L"Weapon_Cross_3");
	WeaponInit(L"Weapon_Cross_4");
	WeaponInit(L"Weapon_Cross_5");
	WeaponInit(L"Weapon_Cross_6");
	WeaponInit(L"Weapon_Cross_7");
	WeaponInit(L"Weapon_Cross_8");
	WeaponInit(L"Weapon_Cross_9");
	WeaponInit(L"Weapon_Cross_10");

	WeaponInit(L"Weapon_Katana_1");
	WeaponInit(L"Weapon_Katana_2");
	WeaponInit(L"Weapon_Katana_3");
	WeaponInit(L"Weapon_Katana_4");
	WeaponInit(L"Weapon_Katana_5");
	WeaponInit(L"Weapon_Katana_6");
	WeaponInit(L"Weapon_Katana_7");
	WeaponInit(L"Weapon_Katana_8");
	WeaponInit(L"Weapon_Katana_9");
	WeaponInit(L"Weapon_Katana_10");

	ValkyrieStatusDataListInit(L"투예복백련");
	ValkyrieStatusDataListInit(L"월하초옹");
	ValkyrieStatusDataListInit(L"역신무녀");

	InStockValkyrieInit(L"투예복·백련");
	InStockValkyrieInit(L"월하초옹");
	InStockValkyrieInit(L"역신무녀");

	SquadInit(L"투예복·백련");
}

void CDataManager::Update(void)
{

}

void CDataManager::OnDestroy(void)
{
	if (m_pCaptainData != nullptr)
		delete (m_pCaptainData);

	if (m_pInStockValkyrieData != nullptr)
		delete(m_pInStockValkyrieData);

	if (m_pSquadData != nullptr)
		delete(m_pSquadData);

	for (auto& obj : m_pValkyrieStatusDataList)
	{
		delete (obj);
	}
	m_pValkyrieStatusDataList.clear();

	for (auto& obj : m_pItemDataList)
	{
		delete (obj);
	}
	m_pItemDataList.clear();
	
	for (auto& obj : m_pWeaponDataList)
	{
		delete (obj);
	}
	m_pWeaponDataList.clear();
	
}

CCaptainData * CDataManager::FindCaptainData()
{
	return m_pCaptainData;
}

CValkyrieStatusData * CDataManager::FindInStockValkyrieData(std::wstring keyValue)
{
	for (auto* data : m_pInStockValkyrieData->GetValkyriesList())
	{
		if (data->GetSubName() == keyValue)
		{
			return data;
		}
	}

	return new CValkyrieStatusData();
}

CInStockValkyrieData * CDataManager::FindInStockValkyrieData()
{
	return m_pInStockValkyrieData;
}

CValkyrieStatusData * CDataManager::FindvalkyrieStatusData(std::wstring keyValue)
{
	for (auto* data : m_pValkyrieStatusDataList)
	{
		if (data->GetSubName() == keyValue)
		{
			return data;
		}
	}

	return new CValkyrieStatusData();
}

CSquadData * CDataManager::FindSquadData()
{
	return m_pSquadData;
}

CValkyrieStatusData* CDataManager::FindSquadData(std::wstring keyValue)
{
	for (auto& data : m_pSquadData->GetValkyriesList())
	{
		if (data->GetSubName() == keyValue)
		{
			return data;
		}
	}

	return new CValkyrieStatusData();
}

std::vector<CWeaponData*> CDataManager::FindWeaponData()
{
	return m_pWeaponDataList;
}

CWeaponData * CDataManager::FindWeaponData(std::wstring keyValue)
{
	for (auto* data : m_pWeaponDataList)
	{
		if (data->GetName() == keyValue)
		{
			return data;
		}
	}

	return new CWeaponData();
}

std::vector<CItemData*> CDataManager::FindItemData()
{
	return m_pItemDataList;
}

CItemData * CDataManager::FindItemData(std::wstring keyValue)
{
	for (auto* data : m_pItemDataList)
	{
		if (data->GetName() == keyValue)
		{
			return data;
		}
	}

	return new CItemData();
}

void CDataManager::CaptainInit()
{
	Engine::CDataStore* dataStore = GET_CUR_CLIENT_SCENE->GetDataStore();
	_int dataID = (_int)EDataID::Stat;
	std::wstring objectKey = L"CaptainDataFile";

	std::wstring name;
	_int leval;
	_float experience;
	_float maxExperience;
	_int stamina;
	_int maxStamina;
	_int gold;
	_int diamond;

	dataStore->GetValue(true, dataID, objectKey, L"Name", name);
	dataStore->GetValue(true, dataID, objectKey, L"Leval", leval);
	dataStore->GetValue(true, dataID, objectKey, L"Experience", experience);
	dataStore->GetValue(true, dataID, objectKey, L"MaxExperience", maxExperience);
	dataStore->GetValue(true, dataID, objectKey, L"Stamina", stamina);
	dataStore->GetValue(true, dataID, objectKey, L"MaxStamina", maxStamina);
	dataStore->GetValue(true, dataID, objectKey, L"Gold", gold);
	dataStore->GetValue(true, dataID, objectKey, L"Diamond", diamond);

	CCaptainData* captain = new CCaptainData();
	captain->AddCaptainData(name, leval, experience, maxExperience, stamina, maxStamina, gold, diamond);

	m_pCaptainData = captain;
}

void CDataManager::ValkyrieStatusDataListInit(std::wstring valkyrieName)
{
	Engine::CDataStore* dataStore = GET_CUR_CLIENT_SCENE->GetDataStore();
	_int dataID = (_int)EDataID::Stat;
	std::wstring objectKey = valkyrieName;

	_bool enable;
	std::wstring name;
	std::wstring subName;
	_int maxHp;
	_int maxSp;
	_int damage;
	_int hoesim;
	_int defense;
	_int maxExperience;
	std::wstring rank;
	std::wstring property;
	_int maxLevel;
	std::wstring weaponType;
	std::wstring weaponName;
	std::wstring partyTextureKey;
	std::wstring squadTextureKey;
	std::wstring listTextureKey;

	dataStore->GetValue(true, dataID, objectKey, L"enable", enable);
	dataStore->GetValue(true, dataID, objectKey, L"Name", name);
	dataStore->GetValue(true, dataID, objectKey, L"subName", subName);
	dataStore->GetValue(true, dataID, objectKey, L"maxHp", maxHp);
	dataStore->GetValue(true, dataID, objectKey, L"maxSp", maxSp);
	dataStore->GetValue(true, dataID, objectKey, L"damage", damage);
	dataStore->GetValue(true, dataID, objectKey, L"hoesim", hoesim);
	dataStore->GetValue(true, dataID, objectKey, L"defense", defense);
	dataStore->GetValue(true, dataID, objectKey, L"maxExperience", maxExperience);
	dataStore->GetValue(true, dataID, objectKey, L"rank", rank);
	dataStore->GetValue(true, dataID, objectKey, L"property", property);
	dataStore->GetValue(true, dataID, objectKey, L"maxLevel", maxLevel);
	dataStore->GetValue(true, dataID, objectKey, L"weaponType", weaponType);
	dataStore->GetValue(true, dataID, objectKey, L"weaponName", weaponName);
	dataStore->GetValue(true, dataID, objectKey, L"partyTextureKey", partyTextureKey);
	dataStore->GetValue(true, dataID, objectKey, L"squadTextureKey", squadTextureKey);
	dataStore->GetValue(true, dataID, objectKey, L"ListTextureKey", listTextureKey);

	CValkyrieStatusData* valkyrie = new CValkyrieStatusData();
	valkyrie->AddValkyrieData(enable, name, subName, maxHp, maxSp, damage, hoesim, defense, maxExperience, rank, property, maxLevel, weaponType, partyTextureKey, squadTextureKey, listTextureKey);
	valkyrie->SetWeaponData(FindWeaponData(weaponName));
	valkyrie->SetBattlePower(valkyrie->GetDamage() + valkyrie->GetHoesim() + valkyrie->GetWeaponData()->GetDamage() + valkyrie->GetWeaponData()->GetHoesim());
	m_pValkyrieStatusDataList.emplace_back(valkyrie);
}

void CDataManager::ItemInit(std::wstring itemName, _int count)
{
	Engine::CDataStore* dataStore = GET_CUR_CLIENT_SCENE->GetDataStore();
	_int dataID = (_int)EDataID::Stat;
	std::wstring objectKey = itemName;

	std::wstring name;
	_int rank;
	std::wstring explanation;
	_int experience;
	std::wstring textureKey;

	dataStore->GetValue(true, dataID, objectKey, L"Name", name);

	for (auto& iter : m_pItemDataList)
	{
		if (iter->GetName() == name)
		{
			iter->SetCount(iter->GetCount() + count);
			return;
		}
	}

	dataStore->GetValue(true, dataID, objectKey, L"Rank", rank);
	dataStore->GetValue(true, dataID, objectKey, L"Explanation", explanation);
	dataStore->GetValue(true, dataID, objectKey, L"Experience", experience);
	dataStore->GetValue(true, dataID, objectKey, L"TextureKey", textureKey);

	CItemData* item = new CItemData();
	item->AddItemData(name, rank, explanation, experience, textureKey);
	item->SetCount(count);
	m_pItemDataList.emplace_back(item);
}

void CDataManager::WeaponInit(std::wstring weaponName)
{
	Engine::CDataStore* dataStore = GET_CUR_CLIENT_SCENE->GetDataStore();
	_int dataID = (_int)EDataID::Stat;
	std::wstring objectKey = weaponName;

	std::wstring name;
	_int rank;
	_float maxExperience;
	_int maxLevel;
	_int damage;
	_int hoesim;
	std::wstring explanation;
	std::wstring weaponType;
	_int damageIncrease;
	_int hoesimIncrease;
	_int upgradeGold;
	std::wstring textureKey;
	std::wstring messKey=L"";

	dataStore->GetValue(true, dataID, objectKey, L"Name", name);
	dataStore->GetValue(true, dataID, objectKey, L"Rank", rank);
	dataStore->GetValue(true, dataID, objectKey, L"MaxExperience", maxExperience);
	dataStore->GetValue(true, dataID, objectKey, L"MaxLevel", maxLevel);
	dataStore->GetValue(true, dataID, objectKey, L"Damage", damage);
	dataStore->GetValue(true, dataID, objectKey, L"Hoesim", hoesim);
	dataStore->GetValue(true, dataID, objectKey, L"Explanation", explanation);
	dataStore->GetValue(true, dataID, objectKey, L"WeaponType", weaponType);
	dataStore->GetValue(true, dataID, objectKey, L"DamageIncrease", damageIncrease);
	dataStore->GetValue(true, dataID, objectKey, L"HoesimIncrease", hoesimIncrease);
	dataStore->GetValue(true, dataID, objectKey, L"UpgradeGold", upgradeGold);
	dataStore->GetValue(true, dataID, objectKey, L"TextureKey", textureKey);
	//dataStore->GetValue(true, dataID, objectKey, L"MessKey", messKey);

	CWeaponData* weapon = new CWeaponData();
	weapon->AddWeaponData(name,
		rank,
		maxExperience,
		maxLevel,
		damage,
		hoesim,
		explanation,
		weaponType,
		damageIncrease,
		hoesimIncrease,
		upgradeGold,
		textureKey,
		messKey);

	m_pWeaponDataList.emplace_back(weapon);
}

void CDataManager::InStockValkyrieInit(std::wstring valkyrieName)
{
	CValkyrieStatusData* data = FindvalkyrieStatusData(valkyrieName);
	data->SetEnable(true);

	m_pInStockValkyrieData->AddValkyrieData(data);
}

void CDataManager::SquadInit(std::wstring valkyrieName)
{
	CValkyrieStatusData* data = FindInStockValkyrieData(valkyrieName);

	m_pSquadData->AddValkyrieData(data);
}

void CDataManager::SquadInit(_int value, std::wstring valkyrieName)
{
	CValkyrieStatusData* data = FindInStockValkyrieData(valkyrieName);

	m_pSquadData->AddValkyrieData(value,data);
}

void CDataManager::SquadDelete(std::wstring keyValue)
{
	m_pSquadData->Erase(keyValue);
}

void CDataManager::ItemDelete(std::wstring keyValue)
{
	for (auto& iter = m_pItemDataList.begin(); iter != m_pItemDataList.end(); iter++)
	{
		if ((*iter)->GetName() == keyValue)
		{
			m_pItemDataList.erase(iter);
			return;
		}

	}
	
}
