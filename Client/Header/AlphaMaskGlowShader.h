#pragma once
class CAlphaMaskGlowShader final : public Engine::CShader
{
private:
	CAlphaMaskGlowShader();
	~CAlphaMaskGlowShader();

public:
	static Engine::CShader* Create();
	void Free();
	void Awake();

public:
	void SetUpConstantTable(SP(Engine::CGraphicsC) spGC) override;

	_float4 m_Light_Pos;
};

