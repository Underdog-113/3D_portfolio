#ifndef BRONYASHOOT1PATTERN_H
#define BRONYASHOOT1PATTERN_H

#include "ATBPattern.h"

class CAttackBall;

class CBronyaShoot1Pattern : public CATBPattern
{
	SMART_DELETER_REGISTER

private:
	explicit CBronyaShoot1Pattern();
	virtual ~CBronyaShoot1Pattern();

public:
	virtual void Pattern(Engine::CObject* pOwner) override;
	virtual _float GetCost() { return m_cost; }
	static SP(CBronyaShoot1Pattern) Create();

private:
	void GetRHandMat(Engine::CObject* pOwner, _mat* pAtkBall);

private:
	//_float m_cost = 7.f;
	_float m_cost = 1.f;

	_float m_atkTime = 0.f; // ���� ��Ÿ��
	_float m_atkDis = 15.f; // ���� �Ÿ�
	_float m_atkCool = 3.f; // ���� ��Ÿ��

	_float m_walkTime = 0.f; // �̵� ��Ÿ��
	_float m_walkCool = 1.f; // �̵� �ƽ� ��Ÿ��

	_int m_bulletCnt = 19;

	_bool m_atkReady = true; // true : ���� ����, false : ���� �Ұ�
	_bool m_walkReady = true; // ture : �̵� ����, false : �̵� �Ұ�
	_bool m_onAtk = false;

	_bool m_onAtkBall = false;

	_mat m_atkMat;
	_mat* m_pRHand;
	_mat* m_pAttackBallMat;
	std::wstring m_curState;

	_float3 m_dir;
};

#endif