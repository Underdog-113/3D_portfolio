#include "EngineStdafx.h"
#include "..\Header\SpawnEffectShader.h"

USING(Engine)

CSpawnEffectShader::CSpawnEffectShader()
{
}

CSpawnEffectShader::~CSpawnEffectShader()
{
}

CShader * CSpawnEffectShader::Create()
{
	CSpawnEffectShader* pInstance = new CSpawnEffectShader;
	pInstance->Awake();


	return pInstance;
}

void CSpawnEffectShader::Free()
{
	__super::Free();
}

void CSpawnEffectShader::Awake()
{
	__super::Awake();
	m_fTime = 0.f;
	m_fUVSpeed = 0.25f;
}

void CSpawnEffectShader::SetUpConstantTable(SP(CGraphicsC) spGC)
{
	m_fTime += GET_DT;

	_mat worldMat, viewMat, projMat, WVP;

	worldMat = spGC->GetTransform()->GetLastWorldMatrix();
	viewMat = GET_MAIN_CAM->GetViewMatrix();
	projMat = GET_MAIN_CAM->GetProjMatrix();

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

	SP(CTextureC) spTexture = spGC->GetTexture();

	D3DMATERIAL9* pMtrl = &spGC->m_mtrl;

	m_pEffect->SetTexture("gDiffuseTex", spTexture->GetTexData()[spTexture->GetMeshIndex()][0]->pTexture);
	m_pEffect->SetTexture("gAlphaTex", spTexture->GetTexData()[spTexture->GetMeshIndex()][1]->pTexture);

	m_pEffect->SetFloat("gTime", m_fTime);
	m_pEffect->SetFloat("gUVSpeed", m_fUVSpeed);
}
