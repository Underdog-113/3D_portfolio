#ifndef SCOUTHITPATTERN_H
#define SCOUTHITPATTERN_H

#include "ATBPattern.h"

class Engine::CObject;

class CScoutHitPattern : public CATBPattern
{
	SMART_DELETER_REGISTER

private:
	explicit CScoutHitPattern();
	virtual ~CScoutHitPattern();

public:
	virtual void Pattern(Engine::CObject* pOwner) override;
	static SP(CScoutHitPattern) Create();
};

#endif