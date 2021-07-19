#pragma once

class CShot;
class CTake
{
public:
	CTake();
	~CTake();

public:
	void AddShot(CShot* pShot);
	void ChangeNextShot();

protected:
	GETTOR_SETTOR(std::vector<CShot*>*, m_pShotList, nullptr, MovieDirector)

protected:

};

