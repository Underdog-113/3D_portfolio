#pragma once
class CLaserTrailShader final : public Engine::CShader
{
public:
	CLaserTrailShader();
	~CLaserTrailShader();

public:
	static Engine::CShader* Create();
	void Free();
	void Awake();

public:
	void SetUpConstantTable(SP(Engine::CGraphicsC) spGC) override;

};

