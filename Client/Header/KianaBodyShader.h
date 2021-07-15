#ifndef KIANABODYSHSHADER_H
#define KIANABODYSHSHADER_H

#include "Shader.h"

class CKianaBodyShader final : public Engine::CShader
{
private:
	explicit							CKianaBodyShader		(void);
									   ~CKianaBodyShader		(void);

public:
	static			Engine::CShader*	Create					(void);
					void				Free					(void);

					void				Awake					(void) override;

public:
					void				SetUpConstantTable		(SP(Engine::CGraphicsC) spGC) override;
};

#endif