#ifndef TIMERCOMPONENT_H
#define TIMERCOMPONENT_H

#include "Component.h"
#include "Slider.h"
class CTimerC  final : public Engine::CComponent
{
public:
	explicit CTimerC();
	~CTimerC();

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
	GETTOR_SETTOR(_float, m_time, 0, Time);
	_float m_value;

};
#endif
