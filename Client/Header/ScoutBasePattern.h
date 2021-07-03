#ifndef SCOUTBASEPATTERN_H
#define SCOUTBASEPATTERN_H

#include "ATBPattern.h"

class CScoutBasePattern : public CATBPattern
{
	SMART_DELETER_REGISTER

private:
	explicit CScoutBasePattern();
	virtual ~CScoutBasePattern();

public:
	virtual void Pattern(Engine::CObject* pOwner) override;
	static SP(CScoutBasePattern) Create();

private:
	void SetMoveSound();

private:
	_float m_atkTime = 0.f; // ���� ��Ÿ��
	_float m_atkDis = 6.f; // ���� �Ÿ�
	_float m_atkCool = 2.f; // ���� ��Ÿ��

	_float m_walkTime = 0.f; // �̵� ��Ÿ��
	_float m_walkCool = 3.f; // �ൿ ������ �̵� �ð�

	_bool m_atkReady = true; // true : ���� ����, false : ���� �Ұ�
	_bool m_walkReady = true; // ture : �̵� ����, false : �̵� �Ұ�

	_mat m_atkMat;

	_int m_maxMoveCnt = 1; // �̵� ������ �ٲٴ� �ƽ� ����
	_int m_moveCnt = 0; // �̹� base ���� ���� �� ���� �̵� ������ �ٲ� ����
	std::wstring m_curState;
	_TCHAR* m_curMoveSound;
};

#endif