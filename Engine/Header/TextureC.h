#ifndef TEXTURECOMPONENT_H
#define TEXTURECOMPONENT_H

BEGIN(Engine)
class ENGINE_DLL CTextureC final : public CComponent
{
public:
	explicit					CTextureC	(void);
	virtual					   ~CTextureC	(void);

public:
				SP(CComponent)	MakeClone			(CObject* pObject) override;

				void			Awake				(void) override;
				void			Start				(SP(CComponent) spSelf) override;

				void			FixedUpdate			(SP(CComponent) spSelf) override;
				void			Update				(SP(CComponent) spThis) override;
				void			LateUpdate			(SP(CComponent) spThis) override;

				void			OnDestroy			(void) override;

				void			OnEnable			(void) override;
				void			OnDisable			(void) override;

				void			SetAlpha			(_float alpha);
				void			AddAlpha			(_float alpha);
public:
				void			ResizeTexSet		(_int numOfTexSet);
				void			AddTexture			(std::wstring const& textureKey, _int setIndex = 0);
				void			ChangeTexture		(std::wstring const& textureKey, _int setIndex = 0, _int texIndex = 0);
				void			DeleteTexture		(_int setIndex, _int texIndex);

public:
	static const	EComponentID	m_s_componentID = EComponentID::Texture;
private:
	typedef std::vector<std::vector<_TexData*>> _TEXDATAS;
	GETTOR_SETTOR	(_TEXDATAS,		m_vTexData,			{},						TexData)
	GETTOR_SETTOR	(_TEXDATAS,		m_vNormalData,		{},						NormalData)
	GETTOR_SETTOR	(_TEXDATAS,		m_vLightData,		{},						LightData)
	GETTOR_SETTOR	(_float4,		m_color,			_float4(1, 1, 1, 1),	Color)
	GETTOR_SETTOR	(_int,			m_numOfTex,			0,						NumOfTex)	
	
	//GETTOR_SETTOR	(_bool,			m_changeTex,		false,					ChangeTex)
	//GETTOR_SETTOR	(_float,		m_changeTimer,		0.f,					ChangeTimer)
	//GETTOR_SETTOR	(_float,		m_changeDuration,	0.032f,					ChangeDuration)

	GETTOR_SETTOR	(_int,			m_setIndex,			0,						SetIndex)
	GETTOR_SETTOR	(_int,			m_texIndex,			0,						TexIndex)
};
END

#endif // !TEXTURECOMPONENT_H
