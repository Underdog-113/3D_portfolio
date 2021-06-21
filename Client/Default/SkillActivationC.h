#ifndef SKILLACTIVATIONCOMPONENT_H
#define SKILLACTIVATIONCOMPONENT_H

#include "Component.h"
#include "Slider.h"
class CSkillActivationC  final : public Engine::CComponent
{
public:
	explicit CSkillActivationC();
	~CSkillActivationC();

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
	GETTOR_SETTOR(_float, m_speed, 1 , Speed);
	_float m_dir;
	_float m_alpha;
};
#endif