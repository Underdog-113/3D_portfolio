#pragma once
#include "Shader.h"

class CSoftEffectShader_Glow  final : public Engine::CShader
{
public:
	CSoftEffectShader_Glow();
	~CSoftEffectShader_Glow();

public:
	static Engine::CShader* Create();
	void Free();
	void Awake() override;

public:
	void SetUpConstantTable(SP(Engine::CGraphicsC) spGC) override;
};

