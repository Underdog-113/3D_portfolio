#include "stdafx.h"
#include "InStockValkyrieData.h"


CInStockValkyrieData::CInStockValkyrieData()
{
}


CInStockValkyrieData::~CInStockValkyrieData()
{
}

void CInStockValkyrieData::AddValkyrieData(CValkyrieStatusData* data)
{
	m_valkyriesList.emplace_back(data);
}
