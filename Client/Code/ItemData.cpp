#include "stdafx.h"
#include "ItemData.h"


CItemData::CItemData()
{
}


CItemData::~CItemData()
{
}

void CItemData::AddItemData(std::wstring name, std::wstring rank, std::wstring explanation, _int experience, std::wstring textureKey)
{
	m_name = name;
	m_rank = rank;
	m_explanation = explanation;
	m_experience = experience;
	m_count = 0;
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
