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
	_float m_atkTime = 0.f; // ���� ��Ÿ��
	_float m_atkDis = 1.f; // �� ���� �Ÿ�
	_float m_atkCool = 5.f; // ���� ��Ÿ��

	_float m_walkTime = 0.f; // �̵� ��Ÿ��
	_float m_walkCool = 0.3f; // ���� ������ �̵� �ð�

	_bool m_atkReady = true; // true : ���� ����, false : ���� �Ұ�
	_bool m_walkReady = true; // ture : �̵� ����, false : �̵� �Ұ�
	_bool m_onSignEffect = false;
	_bool m_onTrailEffect = false;

	_mat m_atkMat;
};

#endif