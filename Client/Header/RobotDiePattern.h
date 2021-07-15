#ifndef ROBOTDIEPATTERN_H
#define ROBOTDIEPATTERN_H

#include "ATBPattern.h"

class CRobotDiePattern : public CATBPattern
{
	SMART_DELETER_REGISTER

private:
	explicit CRobotDiePattern();
	virtual ~CRobotDiePattern();

public:
	virtual void Pattern(Engine::CObject* pOwner) override;
	static SP(CRobotDiePattern) Create();

private:
	SP(Engine::CObject) m_spSoftEffect;
	_bool m_isDead = false;
};

#endif