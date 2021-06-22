#ifndef PATTERNMACHINE_H
#define PATTERNMACHINE_H

#include "Component.h"

class CATBPattern;

class CPatternMachineC : public Engine::CComponent
{
	enum Pattern_Type { Born, Die, Base, Hit };

public:
	explicit CPatternMachineC();
	~CPatternMachineC();

	// CComponent��(��) ���� ��ӵ�
	SP(Engine::CComponent) MakeClone(Engine::CObject *pObject) override;
	void Awake() override;
	void Start(SP(Engine::CComponent) spThis) override;
	void FixedUpdate(SP(Engine::CComponent) spThis) override;
	void Update(SP(Engine::CComponent) spThis) override;
	void LateUpdate(SP(Engine::CComponent) spThis) override;
	void OnDestroy() override;
	void OnEnable() override;
	void OnDisable() override;

public:
	void AddNecessaryPatterns(SP(CATBPattern) pBorn, SP(CATBPattern) pDie, SP(CATBPattern) pBase, SP(CATBPattern) pHit);
	void AddPattern(SP(CATBPattern) pPattern);
	

private:
	void SortingPatterns(); // ó�� �Ǵ� ����� �� �ٽ� ���Ϳ� ���� ���� ������
	void PlayBasePattern();
	void PlayBornPattern();
	void PlayDiePattern();
	void PlayHitPattern();
	void PlaySelectPattern(); // ���� ����

public:
	static const EComponentID m_s_componentID = EComponentID::Pattern;

private:
	std::vector<SP(CATBPattern)> m_vPatterns;
	std::vector<_int> m_vIndices;

	GETTOR_SETTOR(_bool, m_onBorn, false, OnBorn);
	GETTOR_SETTOR(_bool, m_onBase, false, OnBase);
	//GETTOR_SETTOR(_bool, m_onDie, false, OnDie);
	GETTOR_SETTOR(_bool, m_onHit, false, OnHit);
	GETTOR_SETTOR(_bool, m_onSelect, false, OnSelect);
	GETTOR_SETTOR(_float, m_curCost, 0.f, CurCost);
	GETTOR_SETTOR(_float, m_maxCost, 30.f, MaxCost);
};

#endif