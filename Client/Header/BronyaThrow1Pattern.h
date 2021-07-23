#ifndef BRONYATHROW1PATTERN_H
#define BRONYATHROW1PATTERN_H

#include "ATBPattern.h"

class CBronyaThrow1Pattern : public CATBPattern
{
	SMART_DELETER_REGISTER

private:
	explicit CBronyaThrow1Pattern();
	virtual ~CBronyaThrow1Pattern();

public:
	virtual void Pattern(Engine::CObject* pOwner) override;
	virtual _float GetCost() { return m_cost; }
	static SP(CBronyaThrow1Pattern) Create();

private:
	void GetRHandMat(Engine::CObject* pOwner, _mat* pAtkBall);

private:
	//_float m_cost = 15.f;
	_float m_cost = 1.f;

	_float m_atkTime = 0.f; // ���� ��Ÿ��
	_float m_atkDis = 4.f; // ���� �Ÿ�
	_float m_atkCool = 3.f; // ���� ��Ÿ��

	_float m_walkTime = 0.f; // �̵� ��Ÿ��
	_float m_walkCool = 1.f; // �̵� �ƽ� ��Ÿ��

	_bool m_atkReady = true; // true : ���� ����, false : ���� �Ұ�
	_bool m_walkReady = true; // ture : �̵� ����, false : �̵� �Ұ�
	_bool m_onAtk = false;
	_bool m_onAtkBall = false;
	_bool m_onFastIdle = false;

	_mat m_atkMat;
	_mat* m_pRHand;
	_mat* m_pAttackBallMat;

	_int m_grenadeCnt = 3;

	_float3 m_dir;

	std::wstring m_curState;
};

#endif