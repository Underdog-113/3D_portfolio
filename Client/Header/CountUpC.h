#ifndef COUNTUPCOMPONENT_H
#define COUNTUPCOMPONENT_H

#include "Component.h"
class CCountUpC  final : public Engine::CComponent
{
public:
	explicit CCountUpC();
	~CCountUpC();

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
	static const	EComponentID	m_s_componentID = EComponentID::TargetPosition;

private:
	GETTOR_SETTOR(_int, m_count, 0, Count);
	_float m_value;

};
#endif
