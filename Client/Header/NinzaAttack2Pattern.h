#ifndef NINZAATTACK2PATTERN_H
#define NINZAATTACK2PATTERN_H

#include "ATBPattern.h"

class CNinzaAttack2Pattern : public CATBPattern
{
	SMART_DELETER_REGISTER

private:
	explicit CNinzaAttack2Pattern();
	virtual ~CNinzaAttack2Pattern();

public:
	virtual void Pattern(Engine::CObject* pOwner) override;
	static SP(CNinzaAttack2Pattern) Create();

private:
	_float m_atkTime = 0.f; // ���� ��Ÿ��
	_float m_atkDis = 1.7f; // �� ���� �Ÿ�
	_float m_atkCool = 2.f; // ���� ��Ÿ��

	_float m_walkTime = 0.f; // �̵� ��Ÿ��
	_float m_walkCool = 0.3f; // ���� ������ �̵� �ð�

	_bool m_atkReady = true; // true : ���� ����, false : ���� �Ұ�
	_bool m_walkReady = true; // ture : �̵� ����, false : �̵� �Ұ�

	_mat m_atkMat;
};

#endif