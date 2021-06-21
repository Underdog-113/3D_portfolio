#ifndef SICKLEDIEPATTERN_H
#define SICKLEDIEPATTERN_H

#include "ATBPattern.h"

class CSickleDiePattern : public CATBPattern
{
	SMART_DELETER_REGISTER

private:
	explicit CSickleDiePattern();
	virtual ~CSickleDiePattern();

public:
	virtual void Pattern(Engine::CObject* pOwner) override;
	static SP(CSickleDiePattern) Create();
};

#endif