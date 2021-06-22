#ifndef ATTACKBALL_H
#define ATTACKBALL_H

class CAttackBall final : public Engine::CObject
{
	SMART_DELETER_REGISTER
private:
	explicit									CAttackBall			(void);
											   ~CAttackBall			(void);

public:
	static			SP(CAttackBall)				Create				(_bool isStatic, Engine::CScene* pScene);

					SP(CObject)					MakeClone			(void) override;
		
					void						Awake				(void) override;
					void						Start				(void) override;
		
					void						FixedUpdate			(void) override;
					void						Update				(void) override;
					void						LateUpdate			(void) override;

					void						OnDestroy			(void) override;
		
					void						OnEnable			(void) override;
					void						OnDisable			(void) override;

					void						OnCollisionEnter	(Engine::_CollisionInfo ci);
					void						OnCollisionStay		(Engine::_CollisionInfo ci);
					void						OnCollisionExit		(Engine::_CollisionInfo ci);

					void						OnTriggerEnter		(Engine::CCollisionC const* pCollisionC);
					void						OnTriggerStay		(Engine::CCollisionC const* pCollisionC);
					void						OnTriggerExit		(Engine::CCollisionC const* pCollisionC);

public:
					void						SetupBall			(CObject* pOwner, _mat* pParentMat, _float radius, HitInfo info);
private:
					void						SetBasicName		(void) override;
private:
	static			_uint						m_s_uniqueID;

	typedef std::vector<Engine::CObject*> _OBJECTS;
	GETTOR			(_OBJECTS,					m_vCollided,		{},				Collided)

	GETTOR			(SP(Engine::CCollisionC),	m_spCollision,		nullptr,		Collision)
	GETTOR			(_int,						m_collisionID,		UNDEFINED,		CollisionID)
	GETTOR_SETTOR	(Engine::CObject*,			m_pOwner,			nullptr,		Owner)
	GETTOR_SETTOR	(HitInfo,					m_hitInfo,			HitInfo(),		HitInfoMation)
	GETTOR_SETTOR	(_mat*,						m_pParentMatrix,	nullptr,		ParentMatrix)

	
};

#endif