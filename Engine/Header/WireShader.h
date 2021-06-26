#ifndef WIRESHADER_H
#define WIRESHADER_H

#include "Shader.h"

BEGIN(Engine)
class ENGINE_DLL CWireShader final : public CShader
{
private:
	explicit							CWireShader				(void);
									   ~CWireShader				(void);

public:
	static			CShader*			Create					(void);
					void				Free					(void);

					void				Awake					(void) override;

public:
					void				SetUpConstantTable		(SP(CGraphicsC) spGC) override;
};
END

#endif