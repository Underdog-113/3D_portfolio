#ifndef IndicatorC_h
#define IndicatorC_h

#include "Component.h"
class CIndicatorC  final : public Engine::CComponent
{
public:
	explicit CIndicatorC();
	~CIndicatorC();

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
	GETTOR_SETTOR(SP(Engine::CObject), m_target, nullptr, Target);
};
#endif
