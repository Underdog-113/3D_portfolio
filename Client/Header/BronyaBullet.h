#pragma once
#ifndef BRONYABULLET_H
#define BRONYABULLET_H

#include "Object.h"

class CBronya_Ult_Impact;
class CBronya_Ult_Impact_Smoke;
class CMB_Bronya;

class CBronyaBullet : public Engine::CObject
{
	SMART_DELETER_REGISTER

public:
	CBronyaBullet();
	~CBronyaBullet();
	
public:
	static			SP(CBronyaBullet)		Create(_bool isStatic, Engine::CScene* pScene);

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
					void					SetBasicName		(void) override;

public:
	void ActiveAttackBall(_float damageRate, HitInfo::Strength strength, HitInfo::CrowdControl cc, _mat* pBoneMat, _float radius);
	void UnActiveAttackBall();

protected:
	static			_uint							m_s_uniqueID;
	GETTOR			(SP(Engine::CMeshC),			m_spMesh,			nullptr,	Mesh)
	GETTOR			(SP(Engine::CTextureC),			m_spTexture,		nullptr,	Texture)
	GETTOR			(SP(Engine::CGraphicsC),		m_spGraphics,		nullptr,	Graphics)
	GETTOR			(SP(Engine::CShaderC),			m_spShader,			nullptr,	Shader)
	GETTOR			(CAttackBall*,					m_pAttackBall,		nullptr,	AttackBall)
	GETTOR			(_float,						m_speed,			22.f,		Speed)
	GETTOR			(_float,						m_accTime,			0.f,		AccTime)
	GETTOR			(_float,						m_maxTime,			4.f,		MaxTime)
		
	GETTOR_SETTOR	(_mat*,							m_pParentMatrix,	nullptr,	ParentMatrix)
	GETTOR_SETTOR	(_float3,						m_dir,				{},			Dir)
	GETTOR_SETTOR	(_bool,							m_move,				true,		Move)

	_mat m_bulletMat;

	_float m_accShotTime = 0.f;

	_bool m_onAttackBall = false;

	_float m_x = 0.f;
	_float m_y = 0.f;

	CMB_Bronya* m_pBronya = nullptr;

	SP(CBronya_Ult_Impact) m_spImactEffect = nullptr;
	SP(CBronya_Ult_Impact_Smoke) m_spImpactSmokeEffect = nullptr;
	SP(CBronya_Ult_Laser) m_spLaserEffect = nullptr;

	GETTOR(M_Stat*, m_pStat, nullptr, Stat)
	GETTOR_SETTOR(_int, index, 0, Index)
};

#endif
