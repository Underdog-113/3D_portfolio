#include "stdafx.h"
#include "ItemData.h"


CItemData::CItemData()
{
}


CItemData::~CItemData()
{
}

void CItemData::AddItemData(std::wstring name, _int rank, std::wstring explanation,	std::wstring textureKey)
{
	m_name = name;
	m_rank = rank;
	m_explanation = explanation;
	m_count = 0;
	m_textureKey = textureKey;
}
