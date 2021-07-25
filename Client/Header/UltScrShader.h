#ifndef ULTSCRSHADER_H
#define ULTSCRSHADER_H

#include "Shader.h"

class CUltScrShader final : public Engine::CShader
{
private:
	explicit							CUltScrShader			(void);
									   ~CUltScrShader			(void);

public:
	static			Engine::CShader*	Create					(void);
					void				Free					(void);

					void				Awake					(void) override;

public:
					void				SetUpConstantTable		(SP(Engine::CGraphicsC) spGC) override;
};

#endif