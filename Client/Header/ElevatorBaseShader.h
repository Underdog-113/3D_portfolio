#ifndef ELEVATORBASESHADER_H
#define ELEVATORBASESHADER_H

#include "Shader.h"

class CElevatorBaseShader final : public Engine::CShader
{
private:
	explicit							CElevatorBaseShader		(void);
									   ~CElevatorBaseShader		(void);

public:
	static			Engine::CShader*	Create					(void);
					void				Free					(void);

					void				Awake					(void) override;

public:
					void				SetUpConstantTable		(SP(Engine::CGraphicsC) spGC) override;
};

#endif