#ifndef GANESHASTAMPPATTERN_H
#define GANESHASTAMPPATTERN_H

#include "ATBPattern.h"

class CGaneshaStampPattern : public CATBPattern
{
	SMART_DELETER_REGISTER

private:
	explicit CGaneshaStampPattern();
	virtual ~CGaneshaStampPattern();

public:
	virtual void Pattern(Engine::CObject* pOwner) override;
	virtual _float GetCost() { return m_cost; }
	static SP(CGaneshaStampPattern) Create();

private:
	_float m_cost = 15.f;

	_float m_atkTime = 0.f; // ���� ��Ÿ��
	_float m_atkDis = 5.f; // ���� �Ÿ�
	_float m_stampDis = 0.9f; // ��� �Ÿ�
	_float m_atkCool = 2.f; // ���� ��Ÿ��

	_float m_walkTime = 0.f; // �̵� ��Ÿ��
	_float m_walkCool = 0.20f; // ���� ������ �̵� �ð�

	_bool m_atkReady = true; // true : ���� ����, false : ���� �Ұ�
	_bool m_walkReady = true; // ture : �̵� ����, false : �̵� �Ұ�

	_int m_jumpCnt = 0; // �� �� ���� ����
};

#endif