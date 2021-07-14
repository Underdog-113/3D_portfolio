#ifndef BOXBORNPATTERN_H
#define BOXBORNPATTERN_H

#include "ATBPattern.h"

class CBoxBornPattern : public CATBPattern
{
	SMART_DELETER_REGISTER

private:
	explicit CBoxBornPattern();
	virtual ~CBoxBornPattern();

public:
	virtual void Pattern(Engine::CObject* pOwner) override;
	static SP(CBoxBornPattern) Create();
};

#endif