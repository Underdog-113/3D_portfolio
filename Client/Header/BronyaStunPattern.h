#ifndef BRONYASTUNPATTERN_H
#define BRONYASTUNPATTERN_H

#include "ATBPattern.h"

class CBronyaStunPattern : public CATBPattern
{
	SMART_DELETER_REGISTER

private:
	explicit CBronyaStunPattern();
	virtual ~CBronyaStunPattern();

public:
	virtual void Pattern(Engine::CObject* pOwner) override;
	static SP(CBronyaStunPattern) Create();

private:
	_float m_stunTime = 8.f;
	_float m_accTime = 0.f;

	_bool m_onStun = false;
	_bool m_timeEnd = false;
};

#endif