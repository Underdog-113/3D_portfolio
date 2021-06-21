#ifndef SPIDERBORNPATTERN_H
#define SPIDERBORNPATTERN_H

#include "ATBPattern.h"

class CSpiderBornPattern : public CATBPattern
{
	SMART_DELETER_REGISTER

private:
	explicit CSpiderBornPattern();
	virtual ~CSpiderBornPattern();

public:
	virtual void Pattern(Engine::CObject* pOwner) override;
	static SP(CSpiderBornPattern) Create();
};

#endif