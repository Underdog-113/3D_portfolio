#ifndef SCOUTAIRBORNEPATTERN_H
#define SCOUTAIRBORNEPATTERN_H

#include "ATBPattern.h"

class CScoutAirbornePattern : public CATBPattern
{
	SMART_DELETER_REGISTER

private:
	explicit CScoutAirbornePattern();
	virtual ~CScoutAirbornePattern();

public:
	virtual void Pattern(Engine::CObject* pOwner) override;
	static SP(CScoutAirbornePattern) Create();
};

#endif