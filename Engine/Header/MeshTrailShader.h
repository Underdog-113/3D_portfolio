#pragma once
#include "Shader.h"

BEGIN(Engine)
class CMeshTrailShader final : public CShader
{
private:
	CMeshTrailShader();
	~CMeshTrailShader();

public:
	static CShader* Create();
	void Free();
	void Awake() override;

public:
	void SetUpConstantTable(SP(CGraphicsC) spGC) override;

private:
	_float4 m_Light_Pos;
};
END
