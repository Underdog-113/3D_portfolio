#ifndef SHADERSTORE_H
#define SHADERSTORE_H

#include "ResourceStore.h"

BEGIN(Engine)
class ENGINE_DLL CShaderStore final : public CResourceStore
{
	DECLARE_SINGLETON(CShaderStore)
public:
			void				Awake				(void) override;
			void				Start				(void);
			void				OnDestroy			(void) override;

			void				ClearCurResource	(void) override;

			LPD3DXEFFECT		GetShader			(_int shaderID);
			void				InitShaders			(void);
private:
			void				ParsingShdaer		(std::wstring filePath, 
													 std::wstring fileName);


private:
	typedef std::vector<LPD3DXEFFECT> _ShaderMap;
			_ShaderMap	m_vShaderMap;
};
END
#endif // !MESHSTORE_H
