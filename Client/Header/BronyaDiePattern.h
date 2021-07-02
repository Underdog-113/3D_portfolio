#ifndef BRONYADIEPATTERN_H
#define BRONYADIEPATTERN_H

#include "ATBPattern.h"

class CBronyaDiePattern : public CATBPattern
{
	SMART_DELETER_REGISTER

private:
	explicit CBronyaDiePattern();
	virtual ~CBronyaDiePattern();

public:
	virtual void Pattern(Engine::CObject* pOwner) override;
	static SP(CBronyaDiePattern) Create();
};

#endif