#pragma once
#include "Shot.h"
class CShot_BlackFadeIn : public CShot
{
public:
	struct Desc
	{
		Engine::CFadeInOutC* pBlackFade = nullptr;
		_float alphaLimit = 0.5f;
	};

public:
	CShot_BlackFadeIn();
	~CShot_BlackFadeIn();

	virtual _bool CheckOnTake(_float takeTimer);

public:
	void Ready(CTake * pTake, _float startTimeline, _float endTimeline, void* pDesc);

	virtual void Enter() override;
	virtual void Action() override;
	virtual void Cut() override;
	virtual void Rollback() override;

private:
	Desc m_desc;
};

