#ifndef ROBOTBORNPATTERN_H
#define ROBOTBORNPATTERN_H

#include "ATBPattern.h"

class CRobotBornPattern : public CATBPattern
{
	SMART_DELETER_REGISTER

private:
	explicit CRobotBornPattern();
	virtual ~CRobotBornPattern();

public:
	virtual void Pattern(Engine::CObject* pOwner) override;
	static SP(CRobotBornPattern) Create();
};

#endif