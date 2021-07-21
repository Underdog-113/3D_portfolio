#pragma once
#include "Shot.h"
class CShot_RotateRoll :
	public CShot
{
public:
	struct Desc
	{
		_float startEulerAngle = 0.f;
		_float endEulerAngle = 30.f;

	};
public:
	CShot_RotateRoll();
	~CShot_RotateRoll();

	virtual void Ready(CTake * pTake, _float startTimeline, _float endTimeline, void * pDesc) override;
	virtual void Enter() override;
	virtual void Action() override;
	virtual void Cut() override;
	virtual void Rollback() override;

private:
	Desc m_desc;

	_float m_savedLookAngleForward = 0.f;

};

