#ifndef BRONYAESCAPEPATTERN_H
#define BRONYAESCAPEPATTERN_H

#include "ATBPattern.h"

class CBronya_Teleport_Laser;

class CBronyaEscapePattern : public CATBPattern
{
	SMART_DELETER_REGISTER

private:
	explicit CBronyaEscapePattern();
	virtual ~CBronyaEscapePattern();

public:
	virtual void Pattern(Engine::CObject* pOwner) override;
	virtual _float GetCost() { return m_cost; }
	static SP(CBronyaEscapePattern) Create();

private:
	_float3 GetEscapePos(Engine::CObject* pOwner);

private:
	//_float m_cost = 17.f;
	_float m_cost = 1.f;

	_float m_atkTime = 0.f; // ���� ��Ÿ��
	_float m_atkDis = 25.f; // ���� �Ÿ�
	_float m_atkCool = 3.f; // ���� ��Ÿ��

	_float m_walkTime = 0.f; // �̵� ��Ÿ��
	_float m_walkCool = 1.f; // �̵� �ƽ� ��Ÿ��

	_bool m_atkReady = true; // true : ���� ����, false : ���� �Ұ�
	_bool m_walkReady = true; // ture : �̵� ����, false : �̵� �Ұ�
	_bool m_onAtk = false;
	_bool m_onEscape = false;
	_bool m_onLaserOutEffect = false;
	_bool m_onLaserInEffect = false;

	_mat m_atkMat;

	SP(CBronya_Teleport_Laser) m_vLaserOutEffect = nullptr;
	SP(CBronya_Teleport_Laser) m_vLaserInEffect = nullptr;
	_float defaultEscapeEffectSizeX = 0.f;

private:
	_float3 m_lerpStartPos = ZERO_VECTOR;
	_float3 m_lerpEndPos = ZERO_VECTOR;
	_float m_lerpMaxTimer = 0.7f;
	_float m_lerpCurTimer = 0.f;
};

#endif