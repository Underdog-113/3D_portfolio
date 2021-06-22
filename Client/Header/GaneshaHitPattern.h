#ifndef GANESHAHITPATTERN_H
#define GANESHAHITPATTERN_H

#include "ATBPattern.h"

class CGaneshaHitPattern : public CATBPattern
{
	SMART_DELETER_REGISTER

private:
	explicit CGaneshaHitPattern();
	virtual ~CGaneshaHitPattern();

public:
	virtual void Pattern(Engine::CObject* pOwner) override;
	static SP(CGaneshaHitPattern) Create();

private:
	_float m_maxBreakTime = 4.f;
	_float m_curBreakTime = 0.f;

	_float m_walkTime = 0.f; // 이동 쿨타임
	_bool m_walkReady = true; // ture : 이동 가능, false : 이동 불가
	_int m_jumpCnt = 0; // 두 번 점프 여부

	_bool m_onWeak = false;

	GETTOR_SETTOR(_bool, m_onHit, false, OnHit);
};

#endif