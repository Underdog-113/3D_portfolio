#pragma once
#include "Shot.h"
class CShot_PushIn :
	public CShot
{
public:
	struct Desc
	{
		_float startDistance = 1.5f;
		_float endDistance = 1.f;
	};

public:
	CShot_PushIn();
	~CShot_PushIn();


	virtual void Ready(CTake * pTake, _float startTimeline, _float endTimeline, void * pDesc, _float enterTimeline) override;
	
	virtual void Enter() override;
	virtual void Action() override;
	virtual void Cut() override;
	virtual void Rollback() override;

private:
	Desc m_desc;

	_float m_savedMaxDistance = 0.f;
};

