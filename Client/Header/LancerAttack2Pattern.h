#ifndef LANCERATTACK2PATTERN_H
#define LANCERATTACK2PATTERN_H

#include "ATBPattern.h"

class CLancerAttack2Pattern : public CATBPattern
{
	SMART_DELETER_REGISTER

private:
	explicit CLancerAttack2Pattern();
	virtual ~CLancerAttack2Pattern();

public:
	virtual void Pattern(Engine::CObject* pOwner) override;
	virtual _float GetCost() { return m_cost; }
	static SP(CLancerAttack2Pattern) Create();

private:
	_mat GetRHandMat(Engine::CObject* pOwner);

private:
	_float m_cost = /*35*/1.f;

	_float m_atkTime = 0.f; // ���� ��Ÿ��
	_float m_atkDis = 2.3f; // ���� �Ÿ�
	_float m_atkCool = 6.f; // ���� ��Ÿ��

	_float m_walkTime = 0.f; // �̵� ��Ÿ��
	_float m_walkCool = 0.3f; // ���� ������ �̵� �ð�

	_bool m_atkReady = true; // true : ���� ����, false : ���� �Ұ�
	_bool m_walkReady = true; // ture : �̵� ����, false : �̵� �Ұ�

	_mat m_atkMat;

	/* for.lerp */
	_bool m_onLerp = false;

	/* for.effect */
	SP(Engine::CObject) m_spSignEffect = nullptr;
	SP(Engine::CObject) m_spBladeEffect = nullptr;

	_mat* m_pRHand;

	_bool m_onSignEffect = false;
	_bool m_onBladeEffect = false;

	_bool m_onShoot2 = false;
	_bool m_onWalk = false;

	_float3 m_beamDir = {};
	_TCHAR* m_curMoveSound;
};

#endif