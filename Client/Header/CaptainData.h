#pragma once
class CCaptainData
{
public:
	CCaptainData();
	~CCaptainData();

	void AddCaptainData(std::wstring name,
		_int leval,
		_float experience,
		_float maxExperience,
		_int stamina,
		_int maxStamina,
		_int gold,
		_int diamond);

private:
	GETTOR_SETTOR(std::wstring, m_name, L"»ï»öÀÌ", Name);
	GETTOR_SETTOR(_int, m_leval, 1, Level);
	GETTOR_SETTOR(_float, m_experience, 0, Experience);
	GETTOR_SETTOR(_float, m_maxExperience, 0, MaxExperience);
	GETTOR_SETTOR(_int, m_stamina, 100, Stamina);
	GETTOR_SETTOR(_int, m_maxStamina, 300, MaxStamina);
	GETTOR_SETTOR(_int, m_gold, 0, Gold);
	GETTOR_SETTOR(_int, m_diamond, 0, Diamond);
};

