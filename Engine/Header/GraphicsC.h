#ifndef GRAPHICSCOMPONENT_H
#define GRAPHICSCOMPONENT_H

BEGIN(Engine)
class ENGINE_DLL CGraphicsC final : public CComponent
{
public:
	explicit							CGraphicsC			(void);
									   ~CGraphicsC			(void);
public:
					SP(CComponent)		MakeClone			(CObject* pObject)	override;

					void				Awake				(void) override;
					void				Start				(SP(CComponent) spThis) override;

					void				FixedUpdate			(SP(CComponent) spThis) override;
					void				Update				(SP(CComponent) spThis) override;
					void				LateUpdate			(SP(CComponent) spThis) override;

					void				OnDestroy			(void) override;

					void				OnDisable			(void) override;
					void				OnEnable			(void) override;

public:
					void				AddMaterial			(D3DMATERIAL9 mtrl, _int index = UNDEFINED);
					void				ResizeMaterial		(_int size);
					D3DMATERIAL9&		GetMtrl				(void);

public:
	static const	EComponentID	m_s_componentID = EComponentID::Graphics;

	
private:
					void				GenerateBV			(void);

private:
	typedef std::vector<D3DMATERIAL9> _MATERIALS;
	GETTOR			(_MATERIALS,		m_vMaterials,		{},				Materials)

					D3DMATERIAL9		m_mtrl				= {};		

	GETTOR			(SP(CMeshC),		m_spMesh,			nullptr,		Mesh)
	GETTOR			(SP(CTextureC),		m_spTexture,		nullptr,		Texture)
	GETTOR			(SP(CTransformC),	m_spTransform,		nullptr,		Transform)
	GETTOR			(SP(CRectTexC),		m_spRectTex,		nullptr,		RectTex)
	GETTOR			(SP(CShaderC),		m_spShader,			nullptr,		Shader)

	GETTOR_SETTOR	(_bool,				m_colorReverse,		false,			ColorReverse)
	GETTOR_SETTOR	(_bool,				m_fullShade,		false,			FullShade)

	GETTOR_SETTOR	(_float4,			m_color,			DEFAULT_VEC4,	Color)
	GETTOR			(_float3,			m_offsetBV,			ZERO_VECTOR,	OffsetBV)
	GETTOR			(_float3,			m_sizeBV,			ONE_VECTOR,		SizeBV)
	GETTOR_SETTOR	(_float,			m_glowCoef,			1.f,			GlowCoef)
	GETTOR_SETTOR	(_int,				m_renderID,			UNDEFINED,		RenderID)
	

};
END
#endif // !GRAPHICSCOMPONENT_H
