#pragma once
#include "Shot.h"
class CShot_WhiteFadeIn : public CShot
{
public:
	struct Desc
	{
		Engine::CFadeInOutC* pWhiteFade = nullptr;
	};
	
public:
	CShot_WhiteFadeIn();
	~CShot_WhiteFadeIn();

public:
	void Ready(CTake * pTake, _float startTimeline, _float endTimeline, void* pDesc, _float enterTimeline);

	virtual void Enter() override;
	virtual void Action() override;
	virtual void Cut() override;
	virtual void Rollback() override;

private:
	Desc m_desc;
};

