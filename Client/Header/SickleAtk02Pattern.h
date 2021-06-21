#ifndef SICKLEATK02PATTERN_H
#define SICKLEATK02PATTERN_H

#include "ATBPattern.h"

class CSickleAtk02Pattern : public CATBPattern
{
	SMART_DELETER_REGISTER

private:
	explicit CSickleAtk02Pattern();
	virtual ~CSickleAtk02Pattern();

public:
	virtual void Pattern(Engine::CObject* pOwner) override;
	virtual _float GetCost() { return m_cost; }
	static SP(CSickleAtk02Pattern) Create();

private:
	_float m_cost = 10.f;

	_float m_atkTime = 0.f; // ���� ��Ÿ��
	_float m_atkDis = 2.f; // �� ���� �Ÿ�
	_float m_atkCool = 5.f; // ���� ��Ÿ��

	_float m_walkTime = 0.f; // �̵� ��Ÿ��
	_float m_walkCool = 0.5f; // ���� ������ �̵� �ð�

	_bool m_atkReady = true; // true : ���� ����, false : ���� �Ұ�
	_bool m_walkReady = true; // ture : �̵� ����, false : �̵� �Ұ�
};

#endif