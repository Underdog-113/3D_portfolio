#include "stdafx.h"
#include "WeaponData.h"


CWeaponData::CWeaponData()
{
}


CWeaponData::~CWeaponData()
{
}

void CWeaponData::AddWeaponData(std::wstring name, std::wstring rank, _float maxExperience, _int maxLevel, _int damage, _int hoesim, std::wstring explanation, std::wstring weaponType, _int damageIncrease, _int hoesimIncrease, _int upgradeGold,	std::wstring textureKey, std::wstring messKey)
{
	m_name = name;
	m_rank = rank;
	m_experience = 0;
	m_maxExperience = maxExperience;
	m_level = 1;
	m_maxLevel = maxLevel;
	m_damage = damage;
	m_hoesim = hoesim;
	m_explanation = explanation;
	m_weaponType = weaponType;

	m_damageIncrease = damageIncrease;
	m_hoesimIncrease = hoesimIncrease;
	m_upgradeGold = upgradeGold;

	m_textureKey = textureKey;
	m_messKey = messKey;
}
