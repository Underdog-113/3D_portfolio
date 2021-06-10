#include "EngineStdafx.h"
#include "Shader.h"


USING(Engine)

CShader::CShader(void)
{
}

CShader::~CShader(void)
{
}

void CShader::Free(void)
{
	m_pEffect->Release();
	delete this;
}

void CShader::Awake(void)
{
	__super::Awake();
	std::wstring shaderPath = L"..\\..\\..\\Resource\\Shader\\" + m_objectKey + L".fx";
	if (FAILED(D3DXCreateEffectFromFile(GET_DEVICE, 
										shaderPath.c_str(), 
										NULL,
										NULL, 
										D3DXSHADER_DEBUG, 
										NULL,
										&m_pEffect,
										&m_pErrMsg)))
	{
		MSG_BOX(__FILE__, L"Failed creating EffectFromFile in CMeshShader::Awake()");
		ABORT;
	}
	else if (nullptr != m_pErrMsg)
	{
		MSG_BOX(__FILE__, L"CreateEffectFromFile warning in CMeshShader::Awake()");
		ABORT;
	}
}
