#ifndef LANCERDIEPATTERN_H
#define LANCERDIEPATTERN_H

#include "ATBPattern.h"

class CLancerDiePattern : public CATBPattern
{
	SMART_DELETER_REGISTER

private:
	explicit CLancerDiePattern();
	virtual ~CLancerDiePattern();

public:
	virtual void Pattern(Engine::CObject* pOwner) override;
	static SP(CLancerDiePattern) Create();
};

#endif