#ifndef PHASECHANGER_H
#define PHASECHANGER_H

#include "Object.h"

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

private:
				void				SetBasicName		(void) override;
private:
	static		_uint				m_s_uniqueID;

	GETTOR		(SP(Engine::CCollisionC),	m_spCollision,		nullptr,	Collision)
};
#endif