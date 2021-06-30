#ifndef ROBOTATTACK2PATTERN_H
#define ROBOTATTACK2PATTERN_H

#include "ATBPattern.h"

class CRobotAttack2Pattern : public CATBPattern
{
	SMART_DELETER_REGISTER

private:
	explicit CRobotAttack2Pattern();
	virtual ~CRobotAttack2Pattern();

public:
	virtual void Pattern(Engine::CObject* pOwner) override;
	virtual _float GetCost() { return m_cost; }
	static SP(CRobotAttack2Pattern) Create();

private:
	_float m_cost = 25.f;

	_float m_atkTime = 0.f; // 공격 쿨타임
	_float m_atkDis = 1.5f; // 공격 거리
	_float m_atkCool = 6.f; // 공격 쿨타임

	_float m_walkTime = 0.f; // 이동 쿨타임
	_float m_walkCool = 1.f; // 공격 끝나고 이동 시간

	_bool m_atkReady = true; // true : 공격 가능, false : 공격 불가
	_bool m_walkReady = true; // ture : 이동 가능, false : 이동 불가

	_mat m_atkMat;

	_float3 m_tPos;
	_bool m_onAtkBall = false;
};

#endif