#ifndef FACESHSHADER_H
#define FACESHSHADER_H

#include "Shader.h"

class CFaceShader final : public Engine::CShader
{
private:
	explicit							CFaceShader				(void);
									   ~CFaceShader				(void);

public:
	static			Engine::CShader*	Create					(void);
					void				Free					(void);

					void				Awake					(void) override;

public:
					void				SetUpConstantTable		(SP(Engine::CGraphicsC) spGC) override;
};

#endif