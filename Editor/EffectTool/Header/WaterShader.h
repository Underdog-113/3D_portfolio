#pragma once

#include "Shader.h"

class CWaterShader final : public Engine::CShader
{
private:
	CWaterShader();
	~CWaterShader() = default;

public:
	static Engine::CShader* Create();
	void Free();
	void Awake() override;

public:
	void SetUpConstantTable(SP(Engine::CGraphicsC) spGC) override;

	_float4 m_vColor;
	_float4 m_Light_Pos;
	_mat    m_mFinalMat;
	_float  m_fUVSpeed;
	_float  m_fTime;
};

