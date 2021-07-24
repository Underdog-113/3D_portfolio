#ifndef GANESHAAIRBORNEPATTERN_H
#define GANESHAAIRBORNEPATTERN_H

#include "ATBPattern.h"

class CGaneshaAirbornePattern : public CATBPattern
{
	SMART_DELETER_REGISTER

private:
	explicit CGaneshaAirbornePattern();
	virtual ~CGaneshaAirbornePattern();

public:
	virtual void Pattern(Engine::CObject* pOwner) override;
	static SP(CGaneshaAirbornePattern) Create();
};

#endif