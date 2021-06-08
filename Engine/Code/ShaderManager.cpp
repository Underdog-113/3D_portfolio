#include "EngineStdafx.h"
#include "ShaderManager.h"

#include "Shader.h"

#pragma region Shaders
#include "MeshShader.h"
#include "RectTexShader.h"
#include "DeferredBlendShader.h"
#include "DeferredLightShader.h"
#include "SliderShader.h"
#pragma endregion

USING(Engine)
IMPLEMENT_SINGLETON(CShaderManager)

void CShaderManager::Awake(void)
{
	m_vShaders.emplace_back(CMeshShader::Create());
	m_vShaders.emplace_back(CRectTexShader::Create());
	m_vShaders.emplace_back(CDeferredBlendShader::Create());
	m_vShaders.emplace_back(CDeferredLightShader::Create());
	m_vShaders.emplace_back(CSliderShader::Create());
}

void CShaderManager::OnDestroy(void)
{
	for (auto& shader : m_vShaders)
	{
		shader->Free();
	}

	m_vShaders.clear();
}

CShader* CShaderManager::GetShader(_int shaderID)
{
	if (shaderID < 0 || shaderID >= m_vShaders.size())
	{
		MSG_BOX(__FILE__, L"Shader Index is broken");
		ABORT;
	}

	return m_vShaders[shaderID];
}

_int CShaderManager::GetShaderID(std::wstring shaderName)
{
	if (shaderName == L"MeshShader")
		return (_int)EShaderID::MeshShader;
	else if (shaderName == L"RectTexShader")
		return (_int)EShaderID::RectTexShader;
	else if (shaderName == L"DeferredBlendShader")
		return (_int)EShaderID::DeferredBlendShader;
	else if (shaderName == L"DeferredLightShader")
		return (_int)EShaderID::DeferredLightShader;
	else if (shaderName == L"SkyBoxShader")
		return (_int)EShaderID::SkyBoxShader;
	else if (shaderName == L"SliderShader")
		return (_int)EShaderID::SliderShader;
	else
	{
		MSG_BOX(__FILE__, L"Wrong shdaer name in CShaderManager::GetShaderID");
		ABORT;
	}
}