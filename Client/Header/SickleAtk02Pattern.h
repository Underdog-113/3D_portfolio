#ifndef SICKLEATK02PATTERN_H
#define SICKLEATK02PATTERN_H

#include "ATBPattern.h"

class CSickleAtk02Pattern : public CATBPattern
{
	SMART_DELETER_REGISTER

private:
	explicit CSickleAtk02Pattern();
	virtual ~CSickleAtk02Pattern();

public:
	virtual void Pattern(Engine::CObject* pOwner) override;
	static SP(CSickleAtk02Pattern) Create();

private:
	_float m_cost = 3.f;

};

#endif