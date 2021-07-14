#ifndef SPIDERBASEPATTERN_H
#define SPIDERBASEPATTERN_H

#include "ATBPattern.h"

class CSpiderBasePattern : public CATBPattern
{
	SMART_DELETER_REGISTER

private:
	explicit CSpiderBasePattern();
	virtual ~CSpiderBasePattern();

public:
	virtual void Pattern(Engine::CObject* pOwner) override;
	static SP(CSpiderBasePattern) Create();

private:
	_float m_atkTime = 0.f; // ���� ��Ÿ��
	_float m_atkDis = 1.2f; // �� ���� �Ÿ�
	_float m_atkCool = 2.f; // ���� ��Ÿ��

	_float m_walkTime = 0.f; // �̵� ��Ÿ��
	_float m_walkCool = 0.3f; // ���� ������ �̵� �ð�

	_bool m_atkReady = true; // true : ���� ����, false : ���� �Ұ�
	_bool m_walkReady = true; // ture : �̵� ����, false : �̵� �Ұ�

	_mat m_explosionPosMat;

	/* for.effect */
	SP(Engine::CObject) m_spSoftEffect;
	_bool m_onEffect = false;
	_bool m_onAtk = false;
};

#endif