#ifndef ROBOTRUNATTACKPATTERN_H
#define ROBOTRUNATTACKPATTERN_H

#include "ATBPattern.h"

class CRobotRunAttackPattern : public CATBPattern
{
	SMART_DELETER_REGISTER

private:
	explicit CRobotRunAttackPattern();
	virtual ~CRobotRunAttackPattern();

public:
	virtual void Pattern(Engine::CObject* pOwner) override;
	virtual _float GetCost() { return m_cost; }
	static SP(CRobotRunAttackPattern) Create();

private:
	_float m_cost = 7.f;

	_float m_atkTime = 0.f; // 공격 쿨타임
	_float m_atkDis = 1.5f;
	_float m_minDis = 2.f; // 최소 공격 거리
	_float m_atkCool = 6.f; // 공격 쿨타임

	_float m_walkTime = 0.f; // 이동 쿨타임
	_float m_walkCool = 0.5f; // 공격 끝나고 이동 시간

	_bool m_atkReady = true; // true : 공격 가능, false : 공격 불가
	_bool m_walkReady = true; // ture : 이동 가능, false : 이동 불가

	_mat m_atkMat;

	_bool m_onRun = false;
	_bool m_atkEnd = false;
	_bool m_aniSpeedDown = false;
	_bool m_onAtkBall = false;
	_float3 m_tPos;

	_float m_accTime = 0.f; // 달리기 카운트 현재 시간
	_float m_maxTime = 3.5f; // 달리기 카운트 맥스 시간
};

#endif