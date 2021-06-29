#pragma once
class CFireShader final : public Engine::CShader
{
private:
	CFireShader();
	~CFireShader();

public:
	static Engine::CShader* Create();
	void Free();
	void Awake();

public:
	void SetUpConstantTable(SP(Engine::CGraphicsC) spGC) override;


};

