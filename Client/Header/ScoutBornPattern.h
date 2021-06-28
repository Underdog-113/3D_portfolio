#ifndef SCOUTBORNPATTERN_H
#define SCOUTBORNPATTERN_H

#include "ATBPattern.h"

class CScoutBornPattern : public CATBPattern
{
	SMART_DELETER_REGISTER

private:
	explicit CScoutBornPattern();
	virtual ~CScoutBornPattern();

public:
	virtual void Pattern(Engine::CObject* pOwner) override;
	static SP(CScoutBornPattern) Create();
};

#endif