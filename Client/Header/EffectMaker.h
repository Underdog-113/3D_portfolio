#pragma once
class CEffectMaker
{
public:
	CEffectMaker();
	~CEffectMaker();

public:
	SP(Engine::CObject) CreateEffect(std::wstring objectKey, std::wstring name, std::wstring texName1, std::wstring texName2, std::wstring objName = L"Valkyrie_Effect");

protected:
	Engine::CObject* m_pOwner;
};

