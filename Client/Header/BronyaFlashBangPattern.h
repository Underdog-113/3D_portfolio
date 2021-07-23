#ifndef BRONYAFLASHBANGPATTERN_H
#define BRONYAFLASHBANGPATTERN_H

#include "ATBPattern.h"

class CBronyaFlashBangPattern : public CATBPattern
{
	SMART_DELETER_REGISTER

private:
	explicit CBronyaFlashBangPattern();
	virtual ~CBronyaFlashBangPattern();

public:
	virtual void Pattern(Engine::CObject* pOwner) override;
	virtual _float GetCost() { return m_cost; }
	static SP(CBronyaFlashBangPattern) Create();

private:
	void GetRHandMat(Engine::CObject * pOwner, _mat * pAtkBall);

private:
	_float m_cost = 1.f;

	_float m_atkTime = 0.f; // ���� ��Ÿ��
	_float m_atkDis = 25.f; // ���� �Ÿ�
	_float m_atkCool = 3.f; // ���� ��Ÿ��

	_float m_walkTime = 0.f; // �̵� ��Ÿ��
	_float m_walkCool = 1.f; // �̵� �ƽ� ��Ÿ��

	_bool m_atkReady = true; // true : ���� ����, false : ���� �Ұ�
	_bool m_walkReady = true; // ture : �̵� ����, false : �̵� �Ұ�
	_bool m_onAtk = false;

	_mat m_atkMat;
	_mat* m_pRHand;
	std::wstring m_curState;

	_bool m_onThrow = false;
	_bool m_onFlashEffect = false;

	SP(CBronyaEscapePattern) m_spEscapeP = CBronyaEscapePattern::Create();
};

#endif