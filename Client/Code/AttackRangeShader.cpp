#include "stdafx.h"
#include "..\Header\AttackRangeShader.h"

CAttackRangeShader::CAttackRangeShader()
{
}

CAttackRangeShader::~CAttackRangeShader()
{
}

Engine::CShader * CAttackRangeShader::Create()
{
	CAttackRangeShader* pInstance = new CAttackRangeShader;
	pInstance->Awake();


	return pInstance;
}

void CAttackRangeShader::Free()
{
	__super::Free();
}

void CAttackRangeShader::Awake()
{
	__super::Awake();
	m_fTime = 0.f;
	m_fUVSpeed = 0.25f;
}

void CAttackRangeShader::SetUpConstantTable(SP(Engine::CGraphicsC) spGC)
{
	m_fTime += GET_DT;

	_mat worldMat, viewMat, projMat, WVP;

	worldMat = spGC->GetTransform()->GetLastWorldMatrix();
	viewMat = Engine::GET_MAIN_CAM->GetViewMatrix();
	projMat = Engine::GET_MAIN_CAM->GetProjMatrix();

	m_pEffect->SetMatrix("gWorld", &worldMat);
	m_pEffect->SetMatrix("gView", &viewMat);
	m_pEffect->SetMatrix("gProjection", &projMat);

	WVP = worldMat * viewMat * projMat;

	m_pEffect->SetMatrix("gWorldViewProjectionMatrix", &WVP);

	// Get Inverse Transpose of World Matrix
	_mat iTWM;
	D3DXMatrixInverse(&iTWM, 0, &worldMat);
	D3DXMatrixTranspose(&iTWM, &iTWM);

	m_pEffect->SetMatrix("gInvWorldMatrix", &worldMat);

	_float4 worldLightPos = _float4(500.f, 500.f, -500.f, 1.f);

	m_pEffect->SetVector("gWorldLightPosition", &worldLightPos);

	SP(Engine::CTextureC) spTexture = spGC->GetTexture();

	_int TexIndex = spTexture->GetNumOfTex();

	if (TexIndex == 2)
	{
		m_pEffect->SetTexture("gDiffuseTex", spTexture->GetTexData()[spTexture->GetMeshIndex()][0]->pTexture);
		m_pEffect->SetTexture("gAlphaTex", spTexture->GetTexData()[spTexture->GetMeshIndex()][1]->pTexture);
	}
	else
	{
		m_pEffect->SetTexture("gDiffuseTex", spTexture->GetTexData()[spTexture->GetMeshIndex()][0]->pTexture);
		//m_pEffect->SetTexture("gAlphaTex", spTexture->GetTexData()[spTexture->GetMeshIndex()][0]->pTexture);
	}

	m_pEffect->SetFloat("gTime", m_fTime);
	m_pEffect->SetFloat("gUVSpeed", m_fUVSpeed);
}
