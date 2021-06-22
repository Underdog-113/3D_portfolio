#ifndef SPIDERDIEPATTERN_H
#define SPIDERDIEPATTERN_H

#include "ATBPattern.h"

class CSpiderDiePattern : public CATBPattern
{
	SMART_DELETER_REGISTER

private:
	explicit CSpiderDiePattern();
	virtual ~CSpiderDiePattern();

public:
	virtual void Pattern(Engine::CObject* pOwner) override;
	static SP(CSpiderDiePattern) Create();
};

#endif