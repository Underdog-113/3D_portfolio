#pragma once

class CShot;
class CTake
{
public:
	CTake();
	~CTake();

	void StartTake();
	void ActCurrentShot();
	void EndTake();

public:
	void AddShot(CShot* pShot);
	void ChangeNextShot();

protected:
	GETTOR(std::vector<CShot*>, m_vShotList,{}, ShotList)
	CShot* m_pCurShot = nullptr;

protected:

};

