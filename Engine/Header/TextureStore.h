#ifndef TEXTURESTORE_H
#define TEXTURESTORE_H

#include "ResourceStore.h"
//#include "Texture.h"

BEGIN(Engine)
class ENGINE_DLL CTextureStore final : public CResourceStore
{
private:
	explicit					CTextureStore			(void);
	virtual					   ~CTextureStore			(void);
public:
	static	CTextureStore*		Create					(void);
			void				Free					(void);

			void				Awake					(void) override;
			void				OnDestroy				(void) override;

			void				ClearCurResource		(void) override;

			_TexData*			GetTextureData			(std::wstring textureKey);
			void				InitTextureForScene		(std::wstring curScene, _bool isStatic = false);

private:
			void				ParsingTexture			(std::wstring filePath, 
														 std::wstring fileName);

private:
	typedef std::unordered_map<std::wstring, _TexData*>	_TexDataMap;
			_TexDataMap			m_mCurSceneTextureData;
	static	_TexDataMap			m_s_mStaticTextureData;
	
	static	_uint				m_s_usage;
};
END

#endif