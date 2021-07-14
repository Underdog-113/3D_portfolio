#ifndef SICKLESTUNPATTERN_H
#define SICKLESTUNPATTERN_H

#include "ATBPattern.h"

class CSickleStunPattern : public CATBPattern
{
	SMART_DELETER_REGISTER

private:
	explicit CSickleStunPattern();
	virtual ~CSickleStunPattern();

public:
	virtual void Pattern(Engine::CObject* pOwner) override;
	static SP(CSickleStunPattern) Create();

private:
	_float m_stunTime = 4.f;
	_float m_accTime = 0.f;

	_bool m_onStun = false;
};

#endif