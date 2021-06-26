#pragma once
class CAlphaMaskShader final : public Engine::CShader
{
private:
	CAlphaMaskShader();
	~CAlphaMaskShader() = default;

public:
	static Engine::CShader* Create();
	void Free();
	void Awake();

public:
	void SetUpConstantTable(SP(Engine::CGraphicsC) spGC) override;

	_float4 m_Light_Pos;
};

