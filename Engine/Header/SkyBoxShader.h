#ifndef SKYBOXSHADER_H
#define SKYBOXSHADER_H

#include "Shader.h"

BEGIN(Engine)
class ENGINE_DLL CSkyBoxShader final : public CShader
{
private:
	explicit							CSkyBoxShader			(void);
									   ~CSkyBoxShader			(void);

public:
	static			CShader*			Create					(void);
					void				Free					(void);

					void				Awake					(void) override;

public:
					void				SetUpConstantTable		(SP(CGraphicsC) spGC) override;
};
END

#endif