#include "EngineStdafx.h"
#include "ShaderStore.h"


USING(Engine)
IMPLEMENT_SINGLETON(CShaderStore)

void CShaderStore::Awake(void)
{
	__super::Awake();
	m_fpResourceHandler = std::bind(&CShaderStore::ParsingShdaer, this, std::placeholders::_1, std::placeholders::_2);
	m_resourcePath = L"..\\..\\Resource\\Shader";
}


void CShaderStore::Start(void)
{
	InitShaders();
}

void CShaderStore::OnDestroy(void)
{
	for (auto& shader : m_vShaderMap)
		shader->Release();

	m_vShaderMap.clear();
}

void CShaderStore::ClearCurResource(void)
{
}

LPD3DXEFFECT CShaderStore::GetShader(_int shaderID)
{
	if (shaderID < 0 || shaderID >= m_vShaderMap.size())
	{
		MSG_BOX(__FILE__, L"Shader Index is broken");
		ABORT;
	}

	return m_vShaderMap[shaderID];
}

void CShaderStore::InitShaders(void)
{
	__super::InitResource(m_resourcePath);
}

void CShaderStore::ParsingShdaer(std::wstring filePath, std::wstring fileName)
{
	LPD3DXEFFECT newShader	= nullptr;
	LPD3DXBUFFER errMsg		= nullptr;
	if(FAILED(D3DXCreateEffectFromFile(GET_DEVICE, 
									   (filePath + fileName).c_str(), 
									   NULL,
									   NULL, 
									   D3DXSHADER_DEBUG, NULL,
									   &newShader,
									   &errMsg)))
	{
		MSG_BOX(__FILE__, L"Create Effect from file Failed in ParsingShader");
		ABORT;
	}
	else if (nullptr != errMsg)
	{
		MSG_BOX(__FILE__, L"Shader Warning");
	}

	m_vShaderMap.emplace_back(newShader);
}
