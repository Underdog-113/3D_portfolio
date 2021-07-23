#pragma once
#include "Shader.h"

class CDissolveShader_Glow final : public Engine::CShader
{
public:
	CDissolveShader_Glow();
	~CDissolveShader_Glow();

public:
	static Engine::CShader* Create();
	void Free();
	void Awake() override;

public:
	void SetUpConstantTable(SP(Engine::CGraphicsC) spGC) override;

private:
	_float4 m_Light_Pos;
};

