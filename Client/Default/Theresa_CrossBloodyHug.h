#pragma once
#ifndef CROSSBLOODHUG_H
#define CROSSBLOODHUG_H

#include "Object.h"

class CTheresa;
class CAttackBall;
class CTheresa_CrossBlade;
class CTheresa_CrossBloodyHug final : public Engine::CObject
{
	SMART_DELETER_REGISTER
		
	enum SkillState{ Ready, Fall, Stretch, Roll, End };

public:
	CTheresa_CrossBloodyHug();
	~CTheresa_CrossBloodyHug();
public:
	static			SP(CTheresa_CrossBloodyHug)		Create(_bool isStatic, Engine::CScene* pScene);

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

private:
					void					FallReady();
					void					FallDown();
					void					StretchBlade();
					void					RollBlade();
					void					EndSkill();

protected:
	static			_uint							m_s_uniqueID;
	GETTOR			(SP(Engine::CMeshC),			m_spMesh,			nullptr,	Mesh)
	GETTOR			(SP(Engine::CTextureC),			m_spTexture,		nullptr,	Texture)
	GETTOR			(SP(Engine::CGraphicsC),		m_spGraphics,		nullptr,	Graphics)
	GETTOR			(SP(Engine::CShaderC),			m_spShader,			nullptr,	Shader)
				
private:	
	GETTOR_SETTOR	(CTheresa*,						m_pTheresa,			nullptr,	Theresa)
	GETTOR			(SP(Engine::CObject),			m_spCrossBlade,		nullptr,	CrossBlade)
	GETTOR_SETTOR	(_float,						m_fallStartY,		0.f,		FallStartY)
	GETTOR_SETTOR	(_float,						m_fallEndY,			0.f,		FallEndY)
		
	GETTOR			(CAttackBall*,					m_pAttackBall,		nullptr,	AttackBall)

	SkillState m_skillState = Ready;

	_float m_stateTimer = 0.f;
	_float m_stateDuration = 0.2f;
	_float m_attackTimer = 0.f;

	_bool m_beginAnimEnd = false;

private:
	_float m_fDissolveAlpha = 1.f;
};



#endif // CROSSBLOODHUG_H
