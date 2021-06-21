#ifndef GANESHAHITPATTERN_H
#define GANESHAHITPATTERN_H

#include "ATBPattern.h"

class CGaneshaHitPattern : public CATBPattern
{
	SMART_DELETER_REGISTER

private:
	explicit CGaneshaHitPattern();
	virtual ~CGaneshaHitPattern();

public:
	virtual void Pattern(Engine::CObject* pOwner) override;
	static SP(CGaneshaHitPattern) Create();

private:
	_float m_maxBreakTime = 4.f;
	_float m_curBreakTime = 0.f;

	_float m_walkTime = 0.f; // �̵� ��Ÿ��
	_bool m_walkReady = true; // ture : �̵� ����, false : �̵� �Ұ�
	_int m_jumpCnt = 0; // �� �� ���� ����

	_bool m_onWeak = false;

	GETTOR_SETTOR(_bool, m_onHit, false, OnHit);
};

#endif