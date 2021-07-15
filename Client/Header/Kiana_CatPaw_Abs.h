#pragma once
#include "Object.h"
class CKiana_CatPaw_Abs : public Engine::CObject
{
public:
	CKiana_CatPaw_Abs();
	virtual ~CKiana_CatPaw_Abs();
public:
	virtual void					Awake(void) ;
	virtual void					Start(void) ;
	 
	virtual void					FixedUpdate(void) ;
	virtual void					Update(void) ;
	virtual void					LateUpdate(void) ;
	 
	virtual void					PreRender(LPD3DXEFFECT pEffect) ;
	virtual void					Render(LPD3DXEFFECT pEffect) ;
	virtual void					PostRender(LPD3DXEFFECT pEffect) ;
	 
	virtual void					OnDestroy(void) ;
	 
	virtual void					OnEnable(void) ;
	virtual void					OnDisable(void) ;

	virtual void					OnTriggerEnter(Engine::CCollisionC const* pCollisionC);
	virtual void					OnTriggerStay(Engine::CCollisionC const* pCollisionC);
	virtual void					OnTriggerExit(Engine::CCollisionC const* pCollisionC);

	void					SetBasicName();
	void					FindMidBone(void);
	void					SetupPaw(CObject* pOwner, HitInfo info);

protected:
	static			_uint							m_s_uniqueID;
	GETTOR			(SP(Engine::CMeshC),			m_spMesh,			nullptr,	Mesh)
	GETTOR			(SP(Engine::CTextureC),			m_spTexture,		nullptr,	Texture)
	GETTOR			(SP(Engine::CGraphicsC),		m_spGraphics,		nullptr,	Graphics)
	GETTOR			(SP(Engine::CShaderC),			m_spShader,			nullptr,	Shader)
	GETTOR			(SP(Engine::CCollisionC),		m_spCollision,		nullptr,		Collision)
	GETTOR			(_int,							m_collisionID,		UNDEFINED,		CollisionID)

	Engine::CSphereCollider* m_pCollider;

private:	
	typedef std::vector<Engine::CObject*> _OBJECTS;
	GETTOR			(_OBJECTS,					m_vCollided,		{},				Collided)
	GETTOR_SETTOR	(Engine::CObject*,			m_pOwner,			nullptr,		Owner)
	GETTOR_SETTOR	(HitInfo,					m_hitInfo,			HitInfo(),		HitInfoMation)
	
	Engine::D3DXFRAME_DERIVED*	m_pMidBone_Frame = nullptr;

	_bool m_isAnimEnd = false;
	_float m_fDissolveAlpha = 1.f;

protected:
	GETTOR_SETTOR	(_float3,					m_pawOffset,		ZERO_VECTOR,	PawOffset)
	_float3 m_forwardOffset = ZERO_VECTOR;

};

