#ifndef LANCERIRBORNEPATTERN_H
#define LANCERIRBORNEPATTERN_H

#include "ATBPattern.h"

class CLancerAirbornePattern : public CATBPattern
{
	SMART_DELETER_REGISTER

private:
	explicit CLancerAirbornePattern();
	virtual ~CLancerAirbornePattern();

public:
	virtual void Pattern(Engine::CObject* pOwner) override;
	static SP(CLancerAirbornePattern) Create();
};

#endif