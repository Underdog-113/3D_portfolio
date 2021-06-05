#ifndef SHADERCOMPONENT_H
#define SHADERCOMPONENT_H

BEGIN(Engine)
class ENGINE_DLL CShaderC final : public CComponent
{
public:
	explicit								CShaderC			(void);
										   ~CShaderC			(void);

public:
					SP(CComponent)			MakeClone			(CObject* pObject) override;
					void					Awake				(void) override;
					void					Start				(SP(CComponent) spThis) override;

					void					FixedUpdate			(SP(CComponent) spThis) override;
					void					Update				(SP(CComponent) spThis) override;
					void					LateUpdate			(SP(CComponent) spThis) override;

					void					OnDestroy			(void) override;

					void					OnEnable			(void) override;
					void					OnDisable			(void) override;

public:
					_int					GetShaderID			(std::wstring shaderName);
public:
	static const	EComponentID			m_s_componentID = EComponentID::Shader;

protected:
	GETTOR_SETTOR	(LPD3DXEFFECT,			m_pEffects,			nullptr,		Effect)
};
END

#endif
