#ifndef BRONYASTEALTHBACKPATTERN_H
#define BRONYASTEALTHBACKPATTERN_H

#include "ATBPattern.h"

class CBronyaStealthBackPattern : public CATBPattern
{
	SMART_DELETER_REGISTER

private:
	explicit CBronyaStealthBackPattern();
	virtual ~CBronyaStealthBackPattern();

public:
	virtual void Pattern(Engine::CObject* pOwner) override;
	virtual _float GetCost() { return m_cost; }
	static SP(CBronyaStealthBackPattern) Create();

private:
	_float m_cost = 0.f;
};

#endif