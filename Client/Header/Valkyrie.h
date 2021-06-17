#pragma once

#ifndef VALKYRIE_H
#define VALKYRIE_H
#include "Object.h"

class CStageControlTower;
class CValkyrie abstract : public Engine::CObject
{
	SMART_DELETER_REGISTER;

protected:
	CValkyrie();
	virtual ~CValkyrie() = default;

public:
	virtual		SP(Engine::CObject)			MakeClone			(void) PURE;

	virtual		void						Awake				(void);
	virtual		void						Start				(void);

	//virtual		void						FixedUpdate			(void);
	//virtual		void						Update				(void);
	//virtual		void						LateUpdate			(void);

	//virtual		void						PreRender			(void) {};
	//virtual		void						PreRender			(LPD3DXEFFECT pEffect);

	//virtual		void						Render				(void);
	//virtual		void						Render				(LPD3DXEFFECT pEffect);

	//virtual		void						PostRender			(void);
	//virtual		void						PostRender			(LPD3DXEFFECT pEffect);

	//virtual		void						OnDestroy			(void);

	//virtual		void						OnEnable			(void);
	//virtual		void						OnDisable			(void);

	//virtual		void						SetBasicName		(void);

	virtual		void						OnCollisionEnter(Engine::_CollisionInfo ci) {};
	virtual		void						OnCollisionStay(Engine::_CollisionInfo ci) {};
	virtual		void						OnCollisionExit(Engine::_CollisionInfo ci) {};

protected:
	static			_uint							m_s_uniqueID;
	GETTOR			(SP(Engine::CMeshC),			m_spMesh,			nullptr,	Mesh)
	GETTOR			(SP(Engine::CTextureC),			m_spTexture,		nullptr,	Texture)
	GETTOR			(SP(Engine::CGraphicsC),		m_spGraphics,		nullptr,	Graphics)
	GETTOR			(SP(Engine::CShaderC),			m_spShader,			nullptr,	Shader)

protected:	
	GETTOR			(SP(Engine::CStateMachineC),	m_spStateMachine,	nullptr,	StateMachine)
		
	GETTOR			(V_Stat*,					m_pStat,			nullptr,	Stat)
	
protected:
	CStageControlTower*			m_pCT = nullptr;
};

#endif
