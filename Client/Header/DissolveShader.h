#pragma once
#include "Shader.h"


class CDissolveShader final : public Engine::CShader
{
private:
	CDissolveShader();
	~CDissolveShader();

public:
	static Engine::CShader* Create();
	void Free();
	void Awake() override;

public:
	void SetUpConstantTable(SP(Engine::CGraphicsC) spGC) override;

private:
	_float4 m_Light_Pos;
};


