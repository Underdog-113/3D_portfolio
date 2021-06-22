#ifndef MESHALPHATESTSHADER_H
#define MESHALPHATESTSHADER_H

#include "Shader.h"

BEGIN(Engine)
class ENGINE_DLL CMeshAlphaTestShader final : public CShader
{
private:
	explicit							CMeshAlphaTestShader	(void);
									   ~CMeshAlphaTestShader	(void);

public:
	static			CShader*			Create					(void);
					void				Free					(void);

					void				Awake					(void) override;

public:
					void				SetUpConstantTable		(SP(CGraphicsC) spGC) override;
};
END

#endif