#pragma once
#include "Shot.h"
class CShot_RotateAround : public CShot
{
public:
	struct Desc
	{
		Engine::CObject* pPivotObject = nullptr;
		_float3 offset = ZERO_VECTOR;
		_float rotateSpeed = 5.f;
	};

public:
	CShot_RotateAround();
	~CShot_RotateAround();

public:
	void Ready(CTake * pTake, _float startTimeline, _float endTimeline, void* pDesc);

	virtual void Enter() override;
	virtual void Action() override;
	virtual void Cut() override;
	virtual void Rollback() override;

private:
	Desc m_desc;

	_float3 m_pivotPos = ZERO_VECTOR;

};

