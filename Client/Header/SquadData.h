#pragma once
class CValkyrieStatusData;
class CSquadData
{
public:
	CSquadData();
	~CSquadData();

private:
	GETTOR_SETTOR(std::list<CValkyrieStatusData>, m_valkyriesList, {}, ValkyriesList);
};

