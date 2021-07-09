#ifndef SICKLEAIRBORNEPATTERN_H
#define SICKLEAIRBORNEPATTERN_H

#include "ATBPattern.h"

class CSickleAirbornePattern : public CATBPattern
{
	SMART_DELETER_REGISTER

private:
	explicit CSickleAirbornePattern();
	virtual ~CSickleAirbornePattern();

public:
	virtual void Pattern(Engine::CObject* pOwner) override;
	static SP(CSickleAirbornePattern) Create();
};

#endif