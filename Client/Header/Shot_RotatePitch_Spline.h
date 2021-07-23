#pragma once
#include "Shot.h"

class CSplineCurve;
class CShot_RotatePitch_Spline :
	public CShot
{
public:
	struct Desc
	{
		CSplineCurve* angleCurve;
	};

public:
	CShot_RotatePitch_Spline();
	~CShot_RotatePitch_Spline();

	virtual void Ready(CTake * pTake, _float startTimeline, _float endTimeline, void * pDesc, _float enterTimeline) override;
	virtual void Enter() override;
	virtual void Action() override;
	virtual void Cut() override;
	virtual void Rollback() override;

private:
	Desc m_desc;

	_float m_savedLookAngleRight = 0.f;
};

