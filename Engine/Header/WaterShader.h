#pragma once

#include "Shader.h"

BEGIN(Engine)
class ENGINE_DLL CWaterShader final : public CShader
{
private:
	CWaterShader();
	~CWaterShader() = default;

public:
	static CShader* Create();
	void Free();
	void Awake() override;

public:
	void SetUpConstantTable(SP(CGraphicsC) spGC) override;
	
};
END
