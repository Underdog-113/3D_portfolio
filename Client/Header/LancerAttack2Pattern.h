#ifndef LANCERATTACK2PATTERN_H
#define LANCERATTACK2PATTERN_H

#include "ATBPattern.h"

class CLancerAttack2Pattern : public CATBPattern
{
	SMART_DELETER_REGISTER

private:
	explicit CLancerAttack2Pattern();
	virtual ~CLancerAttack2Pattern();

public:
	virtual void Pattern(Engine::CObject* pOwner) override;
	virtual _float GetCost() { return m_cost; }
	static SP(CLancerAttack2Pattern) Create();

private:
	void SetMoveSound();

private:
	_float m_cost = 3.f;

	_float m_atkTime = 0.f; // 공격 쿨타임
	_float m_atkDis = 3.f; // 공격 거리
	_float m_atkCool = 6.f; // 공격 쿨타임

	_float m_walkTime = 0.f; // 이동 쿨타임
	_float m_walkCool = 4.f; // 공격 끝나고 이동 시간

	_bool m_atkReady = true; // true : 공격 가능, false : 공격 불가
	_bool m_walkReady = true; // ture : 이동 가능, false : 이동 불가

	_mat m_atkMat;

	_bool m_onShoot2 = false;
	_bool m_onWalk = false;

	_float3 m_beamDir = {};
	_TCHAR* m_curMoveSound;
};

#endif