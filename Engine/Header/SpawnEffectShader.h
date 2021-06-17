#pragma once
#include "Shader.h"

BEGIN(Engine)
class CSpawnEffectShader final : public CShader
{
private:
	CSpawnEffectShader();
	~CSpawnEffectShader();

public:
	static CShader* Create();
	void Free();
	void Awake() override;

public:
	void SetUpConstantTable(SP(CGraphicsC) spGC) override;

private:
	_float4 m_vColor;
	_float4 m_Light_Pos;
	_mat    m_mFinalMat;
	_float  m_fUVSpeed;
	_float  m_fTime;

};

