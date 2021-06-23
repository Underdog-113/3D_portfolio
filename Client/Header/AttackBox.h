#ifndef ATTACKBOX_H
#define ATTACKBOX_H

class CAttackBox final : public Engine::CObject
{
	SMART_DELETER_REGISTER
private:
	explicit									CAttackBox			(void);
											   ~CAttackBox			(void);

public:
	static			SP(CAttackBox)				Create				(_bool isStatic, Engine::CScene* pScene);

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
					void						SetupBox			(CObject * pOwner, _mat * pParentMat, _float3 size, _float3 offset, _float3 rotOffset, HitInfo info);
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
	GETTOR_SETTOR	(_float3,					m_offset,			ZERO_VECTOR,	Offset)

	
};

#endif