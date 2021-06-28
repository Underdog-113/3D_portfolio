#ifndef LANCERBORNPATTERN_H
#define LANCERBORNPATTERN_H

#include "ATBPattern.h"

class CLancerBornPattern : public CATBPattern
{
	SMART_DELETER_REGISTER

private:
	explicit CLancerBornPattern();
	virtual ~CLancerBornPattern();

public:
	virtual void Pattern(Engine::CObject* pOwner) override;
	static SP(CLancerBornPattern) Create();
};

#endif