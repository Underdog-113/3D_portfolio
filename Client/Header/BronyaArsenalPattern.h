#ifndef BRONYARSENALPATTERN_H
#define BRONYARSENALPATTERN_H

#include "ATBPattern.h"

class CFSM_BronyaC;
class CBronya_Ult_Ring;
class CBronya_Ult_Range;
class CBronya_Ult_Laser;

class CBronyaArsenalPattern : public CATBPattern
{
	SMART_DELETER_REGISTER

private:
	explicit CBronyaArsenalPattern();
	virtual ~CBronyaArsenalPattern();

public:
	virtual void Pattern(Engine::CObject* pOwner) override;
	virtual _float GetCost() { return m_cost; }
	static SP(CBronyaArsenalPattern) Create();

private:
	void EscapePos(Engine::CObject* pOwner, SP(CFSM_BronyaC) spFSM, _float3 monPos, _float3 endPos, _bool& moved);
	void InitEffect();

private:
	//_float m_cost = 60.f;
	_float m_cost = 1.f;

	_float m_atkTime = 0.f; // 공격 쿨타임
	_float m_atkDis = 1.5f; // 공격 거리
	_float m_atkCool = 8.5f; //  쿨타임

	_float m_walkTime = 0.f; // 이동 쿨타임
	_float m_walkCool = 1.f; // 이동 맥스 쿨타임

	_bool m_atkReady = true; // true : 공격 가능, false : 공격 불가
	_bool m_walkReady = true; // ture : 이동 가능, false : 이동 불가
	_bool m_onAtk = false;
	_bool m_onEscape = false;
	_bool m_movedCenter = false;
	_bool m_movedCorner = false;
	_bool m_onArsenal = false;
	_bool m_onRingEffect = false;
	_bool m_onRangeEffect = false;

	_mat m_atkMat;
	std::wstring m_curState;

private:
	_float3 m_lerpStartPos = ZERO_VECTOR;
	_float3 m_lerpEndPos = ZERO_VECTOR;
	_float m_lerpMaxTimer = 0.7f;
	_float m_lerpCurTimer = 0.f;

	_bool m_initEffect = false;
	_bool m_onArsenalReadySound = false;
	_bool m_onArsenalShotSound = false;

	std::vector<SP(CBronya_Ult_Ring)> m_vRingEffect;
	std::vector<SP(CBronya_Ult_Range)> m_vRangeEffect;
	std::vector<SP(CBronya_Ult_Laser)> m_vLaserEffect;

	SP(CBronya_Teleport_Laser) m_vLaserOutEffect = nullptr;
	SP(CBronya_Teleport_Laser) m_vLaserInEffect = nullptr;
	_float defaultEscapeEffectSizeX = 0.f;
	_bool m_onLaserOutEffect = false;
	_bool m_onLaserInEffect = false;

	_int m_effectIndex = 0;
	SP(Engine::CObject) m_spWeapon;
};

#endif