#pragma once
#ifndef KIANA_CATPAW_ATK02_H
#define KIANA_CATPAW_ATK02_H

#include "Object.h"


class CKiana_CatPaw_Atk02 final : public Engine::CObject
{
	SMART_DELETER_REGISTER

private:
	CKiana_CatPaw_Atk02();
	~CKiana_CatPaw_Atk02();
	
public:
	static			SP(CKiana_CatPaw_Atk02)		Create(_bool isStatic, Engine::CScene* pScene);

public:
					SP(Engine::CObject)		MakeClone			(void) override;
		
					void					Awake				(void) override;
					void					Start				(void) override;
		
					void					FixedUpdate			(void) override;
					void					Update				(void) override;
					void					LateUpdate			(void) override;

					void					PreRender			(LPD3DXEFFECT pEffect) override;
					void					Render				(LPD3DXEFFECT pEffect) override;
					void					PostRender			(LPD3DXEFFECT pEffect) override;
		
					void					OnDestroy			(void) override;
		
					void					OnEnable			(void) override;
					void					OnDisable			(void) override;
					
					void					OnCollisionEnter	(Engine::_CollisionInfo ci);
					void					OnCollisionStay		(Engine::_CollisionInfo ci);
					void					OnCollisionExit		(Engine::_CollisionInfo ci);

					void					OnTriggerEnter		(Engine::CCollisionC const* pCollisionC);
					void					OnTriggerStay		(Engine::CCollisionC const* pCollisionC);
					void					OnTriggerExit		(Engine::CCollisionC const* pCollisionC);

public:
					void					SetBasicName		(void) override;

					void					FindMidBone			(void);
					
					void					SetupPaw(CObject* pOwner, HitInfo info);

protected:
	static			_uint							m_s_uniqueID;
	GETTOR			(SP(Engine::CMeshC),			m_spMesh,			nullptr,	Mesh)
	GETTOR			(SP(Engine::CTextureC),			m_spTexture,		nullptr,	Texture)
	GETTOR			(SP(Engine::CGraphicsC),		m_spGraphics,		nullptr,	Graphics)
	GETTOR			(SP(Engine::CShaderC),			m_spShader,			nullptr,	Shader)
				
private:
	_float m_tempTimer = 0.f;
	_float m_tempDuration = 1.5f;
	
	GETTOR			(_mat*,							m_pMidBone_World,	nullptr,	RightToeWorldMatrix)
	
	_mat*						m_pMidBone_BoneOffset = nullptr;
	Engine::D3DXFRAME_DERIVED*	m_pMidBone_Frame = nullptr;


private:
	
	typedef std::vector<Engine::CObject*> _OBJECTS;
	GETTOR			(_OBJECTS,					m_vCollided,		{},				Collided)

	GETTOR			(SP(Engine::CCollisionC),	m_spCollision,		nullptr,		Collision)
	GETTOR			(_int,						m_collisionID,		UNDEFINED,		CollisionID)
	GETTOR_SETTOR	(Engine::CObject*,			m_pKiana,			nullptr,		Kiana)
	GETTOR_SETTOR	(HitInfo,					m_hitInfo,			HitInfo(),		HitInfoMation)
	GETTOR_SETTOR	(_mat*,						m_pParentMatrix,	nullptr,		ParentMatrix)
	GETTOR_SETTOR	(_float3,					m_offset,			ZERO_VECTOR,	Offset)

	SP(Engine::CCollider) m_spCollider;
	_float m_fDissolveAlpha = 1.f;

};

#endif // KIANA_CATPAW_ATK02_H


