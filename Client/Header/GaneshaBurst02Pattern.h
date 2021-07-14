#ifndef GANESHABURST02PATTERN_H
#define GANESHABURST02PATTERN_H

#include "ATBPattern.h"

class CGaneshaBurst02Pattern : public CATBPattern
{
	SMART_DELETER_REGISTER

private:
	explicit CGaneshaBurst02Pattern();
	virtual ~CGaneshaBurst02Pattern();

public:
	virtual void Pattern(Engine::CObject* pOwner) override;
	virtual _float GetCost() { return m_cost; }
	static SP(CGaneshaBurst02Pattern) Create();

private:
	_float m_cost = 15.f;

	_float m_atkTime = 0.f; // 공격 쿨타임
	_float m_atkDis = 30.f; // 공격 거리
	_float m_atkCool = 2.f; // 공격 쿨타임

	_float m_walkTime = 0.f; // 이동 쿨타임
	_float m_walkCool = 0.20f; // 공격 끝나고 이동 시간

	_bool m_atkReady = true; // true : 공격 가능, false : 공격 불가
	_bool m_walkReady = true; // ture : 이동 가능, false : 이동 불가

	_int m_jumpCnt = 0; // 두 번 점프 여부

	_mat m_atkMat;

	_bool m_onRunStart = false;
	_bool m_onBurstReadyEff = false;
	_bool m_onBurstEff = false;

	SP(Engine::CObject) m_spBurstReadyEff = nullptr;
	SP(Engine::CObject) m_spBurstEff = nullptr;
};

#endif