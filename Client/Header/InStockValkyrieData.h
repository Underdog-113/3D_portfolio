#pragma once
class CValkyrieStatusData;
class CInStockValkyrieData
{
public:
	CInStockValkyrieData();
	~CInStockValkyrieData();

	void AddValkyrieData(CValkyrieStatusData* data);
private:
	GETTOR(std::vector<CValkyrieStatusData*>, m_valkyriesList, {}, ValkyriesList);
};

