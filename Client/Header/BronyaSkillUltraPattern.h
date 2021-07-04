#ifndef BRONYASKILLULTRAPATTERN_H
#define BRONYASKILLULTRAPATTERN_H

#include "ATBPattern.h"

class CFSM_BronyaC;

class CBronyaSkillUltraPattern : public CATBPattern
{
	SMART_DELETER_REGISTER

private:
	explicit CBronyaSkillUltraPattern();
	virtual ~CBronyaSkillUltraPattern();

public:
	virtual void Pattern(Engine::CObject* pOwner) override;
	virtual _float GetCost() { return m_cost; }
	static SP(CBronyaSkillUltraPattern) Create();

private:
	void MoveCenter(Engine::CObject* pOwner, SP(CFSM_BronyaC) spFSM, _float3 mPos);

private:
	_float m_cost = /*35.f;*/ 3.f;

	_float m_atkTime = 0.f; // 공격 쿨타임
	_float m_atkDis = 1.5f; // 공격 거리
	_float m_atkCool = 3.f; // 공격 쿨타임

	_float m_walkTime = 0.f; // 이동 쿨타임
	_float m_walkCool = 1.f; // 이동 맥스 쿨타임

	_bool m_atkReady = true; // true : 공격 가능, false : 공격 불가
	_bool m_walkReady = true; // ture : 이동 가능, false : 이동 불가
	_bool m_onAtk = false;
	_bool m_onEscape = false;
	_bool m_movedCenter = false;
	_bool m_onShock = false;

	_mat m_atkMat;
	std::wstring m_curState;

private:
	_float3 m_lerpStartPos = ZERO_VECTOR;
	_float3 m_lerpEndPos = ZERO_VECTOR;
	_float m_lerpMaxTimer = 0.7f;
	_float m_lerpCurTimer = 0.f;

	SP(CBronyaShock1Pattern) m_spShock1P = CBronyaShock1Pattern::Create();
};

#endif