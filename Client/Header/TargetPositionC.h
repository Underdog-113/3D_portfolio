#ifndef TARGETPOSITIONCOMPONENT_H
#define TARGETPOSITIONCOMPONENT_H

#include "Component.h"
#include "Slider.h"
class CTargetPositionC  final : public Engine::CComponent
{
public:
	explicit CTargetPositionC();
	~CTargetPositionC();

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
	static const	EComponentID	m_s_componentID = EComponentID::Text;
	_int a = 10;
private:
	GETTOR_SETTOR(Engine::CObject*, m_target, nullptr, Target)
	
};
#endif