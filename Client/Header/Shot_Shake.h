#pragma once
#include "Shot.h"
class CShot_Shake :
	public CShot
{
public:
	CShot_Shake();
	~CShot_Shake();

	// CShot을(를) 통해 상속됨
	virtual void Ready(CTake * pTake, _float startTimeline, _float endTimeline, void * pDesc, _float enterTimeline) override;
	virtual void Enter() override;
	virtual void Action() override;
	virtual void Cut() override;
	virtual void Rollback() override;
};

