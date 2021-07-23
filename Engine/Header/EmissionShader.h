#ifndef EMISSIONSHADER_H
#define EMISSIONSHADER_H

#include "Shader.h"

BEGIN(Engine)
class ENGINE_DLL CEmissionShader final : public CShader
{
private:
	explicit							CEmissionShader			(void);
									   ~CEmissionShader			(void);

public:
	static			CShader*			Create					(void);
					void				Free					(void);

					void				Awake					(void) override;

public:
					void				SetUpConstantTable		(SP(CGraphicsC) spGC) override;
};
END

#endif