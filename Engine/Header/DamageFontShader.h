#ifndef DAMAGEFONTSHADER_H
#define DAMAGEFONTSHADER_H

#include "Shader.h"
BEGIN(Engine)
class ENGINE_DLL CDamageFontShader final : public CShader
{
private:
	explicit							CDamageFontShader(void);
	~CDamageFontShader(void);

public:
	static				CShader*			Create(void);
	void				Free(void);

	void				Awake(void) override;

public:
	void				SetUpConstantTable(SP(CGraphicsC) spGC) override;

private:
};
END

#endif