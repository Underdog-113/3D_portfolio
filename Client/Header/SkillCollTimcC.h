#ifndef SKILLCOLLTIMECOMPONENT_H
#define SKILLCOLLTIMECOMPONENT_H

#include "Component.h"
#include "Slider.h"
class CSkillCollTimcC  final : public Engine::CComponent
{
public:
	explicit CSkillCollTimcC();
	~CSkillCollTimcC();

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
private:
	Engine::CSlider* m_spSlider;

};
#endif