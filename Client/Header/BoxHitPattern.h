#ifndef BOXHITPATTERN_H
#define BOXHITPATTERN_H

#include "ATBPattern.h"

class Engine::CObject;

class CBoxHitPattern : public CATBPattern
{
	SMART_DELETER_REGISTER

private:
	explicit CBoxHitPattern();
	virtual ~CBoxHitPattern();

public:
	virtual void Pattern(Engine::CObject* pOwner) override;
	static SP(CBoxHitPattern) Create();
};

#endif