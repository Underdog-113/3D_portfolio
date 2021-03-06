#ifndef BRONYAShock1PATTERN_H
#define BRONYAShock1PATTERN_H

#include "ATBPattern.h"

class CBronyaShock1Pattern : public CATBPattern
{
	SMART_DELETER_REGISTER

private:
	explicit CBronyaShock1Pattern();
	virtual ~CBronyaShock1Pattern();

public:
	virtual void Pattern(Engine::CObject* pOwner) override;
	virtual _float GetCost() { return m_cost; }
	static SP(CBronyaShock1Pattern) Create();

private:
	void GetRHandMat(Engine::CObject* pOwner, _mat* pAtkBall);

private:
	//_float m_cost = 22.f;
	_float m_cost = 1.f;

	_float m_atkTime = 0.f; // 공격 쿨타임
	_float m_atkDis = 1.5f; // 공격 거리
	_float m_atkCool = 3.f; // 공격 쿨타임

	_float m_walkTime = 0.f; // 이동 쿨타임
	_float m_walkCool = 1.f; // 이동 맥스 쿨타임

	_bool m_atkReady = true; // true : 공격 가능, false : 공격 불가
	_bool m_walkReady = true; // ture : 이동 가능, false : 이동 불가
	_bool m_onAtk = false;

	_bool m_onAtkBall = false;
	_bool m_offAtkBall = false;
	_bool m_onShockEffect = false;

	_mat m_atkMat;
	_mat* m_pRHand;
	_mat* m_pAttackBallMat;
	std::wstring m_curState;
};

#endif