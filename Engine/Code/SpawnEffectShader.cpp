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
}

void CSpawnEffectShader::SetUpConstantTable(SP(CGraphicsC) spGC)
{
	m_fTime += GET_DT;

	_mat worldMat, viewMat, projMat;

	worldMat = spGC->GetTransform()->GetLastWorldMatrix();
	viewMat = GET_MAIN_CAM->GetViewMatrix();
	projMat = GET_MAIN_CAM->GetProjMatrix();

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

	SP(CTextureC) spTexture = spGC->GetTexture();
	m_pEffect->SetTexture("g_DiffuseTex", spTexture->GetTexData()[spTexture->GetMeshIndex()][0]->pTexture);
	m_pEffect->SetTexture("g_SpecularTex", spTexture->GetTexData()[spTexture->GetMeshIndex()][1]->pTexture);

	D3DMATERIAL9* pMtrl = &spGC->m_mtrl;

	size_t _dwMaterials = spGC->GetMesh()->GetMeshDatas().size();

	m_pEffect->SetVector("g_LightColor", &m_vColor);

	m_pEffect->SetFloat("g_fTime", m_fTime);
	m_pEffect->SetFloat("g_fUVSpeed", m_fUVSpeed);
}
