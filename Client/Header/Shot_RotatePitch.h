#pragma once
#include "Shot.h"
class CShot_RotatePitch : public CShot
{
public:
	struct Desc
	{
		_float startEulerAngle = 0.f;
		_float endEulerAngle = 30.f;

	};

public:
	CShot_RotatePitch();
	~CShot_RotatePitch();

	virtual void Ready(CTake * pTake, _float startTimeline, _float endTimeline, void* pDesc, _float enterTimeline) override;
	virtual void Enter() override;
	virtual void Action() override;
	virtual void Cut() override;
	virtual void Rollback() override;

private:
	Desc m_desc;

	_float m_savedLookAngleRight= 0.f;
};

