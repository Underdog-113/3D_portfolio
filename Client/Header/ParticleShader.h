#pragma once
#include "Shader.h"

class CParticleShader final : public Engine::CShader
{
private:
     explicit CParticleShader();
     		~CParticleShader();

public:
	static			Engine::CShader*	Create(void);
	void				Free(void);

	void				Awake(void) override;

public:
	void				SetUpConstantTable(SP(Engine::CGraphicsC) spGC) override;
};

