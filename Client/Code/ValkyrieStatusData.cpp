#include "stdafx.h"
#include "ValkyrieStatusData.h"
#include "WeaponData.h"

CValkyrieStatusData::CValkyrieStatusData()
{
}


CValkyrieStatusData::~CValkyrieStatusData()
{
}

void CValkyrieStatusData::AddValkyrieData(_bool enable, std::wstring name, std::wstring subName, _float maxHp, _float maxSp, _int damage, _int hoesim, _float defense, _float maxExperience, _int rank, _int property, _int maxLevel, std::wstring weaponType, std::wstring partyTextureKey, std::wstring squadTextureKey, std::wstring listTextureKey)
{
	m_enable = enable;
	m_name = name;
	m_subName = subName;
	m_maxHp = maxHp;
	m_maxSp = maxSp;
	m_damage = damage;
	m_hoesim = hoesim;
	m_defense = defense;
	m_maxExperience = maxExperience;
	m_rank = rank;
	m_property = property;
	m_level = 1;
	m_maxLevel = maxLevel;
	m_weaponType = weaponType;

	m_partyTextureKey = partyTextureKey;
	
	m_squadTextureKey = squadTextureKey;
	
	m_listTextureKey = listTextureKey;
}

