#ifndef BRONYABASEPATTERN_H
#define BRONYABASEPATTERN_H

#include "ATBPattern.h"

class CBronyaBasePattern : public CATBPattern
{
	SMART_DELETER_REGISTER

private:
	explicit CBronyaBasePattern();
	virtual ~CBronyaBasePattern();

public:
	virtual void Pattern(Engine::CObject* pOwner) override;
	static SP(CBronyaBasePattern) Create();

private:
	_float m_atkTime = 0.f; // ���� ��Ÿ��
	_float m_atkDis = 2.61f; // ���� �Ÿ�
	_float m_atkCool = 2.f; // ���� ��Ÿ��

	_float m_walkTime = 0.f; // �̵� ��Ÿ��
	_float m_walkCool = 0.20f; // ���� ������ �̵� �ð�

	_bool m_atkReady = true; // true : ���� ����, false : ���� �Ұ�
	_bool m_walkReady = true; // ture : �̵� ����, false : �̵� �Ұ�

	_mat m_atkMat;
};

#endif