#ifndef TARGETPOSITIONCOMPONENT_H
#define TARGETPOSITIONCOMPONENT_H

#include "Component.h"
#include "Slider.h"
class CTargetPositionC  final : public Engine::CComponent
{
public:
	explicit CTargetPositionC();
	~CTargetPositionC();

	// CComponent��(��) ���� ���ӵ�
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
	GETTOR_SETTOR(Engine::CObject*, m_target, nullptr, Target)

};
#endif
