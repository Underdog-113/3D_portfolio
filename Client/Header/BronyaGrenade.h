#pragma once
#ifndef BRONYAGRENADE_H
#define BRONYAGRENADE_H

#include "Object.h"

class CMB_Bronya;

class CBronyaGrenade : public Engine::CObject
{
	SMART_DELETER_REGISTER

public:
	CBronyaGrenade();
	~CBronyaGrenade();
	
public:
	static			SP(CBronyaGrenade)		Create(_bool isStatic, Engine::CScene* pScene);

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
					
public:
					void					OnCollisionEnter	(Engine::_CollisionInfo ci);
					void					OnCollisionStay		(Engine::_CollisionInfo ci);
					void					OnCollisionExit		(Engine::_CollisionInfo ci);                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                         
					void					SetBasicName		(void) override;

public:
	void ActiveAttackBall(_float damageRate, HitInfo::Strength strength, HitInfo::CrowdControl cc, _mat* pBoneMat, _float radius);
	void UnActiveAttackBall();

private:
	void TurnOffRigidbodyCollisionSetting();

protected:
	static			_uint							m_s_uniqueID;
	GETTOR			(SP(Engine::CMeshC),			m_spMesh,			nullptr,	Mesh)
	GETTOR			(SP(Engine::CTextureC),			m_spTexture,		nullptr,	Texture)
	GETTOR			(SP(Engine::CGraphicsC),		m_spGraphics,		nullptr,	Graphics)
	GETTOR			(SP(Engine::CShaderC),			m_spShader,			nullptr,	Shader)
	GETTOR			(SP(Engine::CRigidBodyC),		m_spRigidBody,		nullptr,	RigidBody)
	GETTOR			(SP(Engine::CCollisionC),		m_spCollision,		nullptr,	Collision)
	GETTOR			(SP(Engine::CDebugC),			m_spDebug,			nullptr,	Debug)
	GETTOR			(CAttackBall*,					m_pAttackBall,		nullptr,	AttackBall)
	GETTOR			(_float,						m_speed,			22.f,		Speed)
	GETTOR			(_float,						m_accTime,			0.f,		AccTime)
	GETTOR			(_float,						m_maxTime,			4.f,		MaxTime)
		
	GETTOR_SETTOR	(_mat*,							m_pParentMatrix,	nullptr,	ParentMatrix)
	GETTOR_SETTOR	(_float3,						m_dir,				{},			Dir)
	GETTOR_SETTOR	(_bool,							m_move,				true,		Move)

	_mat m_grenadeMat;

	_bool m_onAttackBall = false;
	_bool m_onBoomReady = true;

	_float m_x = 0.f;
	_float m_y = 0.f;
	_int m_bounceCount = 2; //최대 몇번 튕길건지를 변수로 저장

	CMB_Bronya* m_pBronya = nullptr;

	GETTOR(M_Stat*, m_pStat, nullptr, Stat)
	
	GETTOR_SETTOR(_int, index, 0, Index)
};

#endif
