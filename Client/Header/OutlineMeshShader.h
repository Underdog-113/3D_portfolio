#ifndef OUTLINEMESHSHADER_H
#define OUTLINEMESHSHADER_H

#include "Shader.h"

class COutlineMeshShader final : public Engine::CShader
{
private:
	explicit							COutlineMeshShader		(void);
									   ~COutlineMeshShader		(void);

public:
	static			Engine::CShader*	Create					(void);
					void				Free					(void);

					void				Awake					(void) override;

public:
					void				SetUpConstantTable		(SP(Engine::CGraphicsC) spGC) override;
};

#endif