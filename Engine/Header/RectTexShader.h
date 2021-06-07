#ifndef RECTTEXSHADER_H
#define RECTTEXSHADER_H

#include "Shader.h"

BEGIN(Engine)
class ENGINE_DLL CRectTexShader final : public CShader
{
private:
	explicit							CRectTexShader			(void);
									   ~CRectTexShader			(void);

public:
	static			CShader*			Create					(void);
					void				Free					(void);

					void				Awake					(void) override;

public:
					void				SetUpConstantTable		(SP(CGraphicsC) spGC) override;
};
END

#endif