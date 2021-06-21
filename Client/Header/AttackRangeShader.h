#pragma once
#include "Shader.h"


class CAttackRangeShader final : public Engine::CShader
{
private:
	CAttackRangeShader();
	~CAttackRangeShader();

public:
	static Engine::CShader* Create();
	void Free();
	void Awake() override;

public:
	void SetUpConstantTable(SP(Engine::CGraphicsC) spGC) override;

private:
	_float4 m_vColor;
	_float4 m_Light_Pos;
	_mat    m_mFinalMat;
	_float  m_fUVSpeed;
	_float  m_fTime;

};

