#ifndef SHADERCOMPONENT_H
#define SHADERCOMPONENT_H

BEGIN(Engine)
class CShader;
class ENGINE_DLL CShaderC final : public CComponent
{
public:
	explicit							CShaderC				(void);
									   ~CShaderC				(void);

public:
					SP(CComponent)		MakeClone				(CObject* pObject) override;
					void				Awake					(void) override;
					void				Start					(SP(CComponent) spThis) override;

					void				FixedUpdate				(SP(CComponent) spThis) override;
					void				Update					(SP(CComponent) spThis) override;
					void				LateUpdate				(SP(CComponent) spThis) override;

					void				OnDestroy				(void) override;

					void				OnEnable				(void) override;
					void				OnDisable				(void) override;

public:
					CShader*			AddShader				(_int shaderID);
					void				ResizeShaderPerSubset	(_int size);
public:
	static const	EComponentID		m_s_componentID = EComponentID::Shader;

protected:
	typedef std::vector<CShader*> _SHADERS;
	typedef std::vector<_SHADERS> _SHADERS_2D;
	GETTOR			(_SHADERS,			m_vShaders,			{},		Shaders)
	GETTOR			(_SHADERS_2D,		m_vShaderPerSubset,	{},		ShaderPerSubset)
};
END

#endif
