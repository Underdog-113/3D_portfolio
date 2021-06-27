#ifndef SCOUTDIEPATTERN_H
#define SCOUTDIEPATTERN_H

#include "ATBPattern.h"

class CScoutDiePattern : public CATBPattern
{
	SMART_DELETER_REGISTER

private:
	explicit CScoutDiePattern();
	virtual ~CScoutDiePattern();

public:
	virtual void Pattern(Engine::CObject* pOwner) override;
	static SP(CScoutDiePattern) Create();
};

#endif