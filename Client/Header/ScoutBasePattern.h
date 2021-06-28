#ifndef SCOUTBASEPATTERN_H
#define SCOUTBASEPATTERN_H

#include "ATBPattern.h"

class CScoutBasePattern : public CATBPattern
{
	SMART_DELETER_REGISTER

private:
	explicit CScoutBasePattern();
	virtual ~CScoutBasePattern();

public:
	virtual void Pattern(Engine::CObject* pOwner) override;
	static SP(CScoutBasePattern) Create();

private:
	_float m_atkTime = 0.f; // 공격 쿨타임
	_float m_atkDis = 6.f; // 공격 거리
	_float m_atkCool = 2.f; // 공격 쿨타임

	_float m_walkTime = 0.f; // 이동 쿨타임
	_float m_walkCool = 2.f; // 행동 끝나고 이동 시간

	_bool m_atkReady = true; // true : 공격 가능, false : 공격 불가
	_bool m_walkReady = true; // ture : 이동 가능, false : 이동 불가

	_mat m_atkMat;
};

#endif