#include "stdafx.h"
#include "SquadData.h"


CSquadData::CSquadData()
{
}


CSquadData::~CSquadData()
{
}

void CSquadData::AddValkyrieData(CValkyrieStatusData * data)
{
	m_valkyriesList.emplace_back(data);
}

void CSquadData::AddValkyrieData(_int value, CValkyrieStatusData * data)
{
	m_valkyriesList[value] = data;
}

void CSquadData::Erase(std::wstring keyValue)
{
	for (auto& iter = m_valkyriesList.begin(); iter != m_valkyriesList.end(); iter++)
	{
		if ((*iter)->GetSubName() == keyValue)
		{
			m_valkyriesList.erase(iter);
			return;
		}

	}
}

