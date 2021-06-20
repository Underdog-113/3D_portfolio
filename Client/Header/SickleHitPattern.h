#ifndef SICKLEHITPATTERN_H
#define SICKLEHITPATTERN_H

#include "ATBPattern.h"

class Engine::CObject;

class CSickleHitPattern : public CATBPattern
{
	SMART_DELETER_REGISTER

private:
	explicit CSickleHitPattern();
	virtual ~CSickleHitPattern();

public:
	virtual void Pattern(Engine::CObject* pOwner) override;
	static SP(CSickleHitPattern) Create();

private:
	_float m_cost = 0.f;

};

#endif