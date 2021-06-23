#include "stdafx.h"
#include "CaptainData.h"


CCaptainData::CCaptainData()
{
}


CCaptainData::~CCaptainData()
{
}

void CCaptainData::AddCaptainData(std::wstring name, _int leval, _float experience, _float maxExperience, _int stamina, _int maxStamina, _int gold, _int diamond)
{
	m_name = name;
	m_leval = leval;
	m_experience = experience;
	m_maxExperience = maxExperience;
	m_stamina = stamina;
	m_maxStamina = maxStamina;
	m_gold = gold;
	m_diamond = diamond;
}
