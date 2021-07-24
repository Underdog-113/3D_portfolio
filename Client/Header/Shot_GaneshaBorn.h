#pragma once
#include "Shot.h"
class CShot_GaneshaBorn : public CShot
{
public:
	struct Desc
	{
	};
public:
	CShot_GaneshaBorn();
	~CShot_GaneshaBorn();

	virtual void Ready(CTake * pTake, _float startTimeline, _float endTimeline, void * pDesc, _float enterTimeline) override;
	virtual void Enter() override;
	virtual void Action() override;
	virtual void Cut() override;
	virtual void Rollback() override;

private:
	Desc m_desc;

	Engine::CObject* m_pGanesha = nullptr;

	Engine::CAniCtrl* m_pActorAniCtrl = nullptr;
	_uint m_savedAnimIndex = 0;

	_double m_animPosition = 0;

	_float m_prevPlayTime = 0.f;

	_bool m_isSound = false;
};

