#include "stdafx.h"
#include "SquadData.h"
#include "ValkyrieStatusData.h"


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
