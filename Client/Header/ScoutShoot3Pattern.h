#ifndef SCOUTSHOOT3PATTERN_H
#define SCOUTSHOOT3PATTERN_H

#include "ATBPattern.h"

class CScoutShoot3Pattern : public CATBPattern
{
	SMART_DELETER_REGISTER

private:
	explicit CScoutShoot3Pattern();
	virtual ~CScoutShoot3Pattern();

public:
	virtual void Pattern(Engine::CObject* pOwner) override;
	virtual _float GetCost() { return m_cost; }
	static SP(CScoutShoot3Pattern) Create();

private:
	void SetMoveSound();

private:
	_float m_cost = 19.f;

	_float m_atkTime = 0.f; // 공격 쿨타임
	_float m_atkDis = 6.f; // 공격 거리
	_float m_atkCool = 6.f; // 공격 쿨타임

	_float m_walkTime = 0.f; // 이동 쿨타임
	_float m_walkCool = 0.20f; // 공격 끝나고 이동 시간

	_bool m_atkReady = true; // true : 공격 가능, false : 공격 불가
	_bool m_walkReady = true; // ture : 이동 가능, false : 이동 불가

	_mat m_atkMat;
	_bool m_onShoot = false;
	_bool m_firePosFix = false;
	_bool m_onEffect = false;
	_TCHAR* m_curMoveSound;

	_bool m_onWalk = false;

};

#endif