#ifndef DAMAGEFONTSHADER_H
#define DAMAGEFONTSHADER_H

#include "Shader.h"
class CDamageFontShader final : public Engine::CShader
{
private:
	explicit							CDamageFontShader(void);
	~CDamageFontShader(void);

public:
	static				Engine::CShader*			Create(void);
	void				Free(void);

	void				Awake(void) override;

public:
	void				SetUpConstantTable(SP(Engine::CGraphicsC) spGC) override;

private:
};


#endif