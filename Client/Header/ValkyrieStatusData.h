#pragma once
class CWeaponData;
class CValkyrieStatusData
{
public:
	CValkyrieStatusData();
	~CValkyrieStatusData();

	void AddValkyrieData(
		_bool enable,
		std::wstring name,
		std::wstring subName,
		_int maxHp,
		_int maxSp,
		_int damage,
		_int hoesim,
		_int defense,
		_int maxExperience,
		std::wstring rank,
		std::wstring property,
		_int maxLevel,
		std::wstring weaponType,
		std::wstring partyTextureKey,
		std::wstring squadTextureKey,
		std::wstring listTextureKey
		);

private:
	GETTOR_SETTOR(_bool, m_enable, false, Enable);
	GETTOR_SETTOR(std::wstring, m_name , L"" , Name);
	GETTOR_SETTOR(std::wstring, m_subName, L"", SubName);
	GETTOR_SETTOR(_int , m_hp, 0, Hp);
	GETTOR_SETTOR(_int, m_maxHp, 0, MaxHp);
	GETTOR_SETTOR(_int, m_sp, 0, Sp);
	GETTOR_SETTOR(_int, m_maxSp, 0, MaxSp);
	GETTOR_SETTOR(_int, m_damage, 0, Damage);
	GETTOR_SETTOR(_int, m_hoesim, 0, Hoesim);
	GETTOR_SETTOR(_int, m_defense, 0, Defense);
	GETTOR_SETTOR(_int, m_experience, 0, Experience);
	GETTOR_SETTOR(_int, m_maxExperience, 0, MaxExperience);
	GETTOR_SETTOR(std::wstring, m_rank, L"", Rank);
	GETTOR_SETTOR(std::wstring, m_property, L"", Property);
	GETTOR_SETTOR(_int, m_battlePower, 0, BattlePower);
	GETTOR_SETTOR(_int, m_level, 0, Level);
	GETTOR_SETTOR(_int, m_maxLevel, 0, MaxLevel);
	GETTOR_SETTOR(std::wstring, m_weaponType, {}, WeaponType);
	GETTOR_SETTOR(CWeaponData*, m_weaponData, {}, WeaponData);

	// 파티원에들어갈 이미지
	GETTOR_SETTOR(std::wstring, m_partyTextureKey, {}, PartyTextureKey);
	// 스쿼드에 이미지
	GETTOR_SETTOR(std::wstring, m_squadTextureKey, {}, SquadTextureKey);
	// 발키리 목록에 들어갈 이미지
	GETTOR_SETTOR(std::wstring, m_listTextureKey, {}, ListTextureKey);
};

