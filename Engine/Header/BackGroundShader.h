#ifndef BackGroundShader_H
#define BackGroundShader_H

#include "Shader.h"

BEGIN(Engine)
class ENGINE_DLL CBackGroundShader final : public CShader
{
private:
	explicit							CBackGroundShader(void);
	~CBackGroundShader(void);

public:
	static			CShader*			Create(void);
	void				Free(void);

	void				Awake(void) override;

public:
	void				SetUpConstantTable(SP(CGraphicsC) spGC) override;
};
END

#endif