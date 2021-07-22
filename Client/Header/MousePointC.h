#ifndef MOUSEPOINTCOMPONENT_H
#define MOUSEPOINTCOMPONENT_H

#include "Component.h"
class CValkyrie;
class CMousePointC  final : public Engine::CComponent
{
public:
	explicit CMousePointC();
	~CMousePointC();

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
};
#endif
