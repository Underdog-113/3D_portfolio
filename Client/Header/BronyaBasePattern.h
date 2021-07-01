#ifndef BRONYABASEPATTERN_H
#define BRONYABASEPATTERN_H

#include "ATBPattern.h"

class CBronyaBasePattern : public CATBPattern
{
	SMART_DELETER_REGISTER

private:
	explicit CBronyaBasePattern();
	virtual ~CBronyaBasePattern();

public:
	virtual void Pattern(Engine::CObject* pOwner) override;
	static SP(CBronyaBasePattern) Create();

private:
	_float m_atkTime = 0.f; // 공격 쿨타임
	_float m_atkDis = 25.f; // 공격 거리
	_float m_atkCool = 3.f; // 공격 쿨타임

	_float m_walkTime = 0.f; // 이동 쿨타임
	_float m_walkCool = 0.20f; // 공격 끝나고 이동 시간

	_bool m_atkReady = true; // true : 공격 가능, false : 공격 불가
	_bool m_walkReady = true; // ture : 이동 가능, false : 이동 불가
	_bool m_onAtk = false;

	_mat m_atkMat;


};

#endif