#pragma once
#include "Shot.h"
class CShot_MovePivot :
	public CShot
{
public:
	struct Desc
	{
		_mat* pTargetMat = nullptr;
		_float3 startOffset = ZERO_VECTOR;
		_float3 endOffset = ZERO_VECTOR;
	};

public:
	CShot_MovePivot();
	~CShot_MovePivot();

	virtual void Ready(CTake * pTake, _float startTimeline, _float endTimeline, void * pDesc, _float enterTimeline) override;
	virtual void Enter() override;
	virtual void Action() override;
	virtual void Cut() override;
	virtual void Rollback() override;

private:
	Desc m_desc;

	_float3 m_savedPivotPos = ZERO_VECTOR;
};

