#ifndef PHYSICSCOMPONENT_H
#define PHYSICSCOMPONENT_H

BEGIN(Engine)
class ENGINE_DLL CPhysicsC final : public CComponent
{
public:
	explicit							CPhysicsC			(void);
									   ~CPhysicsC			(void);
public:
					SP(CComponent)		MakeClone			(CObject* pObject)	override;

					void				Awake				(void) override;
					void				Start				(SP(CComponent) spThis) override;

					void				FixedUpdate			(SP(CComponent) spThis) override;
					void				Update				(SP(CComponent) spThis) override;
					void				LateUpdate			(SP(CComponent) spThis) override;

					void				OnDestroy			(void) override;

					void				OnDisable			(void) override;
					void				OnEnable			(void) override;

public:
	static const	EComponentID	m_s_componentID = EComponentID::Physics;

private:
	GETTOR			(SP(CTransformC),	m_spTransform,		nullptr,		Transform)
	GETTOR			(SP(CRigidBodyC),	m_spRigidBody,		nullptr,		RigidBody)
	GETTOR			(SP(CCollisionC),	m_spCollision,		nullptr,		Collision)

	GETTOR			(PxActor*,			m_pActor,			nullptr,		Actor)
};
END
#endif // !GRAPHICSCOMPONENT_H
