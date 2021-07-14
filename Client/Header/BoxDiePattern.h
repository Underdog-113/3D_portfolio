#ifndef BOXDIEPATTERN_H
#define BOXDIEPATTERN_H

#include "ATBPattern.h"

class CBoxDiePattern : public CATBPattern
{
	SMART_DELETER_REGISTER

private:
	explicit CBoxDiePattern();
	virtual ~CBoxDiePattern();

public:
	virtual void Pattern(Engine::CObject* pOwner) override;
	static SP(CBoxDiePattern) Create();
};

#endif