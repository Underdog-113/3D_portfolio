#ifndef PHASECHANGER_H
#define PHASECHANGER_H

#include "Object.h"

class CMapObject2D;
class CMonster;

class CPhaseChanger final : public Engine::CObject
{
	SMART_DELETER_REGISTER
private:
	explicit						CPhaseChanger		(void);
								   ~CPhaseChanger		(void);

public:
	static		SP(CPhaseChanger)	Create				(_bool isStatic, Engine::CScene* pScene);

				SP(Engine::CObject)	MakeClone			(void) override;
		
				void				Awake				(void) override;
				void				Start				(void) override;
		
				void				FixedUpdate			(void) override;
				void				Update				(void) override;
				void				LateUpdate			(void) override;

				void				OnDestroy			(void) override;
		
				void				OnEnable			(void) override;
				void				OnDisable			(void) override;

				void				OnTriggerEnter		(Engine::CCollisionC const* pCollisionC);
				void				OnTriggerStay		(Engine::CCollisionC const* pCollisionC);
				void				OnTriggerExit		(Engine::CCollisionC const* pCollisionC);

public:
				void				AddRestrictLine		(SP(Engine::CObject) spRestrictLine);
				void				AddMonster			(SP(CMonster) spMonster);
private:
				void				SetBasicName		(void) override;
private:
	static		_uint				m_s_uniqueID;

	typedef std::vector<SP(Engine::CObject)> _MAPOBJECT2DS;
	GETTOR			(_MAPOBJECT2DS,				m_vRestrictLine,	{},				RestrictLines)

	typedef std::vector<SP(CMonster)> _MONSTERS;
	GETTOR			(_MONSTERS,					m_vMonster,			{},				Monsters)

	GETTOR_SETTOR	(_int,						m_phaseToDie,		UNDEFINED,		PhaseToDie)
	GETTOR_SETTOR	(_bool,						m_timerStart,		false,			TimerStart)
	GETTOR			(_float,					m_spawnTimer,		0.f,			SpawnTimer)
	GETTOR			(SP(Engine::CCollisionC),	m_spCollision,		nullptr,		Collision)
};
#endif