#pragma once
class CEffectMaker
{
public:
	CEffectMaker();
	~CEffectMaker();

public:
	SP(Engine::CObject) CreateEffect_Trail(std::wstring objectKey, std::wstring name, std::wstring texName1, std::wstring texName2, std::wstring texName3);
	SP(Engine::CObject) CreateEffect_AlphaMask(std::wstring objectKey, std::wstring name, std::wstring texName1, std::wstring texName2);
	SP(Engine::CObject) CreateEffect_Dissolve(std::wstring objectKey, std::wstring name, std::wstring texName1, std::wstring texName2);
	SP(Engine::CObject) CreateEffect_Dissolve(std::wstring objectKey, std::wstring name, std::wstring texName1, std::wstring texName2, std::wstring texName3);
	SP(Engine::CObject) CreateEffect_Fire(std::wstring objectKey, std::wstring name, std::wstring texName1, std::wstring texName2);

protected:
	Engine::CObject* m_pOwner;
};

