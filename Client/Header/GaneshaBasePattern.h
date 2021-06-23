#ifndef GANESHABASEPATTERN_H
#define GANESHABASEPATTERN_H

#include "ATBPattern.h"

class CGaneshaBasePattern : public CATBPattern
{
	SMART_DELETER_REGISTER

private:
	explicit CGaneshaBasePattern();
	virtual ~CGaneshaBasePattern();

public:
	virtual void Pattern(Engine::CObject* pOwner) override;
	static SP(CGaneshaBasePattern) Create();

private:
	_float m_atkTime = 0.f; // 공격 쿨타임
	_float m_atkDis = 2.61f; // 공격 거리
	_float m_atkCool = 2.f; // 공격 쿨타임

	_float m_walkTime = 0.f; // 이동 쿨타임
	_float m_walkCool = 0.20f; // 공격 끝나고 이동 시간

	_bool m_atkReady = true; // true : 공격 가능, false : 공격 불가
	_bool m_walkReady = true; // ture : 이동 가능, false : 이동 불가

	_int m_jumpCnt = 0; // 두 번 점프 여부

	_mat m_atkMat;
};

#endif