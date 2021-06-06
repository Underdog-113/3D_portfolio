#ifndef DEFERREDBLENDSHADER_H
#define DEFERREDBLENDSHADER_H

#include "Shader.h"

BEGIN(Engine)
class ENGINE_DLL CDeferredBlendShader final : public CShader
{
private:
	explicit							CDeferredBlendShader	(void);
									   ~CDeferredBlendShader	(void);

public:
	static			CShader*			Create					(void);
					void				Free					(void);

					void				Awake					(void) override;

public:
					void				SetUpConstantTable		(SP(CGraphicsC) spGC) override;
};
END

#endif