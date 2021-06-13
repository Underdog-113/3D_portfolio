#ifndef DECOOBJECT_H
#define DECOOBJECT_H

#include "Object.h"

BEGIN(Engine)
class ENGINE_DLL CDecoObject final : public CObject
{
	SMART_DELETER_REGISTER
private:
	explicit						CDecoObject			(void);
								   ~CDecoObject			(void);

public:
	static		SP(CDecoObject)		Create				(_bool isStatic, CScene* pScene);

				SP(CObject)			MakeClone			(void) override;
		
				void				Awake				(void) override;
				void				Start				(void) override;
		
				void				FixedUpdate			(void) override;
				void				Update				(void) override;
				void				LateUpdate			(void) override;
		
				void				OnDestroy			(void) override;
		
				void				OnEnable			(void) override;
				void				OnDisable			(void) override;

private:
				void				SetBasicName		(void) override;
private:
	static		_uint				m_s_uniqueID;

	GETTOR		(SP(CMeshC),		m_spMesh,			nullptr,	Mesh)
	GETTOR		(SP(CTextureC),		m_spTexture,		nullptr,	Texture)
	GETTOR		(SP(CGraphicsC),	m_spGraphics,		nullptr,	Graphics)
};
END
#endif