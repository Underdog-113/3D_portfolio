#ifndef LANCERBASEPATTERN_H
#define LANCERBASEPATTERN_H

#include "ATBPattern.h"

class CLancerBasePattern : public CATBPattern
{
	SMART_DELETER_REGISTER

private:
	explicit CLancerBasePattern();
	virtual ~CLancerBasePattern();

public:
	virtual void Pattern(Engine::CObject* pOwner) override;
	static SP(CLancerBasePattern) Create();

private:
	_float m_atkTime = 0.f; // ���� ��Ÿ��
	_float m_atkDis = 3.f; // ���� �Ÿ�
	_float m_atkCool = 6.f; // ���� ��Ÿ��

	_float m_walkTime = 0.f; // �̵� ��Ÿ��
	_float m_walkCool = 5.f; // ���� ������ �̵� �ð�

	_bool m_atkReady = true; // true : ���� ����, false : ���� �Ұ�
	_bool m_walkReady = true; // ture : �̵� ����, false : �̵� �Ұ�

	_mat m_atkMat;
};

#endif