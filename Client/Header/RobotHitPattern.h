#ifndef ROBOTHITPATTERN_H
#define ROBOTHITPATTERN_H

#include "ATBPattern.h"

class Engine::CObject;

class CRobotHitPattern : public CATBPattern
{
	SMART_DELETER_REGISTER

private:
	explicit CRobotHitPattern();
	virtual ~CRobotHitPattern();

public:
	virtual void Pattern(Engine::CObject* pOwner) override;
	static SP(CRobotHitPattern) Create();
};

#endif