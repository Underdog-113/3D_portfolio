#pragma once
#include "Shot.h"
class CShot_BlackFadeOut :
	public CShot
{

public:
	struct Desc
	{
		Engine::CFadeInOutC* pBlackFade = nullptr;
		_float alphaLimit = 0.f;
	};

public:
	CShot_BlackFadeOut();
	~CShot_BlackFadeOut();


	virtual _bool CheckOnTake(_float takeTimer);


	virtual void Ready(CTake * pTake, _float startTimeline, _float endTimeline, void * pDesc, _float enterTimeline) override;
	virtual void Enter() override;
	virtual void Action() override;
	virtual void Cut() override;
	virtual void Rollback() override;

private:
	Desc m_desc;
};

