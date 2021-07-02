#ifndef ROBOTATTACK2PATTERN_H
#define ROBOTATTACK2PATTERN_H

#include "ATBPattern.h"

class CRobotAttack2Pattern : public CATBPattern
{
	SMART_DELETER_REGISTER

private:
	explicit CRobotAttack2Pattern();
	virtual ~CRobotAttack2Pattern();

public:
	virtual void Pattern(Engine::CObject* pOwner) override;
	virtual _float GetCost() { return m_cost; }
	static SP(CRobotAttack2Pattern) Create();

private:
	_float m_cost = 25.f;

	_float m_atkTime = 0.f; // ���� ��Ÿ��
	_float m_atkDis = 1.5f; // ���� �Ÿ�
	_float m_atkCool = 6.f; // ���� ��Ÿ��

	_float m_walkTime = 0.f; // �̵� ��Ÿ��
	_float m_walkCool = 1.f; // ���� ������ �̵� �ð�

	_bool m_atkReady = true; // true : ���� ����, false : ���� �Ұ�
	_bool m_walkReady = true; // ture : �̵� ����, false : �̵� �Ұ�

	_mat m_atkMat;

	_float3 m_tPos;
	_bool m_onAtkBall = false;
};

#endif