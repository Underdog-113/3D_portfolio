#ifndef NINZADIEPATTERN_H
#define NINZADIEPATTERN_H

#include "ATBPattern.h"

class CNinzaDiePattern : public CATBPattern
{
	SMART_DELETER_REGISTER

private:
	explicit CNinzaDiePattern();
	virtual ~CNinzaDiePattern();

public:
	virtual void Pattern(Engine::CObject* pOwner) override;
	static SP(CNinzaDiePattern) Create();
};

#endif