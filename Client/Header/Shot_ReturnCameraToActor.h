#pragma once
#include "Shot.h"
class CShot_ReturnCameraToActor : public CShot
{
public:
	struct Desc
	{
	};

public:
	CShot_ReturnCameraToActor();
	~CShot_ReturnCameraToActor();

	virtual void Ready(CTake * pTake, _float startTimeline, _float endTimeline, void * pDesc, _float enterTimeline) override;
	virtual void Enter() override;
	virtual void Action() override;
	virtual void Cut() override;
	virtual void Rollback() override;

private:
	Desc m_desc;
};

