#ifndef LANCERBASEPATTERN_H
#define LANCERBASEPATTERN_H

#include "ATBPattern.h"

class CLancerBasePattern : public CATBPattern
{
	SMART_DELETER_REGISTER

private:
	explicit CLancerBasePattern();
	virtual ~CLancerBasePattern();

public:
	virtual void Pattern(Engine::CObject* pOwner) override;
	static SP(CLancerBasePattern) Create();

private:
	_mat GetRHandMat(Engine::CObject* pOwner);

private:
	_float m_atkTime = 0.f; // ���� ��Ÿ��
	_float m_atkDis = 3.f; // ���� �Ÿ�
	_float m_atkCool = 6.f; // ���� ��Ÿ��

	_float m_walkTime = 0.f; // �̵� ��Ÿ��
	_float m_walkCool = 0.8f; // ���� ������ �̵� �ð�

	_bool m_atkReady = true; // true : ���� ����, false : ���� �Ұ�
	_bool m_walkReady = true; // ture : �̵� ����, false : �̵� �Ұ�

	_mat m_atkMat;

	/* for.lerp */
	_bool m_onLerp = false;

	/* for.effect */
	SP(Engine::CObject) m_spSignEffect = nullptr;
	SP(Engine::CObject) m_spBladeEffect = nullptr;

	_bool m_onSignEffect = false;
	_bool m_onBladeEffect = false;
	_mat* m_pRHand;
};

#endif