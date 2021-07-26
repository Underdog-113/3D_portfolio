#ifndef GLOWSHADER_H
#define GLOWSHADER_H

#include "Shader.h"

BEGIN(Engine)
class ENGINE_DLL CGlowShader final : public CShader
{
private:
	explicit							CGlowShader				(void);
									   ~CGlowShader				(void);

public:
	static			CShader*			Create					(void);
					void				Free					(void);

					void				Awake					(void) override;

public:
					void				SetUpConstantTable		(SP(CGraphicsC) spGC) override;
};
END

#endif