#ifndef BRONYAAIRBORNEPATTERN_H
#define BRONYAAIRBORNEPATTERN_H

#include "ATBPattern.h"

class CBronyaAirbornePattern : public CATBPattern
{
	SMART_DELETER_REGISTER

private:
	explicit CBronyaAirbornePattern();
	virtual ~CBronyaAirbornePattern();

public:
	virtual void Pattern(Engine::CObject* pOwner) override;
	static SP(CBronyaAirbornePattern) Create();
};

#endif