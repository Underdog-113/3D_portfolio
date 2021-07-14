#ifndef BRONYAShock2PATTERN_H
#define BRONYAShock2PATTERN_H

#include "ATBPattern.h"

class CBronyaShock2Pattern : public CATBPattern
{
	SMART_DELETER_REGISTER

private:
	explicit CBronyaShock2Pattern();
	virtual ~CBronyaShock2Pattern();

public:
	virtual void Pattern(Engine::CObject* pOwner) override;
	virtual _float GetCost() { return m_cost; }
	static SP(CBronyaShock2Pattern) Create();

private:
	_float m_cost = 22.f;

	_float m_atkTime = 0.f; // ���� ��Ÿ��
	_float m_atkDis = 4.5f; // ���� �Ÿ�
	_float m_atkCool = 3.f; // ���� ��Ÿ��

	_float m_walkTime = 0.f; // �̵� ��Ÿ��
	_float m_walkCool = 1.f; // �̵� �ƽ� ��Ÿ��

	_bool m_atkReady = true; // true : ���� ����, false : ���� �Ұ�
	_bool m_walkReady = true; // ture : �̵� ����, false : �̵� �Ұ�
	_bool m_onAtk = false;

	_mat m_atkMat;
	std::wstring m_curState;
};

#endif