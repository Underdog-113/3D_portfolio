#ifndef BRONYABORNPATTERN_H
#define BRONYABORNPATTERN_H

#include "ATBPattern.h"

class CBronyaBornPattern : public CATBPattern
{
	SMART_DELETER_REGISTER

private:
	explicit CBronyaBornPattern();
	virtual ~CBronyaBornPattern();

public:
	virtual void Pattern(Engine::CObject* pOwner) override;
	static SP(CBronyaBornPattern) Create();
};

#endif