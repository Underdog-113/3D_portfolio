#ifndef GANESHABORNPATTERN_H
#define GANESHABORNPATTERN_H

#include "ATBPattern.h"

class CGaneshaBornPattern : public CATBPattern
{
	SMART_DELETER_REGISTER

private:
	explicit CGaneshaBornPattern();
	virtual ~CGaneshaBornPattern();

public:
	virtual void Pattern(Engine::CObject* pOwner) override;
	static SP(CGaneshaBornPattern) Create();
};

#endif