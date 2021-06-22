#pragma once
#include "Shader.h"


class CSoftEffectShader final : public Engine::CShader
{
private:
	CSoftEffectShader();
	~CSoftEffectShader();

public:
	static Engine::CShader* Create();
	void Free();
	void Awake() override;

public:
	void SetUpConstantTable(SP(Engine::CGraphicsC) spGC) override;

};

