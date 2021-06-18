#ifndef TRAPOBJECT_H
#define TRAPOBJECT_H

#include "Object.h"

class CTrapObject final : public Engine::CObject
{
	SMART_DELETER_REGISTER
private:
	explicit						CTrapObject			(void);
								   ~CTrapObject			(void);

public:
	static		SP(CTrapObject)		Create				(_bool isStatic, Engine::CScene* pScene);

				SP(Engine::CObject)	MakeClone			(void) override;
		
				void				Awake				(void) override;
				void				Start				(void) override;
		
				void				FixedUpdate			(void) override;
				void				Update				(void) override;
				void				LateUpdate			(void) override;
		
				void				PreRender			(void) override;
				void				PreRender			(LPD3DXEFFECT pEffect) override;

				void				Render				(void) override;
				void				Render				(LPD3DXEFFECT pEffect) override;

				void				PostRender			(void) override;
				void				PostRender			(LPD3DXEFFECT pEffect) override;

				void				OnDestroy			(void) override;
		
				void				OnEnable			(void) override;
				void				OnDisable			(void) override;

private:
				void				SetBasicName		(void) override;
private:
	static		_uint				m_s_uniqueID;

	GETTOR		(SP(Engine::CMeshC),		m_spMesh,			nullptr,	Mesh)
	GETTOR		(SP(Engine::CTextureC),		m_spTexture,		nullptr,	Texture)
	GETTOR		(SP(Engine::CGraphicsC),	m_spGraphics,		nullptr,	Graphics)

	GETTOR		(SP(Engine::CCollisionC),	m_spCollision,		nullptr,	Collision)
};
#endif