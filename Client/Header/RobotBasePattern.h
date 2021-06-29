#ifndef ROBOTBASEPATTERN_H
#define ROBOTBASEPATTERN_H

#include "ATBPattern.h"

class CRobotBasePattern : public CATBPattern
{
	SMART_DELETER_REGISTER

private:
	explicit CRobotBasePattern();
	virtual ~CRobotBasePattern();

public:
	virtual void Pattern(Engine::CObject* pOwner) override;
	static SP(CRobotBasePattern) Create();

private:
	_float m_atkTime = 0.f; // ���� ��Ÿ��
	_float m_atkDis = 7.f; // ���� �Ÿ�
	_float m_atkCool = 2.f; // ���� ��Ÿ��

	_float m_walkTime = 0.f; // �̵� ��Ÿ��
	_float m_walkCool = 0.3f; // ���� ������ �̵� �ð�

	_bool m_atkReady = true; // true : ���� ����, false : ���� �Ұ�
	_bool m_walkReady = true; // ture : �̵� ����, false : �̵� �Ұ�

	_mat m_atkMat;
};

#endif