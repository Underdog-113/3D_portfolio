#ifndef SIZEUPCOMPONENT_H
#define SIZEUPCOMPONENT_H

#include "Component.h"
#include "Slider.h"
class CSizeUpC  final : public Engine::CComponent
{
public:
	explicit CSizeUpC();
	~CSizeUpC();

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
	GETTOR_SETTOR(_float, m_size, 0, Size);
	GETTOR_SETTOR(_float, m_speed, 0, Speed);

};
#endif
