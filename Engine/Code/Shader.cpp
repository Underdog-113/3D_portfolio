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
	std::wstring shaderPath = _SOLUTIONDIR L"Resource\\Shader\\" + m_objectKey + L".fx";
	if (FAILED(D3DXCreateEffectFromFile(GET_DEVICE,
										shaderPath.c_str(),
										NULL,
										NULL,
										D3DXSHADER_ENABLE_BACKWARDS_COMPATIBILITY,
										NULL,
										&m_pEffect,
										&m_pErrMsg)))
	{
		MSG_BOX(__FILE__, L"Failed creating EffectFromFile in CShader::Awake()");
		ABORT;
	}
	else if (nullptr != m_pErrMsg)
	{
		std::string pErrMsg = (char*)m_pErrMsg->GetBufferPointer();
		MSG_BOX(__FILE__, (L"CreateEffectFromFile warning in " + m_objectKey + L"::Awake()").c_str());
	}

	m_vRenderTargets.resize(4, nullptr);
}

void CShader::SetupWorldViewProj(SP(CGraphicsC) spGC)
{
	_mat worldMat, viewMat, projMat;

	worldMat = spGC->GetTransform()->GetWorldMatrix();
	viewMat = GET_MAIN_CAM->GetViewMatrix();
	projMat = GET_MAIN_CAM->GetProjMatrix();

	m_pEffect->SetMatrix("g_matWorld", &worldMat);
	m_pEffect->SetMatrix("g_matView", &viewMat);
	m_pEffect->SetMatrix("g_matProj", &projMat);

	m_pEffect->CommitChanges();
}

void CShader::SetupOrthoWVP(SP(CGraphicsC) spGC)
{
	_mat worldMat, viewMat, projMat;

	worldMat = spGC->GetTransform()->GetWorldMatrix();
	D3DXMatrixIdentity(&viewMat);
	projMat = GET_MAIN_CAM->GetOrthoMatrix();

	m_pEffect->SetMatrix("g_matWorld", &worldMat);
	m_pEffect->SetMatrix("g_matView", &viewMat);
	m_pEffect->SetMatrix("g_matProj", &projMat);
	m_pEffect->CommitChanges();
}
