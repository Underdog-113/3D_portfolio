#ifndef BRONYARSENALPATTERN_H
#define BRONYARSENALPATTERN_H

#include "ATBPattern.h"

class CFSM_BronyaC;

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

	_float m_atkTime = 0.f; // ���� ��Ÿ��
	_float m_atkDis = 1.5f; // ���� �Ÿ�
	_float m_atkCool = 7.f; //  ��Ÿ��

	_float m_walkTime = 0.f; // �̵� ��Ÿ��
	_float m_walkCool = 1.f; // �̵� �ƽ� ��Ÿ��

	_bool m_atkReady = true; // true : ���� ����, false : ���� �Ұ�
	_bool m_walkReady = true; // ture : �̵� ����, false : �̵� �Ұ�
	_bool m_onAtk = false;
	_bool m_onEscape = false;
	_bool m_movedCenter = false;
	_bool m_movedCorner = false;
	_bool m_onArsenal = false;

	_mat m_atkMat;
	std::wstring m_curState;

	std::vector<SP(Engine::CObject)> m_vRingEffect;

private:
	_float3 m_lerpStartPos = ZERO_VECTOR;
	_float3 m_lerpEndPos = ZERO_VECTOR;
	_float m_lerpMaxTimer = 0.7f;
	_float m_lerpCurTimer = 0.f;

	_bool m_initEffect = false;
	_int m_maxRingCnt = 14;
};

#endif