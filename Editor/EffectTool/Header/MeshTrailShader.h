#pragma once
#include "Shader.h"


class CMeshTrailShader final : public Engine::CShader
{
private:
	CMeshTrailShader();
	~CMeshTrailShader();

public:
	static Engine::CShader* Create();
	void Free();
	void Awake() override;

public:
	void SetUpConstantTable(SP(Engine::CGraphicsC) spGC) override;

private:
	_float4 m_Light_Pos;
};

