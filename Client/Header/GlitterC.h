#ifndef GLITTERCOMPONENT_H
#define GLITTERCOMPONENT_H

#include "Component.h"
#include "Slider.h"
class CGlitterC  final : public Engine::CComponent
{
public:
	explicit CGlitterC();
	~CGlitterC();

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

	void AddGlitterData(_float a1TimerMax, _float a0TimerMax);
public:
	static const	EComponentID	m_s_componentID = EComponentID::Text;
private:
	_float m_A1Timer;
	_float m_A1TimerMax;

	_float m_A0Timer;
	_float m_A0TimerMax;

};
#endif