#ifndef HITSUICOMPONENT_H
#define HITSUICOMPONENT_H

#include "Component.h"
class CHitsUiC  final : public Engine::CComponent
{
public:
	explicit CHitsUiC();
	~CHitsUiC();

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

	void AddHitsCount(_int value);
	
public:
	static const	EComponentID	m_s_componentID = EComponentID::Text;
private:
	_int m_hitsCount;
	GETTOR(_int, m_maxHitsCount, 0, MaxHitsCount);
};
#endif