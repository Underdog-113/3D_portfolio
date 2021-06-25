#pragma once
class CValkyrieStatusData;
class CSquadData
{
public:
	CSquadData();
	~CSquadData();

	void AddValkyrieData(CValkyrieStatusData* data);
private:
	GETTOR(std::vector<CValkyrieStatusData*>, m_valkyriesList, {}, ValkyriesList);
};

