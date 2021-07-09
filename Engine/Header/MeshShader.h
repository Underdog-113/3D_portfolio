#ifndef MESHSHADER_H
#define MESHSHADER_H

#include "Shader.h"

BEGIN(Engine)
class ENGINE_DLL CMeshShader final : public CShader
{
private:
	explicit							CMeshShader				(void);
									   ~CMeshShader				(void);

public:
	static			CShader*			Create					(void);
					void				Free					(void);

					void				Awake					(void) override;

public:
					void				SetUpConstantTable		(SP(CGraphicsC) spGC) override;


			GETTOR_SETTOR	(_float4,		m_addColor,		ZERO_VEC4,	AddColor)
};
END

#endif