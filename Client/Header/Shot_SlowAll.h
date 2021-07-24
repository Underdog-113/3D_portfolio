#pragma once
#include "Shot.h"
class CShot_SlowAll :
	public CShot
{
public:
	struct Desc
	{
		_float timeSpeed = 0.1f;
	};

public:
	CShot_SlowAll();
	~CShot_SlowAll();
	
	virtual void Ready(CTake * pTake, _float startTimeline, _float endTimeline, void * pDesc, _float enterTimeline) override;
	virtual void Enter() override;
	virtual void Action() override;
	virtual void Cut() override;
	virtual void Rollback() override;

private:
	Desc m_desc;
};

