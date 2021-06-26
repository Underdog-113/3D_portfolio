#include "stdafx.h"
#include "..\Header\WaterShader.h"

CWaterShader::CWaterShader()
{
}

Engine::CShader * CWaterShader::Create()
{
	CWaterShader* pInstance = new CWaterShader;
	pInstance->Awake();

	return pInstance;
}

void CWaterShader::Free()
{
	__super::Free();
}

void CWaterShader::Awake()
{
	__super::Awake();
	m_fTime = 0.f;
}

void CWaterShader::SetUpConstantTable(SP(Engine::CGraphicsC) spGC)
{
	// 아직 스페큘러 사용안함.
	m_fTime += GET_DT;

	_mat worldMat, viewMat, projMat;

	worldMat = spGC->GetTransform()->GetLastWorldMatrix();
	viewMat = Engine::GET_MAIN_CAM->GetViewMatrix();
	projMat = Engine::GET_MAIN_CAM->GetProjMatrix();

	m_pEffect->SetMatrix("g_WorldMat", &worldMat);
	m_pEffect->SetMatrix("g_ViewMat", &viewMat);
	m_pEffect->SetMatrix("g_ProjMat", &projMat);


	m_mFinalMat = worldMat * viewMat * projMat;

	// 광원의 방향
	m_Light_Pos = D3DXVECTOR4(500.f, 500.f, -500.f, 1.f);
	D3DXMatrixInverse(&m_mFinalMat, NULL, &worldMat);
	D3DXVec4Transform(&m_vColor, &m_Light_Pos, &m_mFinalMat);
	D3DXVec3Normalize((D3DXVECTOR3 *)&m_vColor, (D3DXVECTOR3 *)&m_vColor);
	m_vColor.w = 1.f;		// 환경광 강도

	m_pEffect->SetVector("g_WorldLightPos", &m_vColor);

	// 시점(로컬좌표계)

	m_vColor = D3DXVECTOR4(1, 1, 1, 1);
	m_pEffect->SetVector("g_WorldCameraPos", &m_vColor);

	SP(Engine::CTextureC) spTexture = spGC->GetTexture();
	m_pEffect->SetTexture("g_DiffuseTex", spTexture->GetTexData()[spTexture->GetSetIndex()][0]->pTexture);
	//m_pEffect->SetTexture("g_SpecularTex", spTexture->GetTexData()[spTexture->GetSetIndex()][1]->pTexture);

	m_pEffect->SetVector("g_LightColor", &m_vColor);

	m_pEffect->SetFloat("g_fTime", m_fTime);
}
