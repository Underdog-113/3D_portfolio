#ifndef LIFEOBJECTCOMPONENT_H
#define LIFEOBJECTCOMPONENT_H

#include "Component.h"
class CLifeObjectC  final : public Engine::CComponent
{
public:
	explicit CLifeObjectC();
	~CLifeObjectC();

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
	GETTOR_SETTOR(_float, m_lifeTime, 0, LifeTime);
};
#endif