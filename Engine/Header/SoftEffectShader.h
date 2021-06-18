#pragma once
#include "Shader.h"

BEGIN(Engine)
class CSoftEffectShader final : public CShader
{
private:
	CSoftEffectShader();
	~CSoftEffectShader();

public:
	static CShader* Create();
	void Free();
	void Awake() override;

public:
	void SetUpConstantTable(SP(CGraphicsC) spGC) override;

};
END
