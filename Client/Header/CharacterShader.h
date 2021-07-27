#ifndef CHARACTERSHADER_H
#define CHARACTERSHADER_H

#include "Shader.h"

class CCharacterShader final : public Engine::CShader
{
private:
	explicit							CCharacterShader		(void);
									   ~CCharacterShader		(void);

public:
	static			Engine::CShader*	Create					(void);
					void				Free					(void);

					void				Awake					(void) override;

public:
					void				SetUpConstantTable		(SP(Engine::CGraphicsC) spGC) override;

			GETTOR_SETTOR	(_float4,		m_addColor,		ZERO_VEC4,	AddColor)
			GETTOR_SETTOR	(_float4,		m_multColor,	_float4(1.f,1.f,1.f,1.f),	MultColor)
};

#endif