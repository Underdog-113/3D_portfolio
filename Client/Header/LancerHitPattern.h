#ifndef LANCERHITPATTERN_H
#define LANCERHITPATTERN_H

#include "ATBPattern.h"

class Engine::CObject;

class CLancerHitPattern : public CATBPattern
{
	SMART_DELETER_REGISTER

private:
	explicit CLancerHitPattern();
	virtual ~CLancerHitPattern();

public:
	virtual void Pattern(Engine::CObject* pOwner) override;
	static SP(CLancerHitPattern) Create();
};

#endif