#ifndef SHADOWSHADER_H
#define SHADOWSHADER_H

#include "Shader.h"

BEGIN(Engine)
class ENGINE_DLL CShadowShader final : public CShader
{
private:
	explicit							CShadowShader			(void);
									   ~CShadowShader			(void);

public:
	static			CShader*			Create					(void);
					void				Free					(void);

					void				Awake					(void) override;

public:
					void				SetUpConstantTable		(SP(CGraphicsC) spGC) override;
};
END

#endif