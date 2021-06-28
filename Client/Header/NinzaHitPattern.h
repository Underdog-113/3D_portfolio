#ifndef NINZAHITPATTERN_H
#define NINZAHITPATTERN_H

#include "ATBPattern.h"

class Engine::CObject;

class CNinzaHitPattern : public CATBPattern
{
	SMART_DELETER_REGISTER

private:
	explicit CNinzaHitPattern();
	virtual ~CNinzaHitPattern();

public:
	virtual void Pattern(Engine::CObject* pOwner) override;
	static SP(CNinzaHitPattern) Create();
};

#endif