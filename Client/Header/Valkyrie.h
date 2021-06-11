#pragma once
#include "Object.h"

class CValkyrie abstract : public Engine::CObject
{
	SMART_DELETER_REGISTER;

protected:
	CValkyrie();
	virtual ~CValkyrie() = default;

public:
	virtual		SP(Engine::CObject)			MakeClone(void) PURE;

	virtual		void						Awake(void) PURE;
	virtual		void						Start(void) PURE;

	virtual		void						FixedUpdate(void) PURE;
	virtual		void						Update(void) PURE;
	virtual		void						LateUpdate(void) PURE;

	virtual		void						PreRender(void) PURE;
	virtual		void						PreRender(LPD3DXEFFECT pEffect) PURE;

	virtual		void						Render(void) PURE;
	virtual		void						Render(LPD3DXEFFECT pEffect) PURE;

	virtual		void						PostRender(void) PURE;
	virtual		void						PostRender(LPD3DXEFFECT pEffect) PURE;

	virtual		void						OnDestroy(void) PURE;

	virtual		void						OnEnable(void) PURE;
	virtual		void						OnDisable(void) PURE;

	virtual		void						SetBasicName(void)  PURE;

	virtual		void						OnCollisionEnter(Engine::_CollisionInfo ci) {};
	virtual		void						OnCollisionStay(Engine::_CollisionInfo ci) {};
	virtual		void						OnCollisionExit(Engine::_CollisionInfo ci) {};

protected:
	static			_uint						m_s_uniqueID;
	GETTOR			(SP(Engine::CMeshC),		m_spMesh,		nullptr, Mesh)
	GETTOR			(SP(Engine::CGraphicsC),	m_spGraphics,	nullptr, Graphics)
	GETTOR			(SP(Engine::CShaderC),		m_spShader,		nullptr, Shader)
	GETTOR			(SP(Engine::CTextureC),		m_spTexture,	nullptr, Texture)
		
};

