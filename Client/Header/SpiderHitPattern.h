#ifndef SPIDERHITPATTERN_H
#define SPIDERHITPATTERN_H

#include "ATBPattern.h"

class CSpiderHitPattern : public CATBPattern
{
	SMART_DELETER_REGISTER

private:
	explicit CSpiderHitPattern();
	virtual ~CSpiderHitPattern();

public:
	virtual void Pattern(Engine::CObject* pOwner) override;
	static SP(CSpiderHitPattern) Create();
};

#endif