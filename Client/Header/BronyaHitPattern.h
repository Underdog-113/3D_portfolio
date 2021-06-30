#ifndef BRONYAHITPATTERN_H
#define BRONYAHITPATTERN_H

#include "ATBPattern.h"

class CBronyaHitPattern : public CATBPattern
{
	SMART_DELETER_REGISTER

private:
	explicit CBronyaHitPattern();
	virtual ~CBronyaHitPattern();

public:
	virtual void Pattern(Engine::CObject* pOwner) override;
	static SP(CBronyaHitPattern) Create();

private:
	_float m_walkTime = 0.f; // 이동 쿨타임
	_bool m_walkReady = true; // ture : 이동 가능, false : 이동 불가
};

#endif