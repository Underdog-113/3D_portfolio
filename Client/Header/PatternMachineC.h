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

	// CComponent을(를) 통해 상속됨
	SP(Engine::CComponent) MakeClone(Engine::CObject *pObject) override;
	void Awake() override;
	void Start(SP(Engine::CComponent) spThis) override;
	void FixedUpdate(SP(Engine::CComponent) spThis) override;
	void Update(SP(Engine::CComponent) spThis) override;
	void LateUpdate(SP(Engine::CComponent) spThis) override;
	void OnDestroy() override;
	void OnEnable() override;
	void OnDisable() override;

	static const EComponentID m_s_componentID = EComponentID::Pattern;

public:
	void AddNecessaryPatterns(SP(CATBPattern) pBorn, SP(CATBPattern) pDie, SP(CATBPattern) pBase, SP(CATBPattern) pHit);
	void AddPattern(SP(CATBPattern) pPattern);

private:
	void SortingPatterns(); // 처음 또는 비었을 때 다시 벡터에 패턴 랜덤 재정렬
	void PlayBasePattern();
	void PlayBornPattern();
	void PlayHitPattern();
	void PlayDiePattern();
	void PlaySelectPattern(); // 패턴 선택

private:
	std::vector<SP(CATBPattern)> m_vPatterns;
	std::vector<_int> m_vIndices;

	GETTOR_SETTOR(_bool, m_onBorn, false, OnBorn);
	GETTOR_SETTOR(_bool, m_onBase, false, OnBase);
	GETTOR_SETTOR(_bool, m_onDie, false, OnDie);
	GETTOR_SETTOR(_bool, m_onHitL, false, OnHitL); // hit_l
	GETTOR_SETTOR(_bool, m_onHitH, false, OnHitH); // hit_h
	GETTOR_SETTOR(_bool, m_onHitFrontL, false, OnHitFrontL); // hit_front_l
	GETTOR_SETTOR(_bool, m_onHitFront, false, OnHitFront); // hit_front
	GETTOR_SETTOR(_bool, m_onHitBack, false, OnHitBack); // hit_back
	GETTOR_SETTOR(_bool, m_onSelect, false, OnSelect);
	GETTOR_SETTOR(_float, m_curCost, 0.f, CurCost);
	GETTOR_SETTOR(_float, m_maxCost, 30.f, MaxCost);
};

#endif
