#ifndef BRONYASKILLULTRAPATTERN_H
#define BRONYASKILLULTRAPATTERN_H

#include "ATBPattern.h"

#include "BronyaStealthBackPattern.h"

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
	void ReadyUltra(Engine::CObject* pOwner, SP(CFSM_BronyaC) fsm, _float3 mPos);
	void PlayShockPattern(Engine::CObject* pOwner, SP(CFSM_BronyaC) fsm, _float3 mPos);
	void PlayEscapePattern(Engine::CObject* pOwner, SP(CFSM_BronyaC) fsm, _float3 mPos);
	void PlayStealthBackPattern(Engine::CObject* pOwner, SP(CFSM_BronyaC) fsm, _float3 mPos);
	void PlayFastIDLEPattern(Engine::CObject* pOwner, SP(CFSM_BronyaC) fsm, _float3 mPos);
	void MoveCenter(Engine::CObject* pOwner, SP(CFSM_BronyaC) spFSM, _float3 mPos);

private:
	//_float m_cost = 25.f;
	_float m_cost = 1.f;

	_float m_atkTime = 0.f; // 공격 쿨타임
	_float m_atkDis = 1.5f; // 공격 거리
	_float m_atkCool = 3.f; // 공격 쿨타임

	_float m_walkTime = 0.f; // 이동 쿨타임
	_float m_walkCool = 1.f; // 이동 맥스 쿨타임

	_bool m_atkReady = true; // true : 공격 가능, false : 공격 불가
	_bool m_walkReady = true; // ture : 이동 가능, false : 이동 불가
	_bool m_onAtk = false;
	_bool m_onEscape = false;
	_bool m_onStealthBack = false;
	_bool m_movedCenter = false;
	_bool m_onShock = false;
	_bool m_onCenter = false;
	_bool m_onUltraReady = false; // shock 쓰기 전까지 준비가 되었는지 판단

	// 내려찍는 패턴을 몇 번 반복할지 정함
	// 최소 2번, 최대 4번을 반복
	_int m_curCnt = 0;
	_int m_minCnt = 2;
	_int m_maxCnt = 4;

	// 현재 실행하고 있는 shock 패턴
	_int m_curPattern = 0;

	_mat m_atkMat;
	std::wstring m_curState;

private:
	_float3 m_centerPos = { 186.04f, -3.69f, -8.94f };


	_float3 m_lerpStartPos = ZERO_VECTOR;
	_float3 m_lerpEndPos = ZERO_VECTOR;
	_float m_lerpMaxTimer = 0.7f;
	_float m_lerpCurTimer = 0.f;

	_bool m_onHide = false;
	_bool m_beginHide = false;
	_bool m_beginReveal = false;

	SP(Engine::CObject) m_spWeapon;
	SP(CBronyaShock1Pattern) m_spShock1P = CBronyaShock1Pattern::Create();
	SP(CBronyaShock2Pattern) m_spShock2P = CBronyaShock2Pattern::Create();
	SP(CBronyaEscapePattern) m_spEscapeBackP = CBronyaEscapePattern::Create();
	SP(CBronyaStealthBackPattern) m_spStealthBackP = CBronyaStealthBackPattern::Create();
};

#endif