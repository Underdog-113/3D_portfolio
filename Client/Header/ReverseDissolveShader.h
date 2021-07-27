#pragma once
#include "Shader.h"

class CReverseDissolveShader final : public Engine::CShader
{
public:
	CReverseDissolveShader();
	~CReverseDissolveShader();

public:
	static Engine::CShader* Create();
	void Free();
	void Awake() override;

public:
	void SetUpConstantTable(SP(Engine::CGraphicsC) spGC) override;

private:
	_float4 m_Light_Pos;
	GETTOR_SETTOR(_float4, m_addColor, ZERO_VEC4, AddColor)
	GETTOR_SETTOR(_float4, m_multColor, _float4(1.f, 1.f, 1.f, 1.f), MultColor)
};

