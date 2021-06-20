#ifndef SICKLEBORNPATTERN_H
#define SICKLEBORNPATTERN_H

#include "ATBPattern.h"

class CSickleBornPattern : public CATBPattern
{
	SMART_DELETER_REGISTER

private:
	explicit CSickleBornPattern();
	virtual ~CSickleBornPattern();

public:
	virtual void Pattern(Engine::CObject* pOwner) override;
	static SP(CSickleBornPattern) Create();

private:
	_float m_cost = 0.f;

};

#endif