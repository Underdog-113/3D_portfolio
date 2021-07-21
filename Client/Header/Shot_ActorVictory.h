#pragma once
#include "Shot.h"
class CShot_ActorVictory : public CShot
{
public:
	struct Desc
	{
	};
public:
	CShot_ActorVictory();
	~CShot_ActorVictory();

	virtual void Ready(CTake * pTake, _float startTimeline, _float endTimeline, void * pDesc) override;
	virtual void Enter() override;
	virtual void Action() override;
	virtual void Cut() override;
	virtual void Rollback() override;

private:
	Desc m_desc;

	Engine::CAniCtrl* m_pActorAniCtrl = nullptr;
	_uint m_savedAnimIndex = 0;

	_double m_animPosition = 0;
	_uint m_victoryAnimIndex = 0;
	_uint m_victoryIdleAnimIndex = 0;

	_float m_prevPlayTime = 0.f;
};

