#pragma once
#include "Shot.h"
class CShot_RotateAround : public CShot
{
public:
	struct Desc
	{
		_float3 offset = ZERO_VECTOR;

		_float startEulerRotate = 0.f;
		_float startRadianRotate = 0.f;
		_float rotateSpeed = 5.f;
		_bool isEndless = true;
	};

public:
	CShot_RotateAround();
	~CShot_RotateAround();

public:
	void Ready(CTake * pTake, _float startTimeline, _float endTimeline, void* pDesc, _float enterTimeline);

	virtual void Enter() override;
	virtual void Action() override;
	virtual void Cut() override;
	virtual void Rollback() override;

private:
	Desc m_desc;

	_float3 m_savedPivotPos = ZERO_VECTOR;
	_float m_savedLookAngleUp = 0.f;

};

