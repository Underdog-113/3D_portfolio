#ifndef NINZABORNPATTERN_H
#define NINZABORNPATTERN_H

#include "ATBPattern.h"

class CNinzaBornPattern : public CATBPattern
{
	SMART_DELETER_REGISTER

private:
	explicit CNinzaBornPattern();
	virtual ~CNinzaBornPattern();

public:
	virtual void Pattern(Engine::CObject* pOwner) override;
	static SP(CNinzaBornPattern) Create();
};

#endif