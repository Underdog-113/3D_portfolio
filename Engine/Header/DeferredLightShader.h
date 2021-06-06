#ifndef DEFERREDLIGHTSHADER_H
#define DEFERREDLIGHTSHADER_H

#include "Shader.h"

BEGIN(Engine)
class ENGINE_DLL CDeferredLightShader final : public CShader
{
private:
	explicit							CDeferredLightShader	(void);
									   ~CDeferredLightShader	(void);

public:
	static			CShader*			Create					(void);
					void				Free					(void);

					void				Awake					(void) override;

public:
					void				SetUpConstantTable		(SP(CGraphicsC) spGC) override;
};
END

#endif