#include "EngineStdafx.h"
#include "ShaderManager.h"

#include "Shader.h"

#pragma region Shaders
#include "MeshShader.h"
#include "RectTexShader.h"
#include "DeferredBlendShader.h"
#include "DeferredLightShader.h"
#include "SliderShader.h"
#include "SkyBoxShader.h"
#include "CelShader.h"
#include "WireShader.h"
#include "MeshAlphaTestShader.h"
#pragma endregion

USING(Engine)
IMPLEMENT_SINGLETON(CShaderManager)

void CShaderManager::Awake(void)
{
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
	for (_uint i = 0; i < m_vHashKey.size(); ++i)
	{
		if (m_vHashKey[i] == shaderName)
			return i;
	}

	MSG_BOX(__FILE__, L"Wrong shaderName in CShadermanager::GetShaderID()");
	ABORT;
}

void CShaderManager::InitShaderList(_uint numOfShader)
{
	m_vShaders.resize(numOfShader);
	m_vHashKey.resize(numOfShader);

	AddKeyAndShader(CMeshShader::Create(),				L"MeshShader",				(_uint)EShaderID::MeshShader);
	AddKeyAndShader(CRectTexShader::Create(),			L"RecTexShader",			(_uint)EShaderID::RectTexShader);
	AddKeyAndShader(CDeferredBlendShader::Create(),		L"DeferredBlendShader",		(_uint)EShaderID::DeferredBlendShader);
	AddKeyAndShader(CDeferredLightShader::Create(),		L"DeferredLightShader",		(_uint)EShaderID::DeferredLightShader);
	AddKeyAndShader(CSliderShader::Create(),			L"SliderShader",			(_uint)EShaderID::SliderShader);
	AddKeyAndShader(CSkyBoxShader::Create(),			L"SkyBoxShader",			(_uint)EShaderID::SkyBoxShader);
	AddKeyAndShader(CCelShader::Create(),				L"CelShader",				(_uint)EShaderID::CelShader);
	AddKeyAndShader(CWireShader::Create(),				L"WireShader",				(_uint)EShaderID::WireShader);
	AddKeyAndShader(CMeshAlphaTestShader::Create(),		L"MeshAlphaTestShader",		(_uint)EShaderID::MeshAlphaTestShader);
}

void CShaderManager::AddKeyAndShader(CShader * pShader, std::wstring shaderKey, _uint ID)
{
	m_vHashKey[ID] = shaderKey;
	m_vShaders[ID] = pShader;
}
