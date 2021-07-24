#ifndef SPITEMCOMPONENT_H
#define SPITEMCOMPONENT_H

#include "Component.h"
class CValkyrie;
class CSpItemC  final : public Engine::CComponent
{
public:
	explicit CSpItemC();
	~CSpItemC();

	SP(Engine::CComponent) MakeClone(Engine::CObject *pObject) override;
	void Awake() override;
	void Start(SP(Engine::CComponent) spThis) override;
	void FixedUpdate(SP(Engine::CComponent) spThis) override;
	void Update(SP(Engine::CComponent) spThis) override;
	void LateUpdate(SP(Engine::CComponent) spThis) override;
	void OnDestroy() override;
	void OnEnable() override;
	void OnDisable() override;

	void AddDataInit(_int spValue, _float force);

private:
	void UpDown();
public:
	static const	EComponentID	m_s_componentID = EComponentID::TargetPosition;

private:
	CValkyrie* m_currentValkyrie;

	_int m_spValue;
	_float m_force;

	_bool m_init;
	_float m_oldY;

	_bool m_enable;
	_float m_dir;
};
#endif
