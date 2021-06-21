#ifndef GANESHADIEPATTERN_H
#define GANESHADIEPATTERN_H

#include "ATBPattern.h"

class CGaneshaDiePattern : public CATBPattern
{
	SMART_DELETER_REGISTER

private:
	explicit CGaneshaDiePattern();
	virtual ~CGaneshaDiePattern();

public:
	virtual void Pattern(Engine::CObject* pOwner) override;
	static SP(CGaneshaDiePattern) Create();
};

#endif