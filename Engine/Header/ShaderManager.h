#ifndef SHADERSTORE_H
#define SHADERSTORE_H

#include "ResourceStore.h"
#include "Shader.h"

BEGIN(Engine)
class ENGINE_DLL CShaderManager final
{
	DECLARE_SINGLETON(CShaderManager)
public:
			void				Awake				(void);
			void				OnDestroy			(void);

public:
			CShader*			GetShader			(_int shaderID);
			_int				GetShaderID			(std::wstring shaderName);

			void				InitShaderList		(_uint numOfShader);
			void				AddKeyAndShader		(CShader* pShader, std::wstring shaderKey, _uint ID);
private:
	typedef std::vector<CShader*> _SHADERS;
	typedef std::vector<std::wstring> _HASHMAP;
			_SHADERS	m_vShaders;
			_HASHMAP	m_vHashKey;

};
END
#endif // !MESHSTORE_H
