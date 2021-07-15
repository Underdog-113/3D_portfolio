#ifndef BRONYASKILLULTRAPATTERN_H
#define BRONYASKILLULTRAPATTERN_H

#include "ATBPattern.h"

#include "BronyaStealthBackPattern.h"

class CFSM_BronyaC;

class CBronyaSkillUltraPattern : public CATBPattern
{
	SMART_DELETER_REGISTER

private:
	explicit CBronyaSkillUltraPattern();
	virtual ~CBronyaSkillUltraPattern();

public:
	virtual void Pattern(Engine::CObject* pOwner) override;
	virtual _float GetCost() { return m_cost; }
	static SP(CBronyaSkillUltraPattern) Create();

private:
	void MoveCenter(Engine::CObject* pOwner, SP(CFSM_BronyaC) spFSM, _float3 mPos);
	void EscapeBack(Engine::CObject* pOwner, SP(CFSM_BronyaC) spFSM);

private:
	//_float m_cost = 25.f;
	_float m_cost = 5.f;

	_float m_atkTime = 0.f; // ���� ��Ÿ��
	_float m_atkDis = 1.5f; // ���� �Ÿ�
	_float m_atkCool = 3.f; // ���� ��Ÿ��

	_float m_walkTime = 0.f; // �̵� ��Ÿ��
	_float m_walkCool = 1.f; // �̵� �ƽ� ��Ÿ��

	_bool m_atkReady = true; // true : ���� ����, false : ���� �Ұ�
	_bool m_walkReady = true; // ture : �̵� ����, false : �̵� �Ұ�
	_bool m_onAtk = false;
	_bool m_onEscape = false;
	_bool m_movedCenter = false;
	_bool m_onShock = false;

	// ������� ������ �� �� �ݺ����� ����
	// �ּ� 2��, �ִ� 4���� �ݺ�
	_int m_curCnt = 0;
	_int m_minCnt = 2;
	_int m_maxCnt = 4;

	// ���� �����ϰ� �ִ� shock ����
	_int m_curPattern = 0;

	_mat m_atkMat;
	std::wstring m_curState;

private:
	_float3 m_lerpStartPos = ZERO_VECTOR;
	_float3 m_lerpEndPos = ZERO_VECTOR;
	_float m_lerpMaxTimer = 0.7f;
	_float m_lerpCurTimer = 0.f;

	SP(CBronyaShock1Pattern) m_spShock1P = CBronyaShock1Pattern::Create();
	SP(CBronyaShock2Pattern) m_spShock2P = CBronyaShock2Pattern::Create();
	SP(CBronyaStealthBackPattern) m_spStealthBackP = CBronyaStealthBackPattern::Create();
};

#endif