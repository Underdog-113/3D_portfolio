#include "stdafx.h"
#include "ItemData.h"


CItemData::CItemData()
{
}


CItemData::~CItemData()
{
}

void CItemData::AddItemData(std::wstring name, _int rank, std::wstring explanation, _int experience, std::wstring textureKey, STATE type)
{
	m_name = name;
	m_rank = rank;
	m_explanation = explanation;
	m_experience = experience;
	m_count = 0;
	m_type = type;
	m_textureKey = textureKey;
}

void CItemData::CountDown(_int value)
{
	m_count -= value;

	if (m_count <= 0)
	{
		CDataManager::GetInstance()->ItemDelete(m_name);
	}
}
