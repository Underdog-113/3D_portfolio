#ifndef ROBOTRUNATTACKPATTERN_H
#define ROBOTRUNATTACKPATTERN_H

#include "ATBPattern.h"

class CRobotRunAttackPattern : public CATBPattern
{
	SMART_DELETER_REGISTER

private:
	explicit CRobotRunAttackPattern();
	virtual ~CRobotRunAttackPattern();

public:
	virtual void Pattern(Engine::CObject* pOwner) override;
	virtual _float GetCost() { return m_cost; }
	static SP(CRobotRunAttackPattern) Create();

private:
	_float m_cost = 7.f;

	_float m_atkTime = 0.f; // ���� ��Ÿ��
	_float m_atkDis = 1.5f;
	_float m_minDis = 2.f; // �ּ� ���� �Ÿ�
	_float m_atkCool = 6.f; // ���� ��Ÿ��

	_float m_walkTime = 0.f; // �̵� ��Ÿ��
	_float m_walkCool = 0.5f; // ���� ������ �̵� �ð�

	_bool m_atkReady = true; // true : ���� ����, false : ���� �Ұ�
	_bool m_walkReady = true; // ture : �̵� ����, false : �̵� �Ұ�

	_mat m_atkMat;

	_bool m_onRun = false;
	_bool m_atkEnd = false;
	_bool m_aniSpeedDown = false;
	_bool m_onAtkBall = false;
	_float3 m_tPos;

	_float m_accTime = 0.f; // �޸��� ī��Ʈ ���� �ð�
	_float m_maxTime = 3.5f; // �޸��� ī��Ʈ �ƽ� �ð�
};

#endif