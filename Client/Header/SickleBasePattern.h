#ifndef SICKLEBASEPATTERN_H
#define SICKLEBASEPATTERN_H

#include "ATBPattern.h"

class CSickleBasePattern : public CATBPattern
{
	SMART_DELETER_REGISTER

private:
	explicit CSickleBasePattern();
	virtual ~CSickleBasePattern();

public:
	virtual void Pattern(Engine::CObject* pOwner) override;
	static SP(CSickleBasePattern) Create();

private:
	_float m_cost = 0.f;

	_float m_atkTime = 0.f; // ���� ��Ÿ��
	_float m_atkDis = 1.2f; // �� ���� �Ÿ�
	_float m_atkCool = 2.f; // ���� ��Ÿ��

	_float m_walkTime = 0.f; // �̵� ��Ÿ��
	_float m_walkCool = 0.3f; // ���� ������ �̵� �ð�

	_bool m_atkReady = true; // true : ���� ����, false : ���� �Ұ�
	_bool m_walkReady = true; // ture : �̵� ����, false : �̵� �Ұ�
};

#endif