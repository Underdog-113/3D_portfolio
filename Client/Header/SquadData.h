#pragma once
class CValkyrieStatusData;
class CSquadData
{
public:
	CSquadData();
	~CSquadData();

	void AddValkyrieData(CValkyrieStatusData* data);
	void AddValkyrieData(_int value, CValkyrieStatusData* data);
	void Erase(std::wstring keyValue);
private:
	GETTOR(std::vector<CValkyrieStatusData*>, m_valkyriesList, {}, ValkyriesList);
};

