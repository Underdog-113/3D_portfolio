#ifndef ROBOTATTACK1PATTERN_H
#define ROBOTATTACK1PATTERN_H

#include "ATBPattern.h"

class CRobotAttack1Pattern : public CATBPattern
{
	SMART_DELETER_REGISTER

private:
	explicit CRobotAttack1Pattern();
	virtual ~CRobotAttack1Pattern();

public:
	virtual void Pattern(Engine::CObject* pOwner) override;
	virtual _float GetCost() { return m_cost; }
	static SP(CRobotAttack1Pattern) Create();

private:
	_float m_cost = 5.f;

	_float m_atkTime = 0.f; // ���� ��Ÿ��
	_float m_atkDis = 1.f; // ���� �Ÿ�
	_float m_atkCool = 6.f; // ���� ��Ÿ��

	_float m_walkTime = 0.f; // �̵� ��Ÿ��
	_float m_walkCool = 1.f; // ���� ������ �̵� �ð�

	_bool m_atkReady = true; // true : ���� ����, false : ���� �Ұ�
	_bool m_walkReady = true; // ture : �̵� ����, false : �̵� �Ұ�

	_mat m_atkMat;

	_float3 m_tPos;
};

#endif