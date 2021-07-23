#ifndef GACHBOXCOMPONENT_H
#define GACHBOXCOMPONENT_H

#include "Component.h"
class CGachBoxC  final : public Engine::CComponent
{
public:
	explicit CGachBoxC();
	~CGachBoxC();

	SP(Engine::CComponent) MakeClone(Engine::CObject *pObject) override;
	void Awake() override;
	void Start(SP(Engine::CComponent) spThis) override;
	void FixedUpdate(SP(Engine::CComponent) spThis) override;
	void Update(SP(Engine::CComponent) spThis) override;
	void LateUpdate(SP(Engine::CComponent) spThis) override;
	void OnDestroy() override;
	void OnEnable() override;
	void OnDisable() override;

private:
public:
	static const	EComponentID	m_s_componentID = EComponentID::TargetPosition;
private:
	GETTOR_SETTOR(_bool*, m_production, nullptr, Production);
};
#endif
