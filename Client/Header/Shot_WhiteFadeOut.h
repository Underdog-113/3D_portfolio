#pragma once
#include "Shot.h"
class CShot_WhiteFadeOut : public CShot
{
public:
	struct Desc
	{
		Engine::CFadeInOutC* pWhiteFade = nullptr;
	};

public:
	CShot_WhiteFadeOut();
	~CShot_WhiteFadeOut();

public:
	void Ready(CTake * pTake, _float startTimeline, _float endTimeline, void* pDesc, _float enterTimeline);

	virtual void Enter() override;
	virtual void Action() override;
	virtual void Cut() override;
	virtual void Rollback() override;

private:
	Desc m_desc;
};

