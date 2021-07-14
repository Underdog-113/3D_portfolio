#ifndef GANESHABURST02PATTERN_H
#define GANESHABURST02PATTERN_H

#include "ATBPattern.h"

class CGaneshaBurst02Pattern : public CATBPattern
{
	SMART_DELETER_REGISTER

private:
	explicit CGaneshaBurst02Pattern();
	virtual ~CGaneshaBurst02Pattern();

public:
	virtual void Pattern(Engine::CObject* pOwner) override;
	virtual _float GetCost() { return m_cost; }
	static SP(CGaneshaBurst02Pattern) Create();

private:
	_float m_cost = 15.f;

	_float m_atkTime = 0.f; // ���� ��Ÿ��
	_float m_atkDis = 30.f; // ���� �Ÿ�
	_float m_atkCool = 2.f; // ���� ��Ÿ��

	_float m_walkTime = 0.f; // �̵� ��Ÿ��
	_float m_walkCool = 0.20f; // ���� ������ �̵� �ð�

	_bool m_atkReady = true; // true : ���� ����, false : ���� �Ұ�
	_bool m_walkReady = true; // ture : �̵� ����, false : �̵� �Ұ�

	_int m_jumpCnt = 0; // �� �� ���� ����

	_mat m_atkMat;

	_bool m_onRunStart = false;
	_bool m_onBurstReadyEff = false;
	_bool m_onBurstEff = false;

	SP(Engine::CObject) m_spBurstReadyEff = nullptr;
	SP(Engine::CObject) m_spBurstEff = nullptr;
};

#endif