#ifndef GANESHASTAMPPATTERN_H
#define GANESHASTAMPPATTERN_H

#include "ATBPattern.h"

class CGaneshaStampPattern : public CATBPattern
{
	SMART_DELETER_REGISTER

private:
	explicit CGaneshaStampPattern();
	virtual ~CGaneshaStampPattern();

public:
	virtual void Pattern(Engine::CObject* pOwner) override;
	virtual _float GetCost() { return m_cost; }
	static SP(CGaneshaStampPattern) Create();

private:
	_float m_cost = 15.f;

	_float m_atkTime = 0.f; // 공격 쿨타임
	_float m_atkDis = 5.f; // 공격 거리
	_float m_stampDis = 0.9f; // 찍는 거리
	_float m_atkCool = 2.f; // 공격 쿨타임

	_float m_walkTime = 0.f; // 이동 쿨타임
	_float m_walkCool = 0.20f; // 공격 끝나고 이동 시간

	_bool m_atkReady = true; // true : 공격 가능, false : 공격 불가
	_bool m_walkReady = true; // ture : 이동 가능, false : 이동 불가

	_int m_jumpCnt = 0; // 두 번 점프 여부
};

#endif