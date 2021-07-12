#ifndef BLURSHADER_H
#define BLURSHADER_H

#include "Shader.h"

BEGIN(Engine)
class ENGINE_DLL CBlurShader final : public CShader
{
private:
	explicit							CBlurShader				(void);
									   ~CBlurShader				(void);

public:
	static			CShader*			Create					(void);
					void				Free					(void);

					void				Awake					(void) override;

public:
					void				SetUpConstantTable		(SP(CGraphicsC) spGC) override;
};
END

#endif