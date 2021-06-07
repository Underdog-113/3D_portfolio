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


private:
	typedef std::vector<CShader*> _Shaders;
			_Shaders	m_vShaders;
};
END
#endif // !MESHSTORE_H
