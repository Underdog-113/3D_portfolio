#ifndef FINALSHADER_H
#define FINALSHADER_H

#include "Shader.h"

BEGIN(Engine)
class ENGINE_DLL CFinalShader final : public CShader
{
private:
	explicit							CFinalShader			(void);
									   ~CFinalShader			(void);

public:
	static			CShader*			Create					(void);
					void				Free					(void);

					void				Awake					(void) override;

public:
					void				SetUpConstantTable		(SP(CGraphicsC) spGC) override;
};
END

#endif