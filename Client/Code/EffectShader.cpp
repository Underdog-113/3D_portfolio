#include "stdafx.h"
#include "EffectShader.h"

CEffectShader::CEffectShader()
{
}


CEffectShader::~CEffectShader()
{
}

Engine::CShader * CEffectShader::Create()
{
	CEffectShader* pInstance = new CEffectShader;
	pInstance->Awake();

	return pInstance;
}

void CEffectShader::Free()
{
	__super::Free();
}

void CEffectShader::Awake()
{
	__super::Awake();
	m_fTime = 0.f;
	m_fUVSpeed = 0.25f;
}

void CEffectShader::SetUpConstantTable(SP(Engine::CGraphicsC) spGC)
{
	m_fTime += GET_DT;

	_mat worldMat, viewMat, projMat;

	worldMat = spGC->GetTransform()->GetWorldMatrix();
	viewMat = Engine::GET_MAIN_CAM->GetViewMatrix();
	projMat = Engine::GET_MAIN_CAM->GetProjMatrix();

	m_pEffect->SetMatrix("g_WorldMat", &worldMat);
	m_pEffect->SetMatrix("g_ViewMat", &viewMat);
	m_pEffect->SetMatrix("g_ProjMat", &projMat);


	m_mFinalMat = worldMat * viewMat * projMat;

	// 광원의 방향
	m_Light_Pos = D3DXVECTOR4(-0.577f, -0.577f, -0.577f, 0.f);
	D3DXMatrixInverse(&m_mFinalMat, NULL, &worldMat);
	D3DXVec4Transform(&m_vColor, &m_Light_Pos, &m_mFinalMat);
	D3DXVec3Normalize((D3DXVECTOR3 *)&m_vColor, (D3DXVECTOR3 *)&m_vColor);
	m_vColor.w = -1.f;		// 환경광 강도

	m_pEffect->SetVector("g_WorldLightPos", &m_vColor);

	// 시점(로컬좌표계)

	m_vColor = D3DXVECTOR4(0, 0, 0, 1);
	m_pEffect->SetVector("g_WorldCameraPos", &m_vColor);

	SP(Engine::CTextureC) spTexture = spGC->GetTexture();
	m_pEffect->SetTexture("g_SpecularTex", spTexture->GetTexData()[spTexture->GetSetIndex()][1]->pTexture);

	//D3DMATERIAL9* pMtrl = &spGC->m_mtrl;
	//
	//size_t _dwMaterials = spGC->GetMesh()->GetMeshData()->GetSubsetCount();
	//
	//for (size_t i = 0; i < _dwMaterials; ++i)
	//{
	//	m_vColor.x = pMtrl->Diffuse.r;
	//	m_vColor.y = pMtrl->Diffuse.g;
	//	m_vColor.z = pMtrl->Diffuse.b;
	//
	//	m_pEffect->SetVector("g_LightColor", &m_vColor);
	//	m_pEffect->SetTexture("g_DiffuseTex", spTexture->GetTexData()[spTexture->GetSetIndex()][i]->pTexture);
	//
	//	pMtrl++;
	//}	


	m_pEffect->SetFloat("g_fTime", m_fTime);
	m_pEffect->SetFloat("g_fUVSpeed", m_fUVSpeed);
}
