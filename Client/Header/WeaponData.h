#pragma once
class CWeaponData
{
public:
	CWeaponData();
	~CWeaponData();

	void AddWeaponData(std::wstring name,
		_int rank,
		_float maxExperience,
		_int maxLevel,
		_int damage,
		_int hoesim,
		std::wstring explanation,
		std::wstring weaponType,
		_int damageIncrease,
		_int hoesimIncrease,
		_int upgradeGold,
		std::wstring textureKey,
		std::wstring messKey);

private:
	GETTOR_SETTOR(std::wstring, m_name, L"", Name);
	GETTOR_SETTOR(_int, m_rank, 0, Rank);
	GETTOR_SETTOR(_float, m_experience, 0, Experience);
	GETTOR_SETTOR(_float, m_maxExperience, 0, MaxExperience);
	GETTOR_SETTOR(_int, m_level, 0, Level);
	GETTOR_SETTOR(_int, m_maxLevel, 0, MaxLevel);
	GETTOR_SETTOR(_int, m_damage, 0, Damage);
	GETTOR_SETTOR(_int, m_hoesim, 0, Hoesim);
	GETTOR_SETTOR(std::wstring, m_explanation, {}, Explanation);
	GETTOR_SETTOR(std::wstring, m_weaponType, {}, WeaponType);

	GETTOR_SETTOR(_int, m_damageIncrease, 0, DamageIncrease);
	GETTOR_SETTOR(_int, m_hoesimIncrease, 0, HoesimIncrease);
	GETTOR_SETTOR(_int, m_upgradeGold, 0, UpgradeGold);

	GETTOR_SETTOR(std::wstring, m_textureKey, {}, TextureKey);
	GETTOR_SETTOR(std::wstring, m_messKey, {}, MessKey);
};
