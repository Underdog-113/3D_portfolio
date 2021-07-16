#ifndef QTECOMPONENT_H
#define QTECOMPONENT_H

#include "Component.h"
class CQteC  final : public Engine::CComponent
{
public:
	explicit CQteC();
	~CQteC();

	SP(Engine::CComponent) MakeClone(Engine::CObject *pObject) override;
	void Awake() override;
	void Start(SP(Engine::CComponent) spThis) override;
	void FixedUpdate(SP(Engine::CComponent) spThis) override;
	void Update(SP(Engine::CComponent) spThis) override;
	void LateUpdate(SP(Engine::CComponent) spThis) override;
	void OnDestroy() override;
	void OnEnable() override;
	void OnDisable() override;

	void AddData(_float minSize, _float maxSize, _float speed);
public:
	static const	EComponentID	m_s_componentID = EComponentID::TargetPosition;

private:
	_float m_minSize;
	_float m_maxSize;
	_float m_speed;

	_float m_value;
	_float3 m_oldScale;

};
#endif
