#ifndef OUTLINESHADER_H
#define OUTLINESHADER_H

#include "Shader.h"

class COutlineShader final : public Engine::CShader
{
private:
	explicit							COutlineShader			(void);
									   ~COutlineShader			(void);

public:
	static			Engine::CShader*	Create					(void);
					void				Free					(void);

					void				Awake					(void) override;

public:
					void				SetUpConstantTable		(SP(Engine::CGraphicsC) spGC) override;
};

#endif