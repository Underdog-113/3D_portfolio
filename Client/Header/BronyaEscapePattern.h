#ifndef BRONYAESCAPEPATTERN_H
#define BRONYAESCAPEPATTERN_H

#include "ATBPattern.h"

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
	_float m_cost = 20.f;

	_float m_atkTime = 0.f; // ���� ��Ÿ��
	_float m_atkDis = 25.f; // ���� �Ÿ�
	_float m_atkCool = 3.f; // ���� ��Ÿ��

	_float m_walkTime = 0.f; // �̵� ��Ÿ��
	_float m_walkCool = 1.f; // �̵� �ƽ� ��Ÿ��

	_bool m_atkReady = true; // true : ���� ����, false : ���� �Ұ�
	_bool m_walkReady = true; // ture : �̵� ����, false : �̵� �Ұ�
	_bool m_onAtk = false;

	_mat m_atkMat;

	_bool m_onEscape = false;
};

#endif