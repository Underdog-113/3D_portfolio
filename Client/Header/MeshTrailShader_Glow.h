#pragma once
#include  "Shader.h"
class CMeshTrailShader_Glow final : public Engine::CShader
{
public:
	CMeshTrailShader_Glow();
	~CMeshTrailShader_Glow();

public:
	static Engine::CShader* Create();
	void Free();
	void Awake() override;

public:
	void SetUpConstantTable(SP(Engine::CGraphicsC) spGC) override;

private:
	_float4 m_Light_Pos;
};

