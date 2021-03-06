#ifndef STAGE2GLOWSHADER_H
#define STAGE2GLOWSHADER_H

#include "Shader.h"

class CStage2GlowShader final : public Engine::CShader
{
private:
	explicit							CStage2GlowShader		(void);
									   ~CStage2GlowShader		(void);

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