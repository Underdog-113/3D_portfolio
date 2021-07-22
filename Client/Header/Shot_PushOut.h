#pragma once
#include "Shot.h"
class CShot_PushOut : public CShot
{
public:
	struct Desc
	{
		_float startDistance = 1.f;
		_float endDistance = 1.5f;
	};

public:
	CShot_PushOut();
	~CShot_PushOut();

public:
	void Ready(CTake * pTake, _float startTimeline, _float endTimeline, void* pDesc, _float enterTimeline);

	virtual void Enter() override;
	virtual void Action() override;
	virtual void Cut() override;
	virtual void Rollback() override;

private:
	Desc m_desc;

	_float m_savedMaxDistance = 0.f;
};

