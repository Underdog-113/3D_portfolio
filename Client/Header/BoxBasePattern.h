#ifndef BOXASEPATTERN_H
#define BOXASEPATTERN_H

#include "ATBPattern.h"

class CBoxBasePattern : public CATBPattern
{
	SMART_DELETER_REGISTER

private:
	explicit CBoxBasePattern();
	virtual ~CBoxBasePattern();

public:
	virtual void Pattern(Engine::CObject* pOwner) override;
	static SP(CBoxBasePattern) Create();
};

#endif