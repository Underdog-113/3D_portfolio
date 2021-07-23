#ifndef GANESHASTUNPATTERN_H
#define GANESHASTUNPATTERN_H

#include "ATBPattern.h"

class CGaneshaStunPattern : public CATBPattern
{
	SMART_DELETER_REGISTER

private:
	explicit CGaneshaStunPattern();
	virtual ~CGaneshaStunPattern();

public:
	virtual void Pattern(Engine::CObject* pOwner) override;
	static SP(CGaneshaStunPattern) Create();

private:
	_float m_stunTime = 8.f;
	_float m_accTime = 0.f;

	_bool m_onStun = false;
	_bool m_timeEnd = false;
};

#endif