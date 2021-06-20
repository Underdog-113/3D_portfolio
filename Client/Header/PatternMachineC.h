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

public:
	void AddNecessaryPatterns(SP(CATBPattern) pBorn, SP(CATBPattern) pDie, SP(CATBPattern) pBase, SP(CATBPattern) pHit);
	void AddPattern(SP(CATBPattern) pPattern);
	

private:
	void SortingPatterns(); // 처음 또는 비었을 때 다시 벡터에 패턴 랜덤 재정렬
	void PlayBasePattern();
	void PlayBornPattern();
	void PlayDiePattern();
	void PlayHitPattern();
	void PlaySelectPattern(); // 패턴 선택

public:
	static const EComponentID m_s_componentID = EComponentID::Pattern;

private:
	std::vector<SP(CATBPattern)> m_vPatterns;
	std::vector<_int> m_vIndices;

	_bool m_select = false;
	_bool m_hit = false;
	_bool m_die = false;

	GETTOR_SETTOR(_float, m_curCost, 0.f, CurCost);
	GETTOR_SETTOR(_float, m_maxCost, 30.f, MaxCost);
};

#endif
