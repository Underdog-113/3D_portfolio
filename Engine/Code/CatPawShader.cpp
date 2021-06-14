#include "EngineStdafx.h"
#include "..\Header\CatPawShader.h"

USING(Engine)

CCatPawShader::CCatPawShader()
{
}


CCatPawShader::~CCatPawShader()
{
}

CShader * CCatPawShader::Create()
{
	CCatPawShader* pInstance = new CCatPawShader;
	pInstance->Awake();

	return pInstance;
}

void CCatPawShader::Free()
{
	__super::Free();
}

void CCatPawShader::Awake()
{
	__super::Awake();
	m_fTime = 0.f;
	m_fUVSpeed = 0.25f;
}

void CCatPawShader::SetUpConstantTable(SP(CGraphicsC) spGC)
{
	_float4 LightDir;
	LightDir = _float4(-0, -40.f, -70.f, 0.f);

	_mat worldMat, viewMat, projMat, WVP;

	worldMat = spGC->GetTransform()->GetLastWorldMatrix();
	viewMat = GET_MAIN_CAM->GetViewMatrix();
	projMat = GET_MAIN_CAM->GetProjMatrix();

	WVP = worldMat * viewMat * projMat;
	m_pEffect->SetMatrix("m_WVP", &WVP);

	_mat m;
	_float4 v;

	//Light
	D3DXVec3Normalize((D3DXVECTOR3*)&LightDir, (D3DXVECTOR3*)&LightDir);
	D3DXMatrixInverse(&m, NULL, &worldMat);
	D3DXVec4Transform(&v, &LightDir, &m);
	D3DXVec4Normalize(&v, &v);
	m_pEffect->SetVector("m_LightDir", &v);

	D3DMATERIAL9* pMtrl = &spGC->m_mtrl;
	size_t _dwMaterials = spGC->GetMesh()->GetMeshDatas().size();
	SP(CTextureC) spTexture = spGC->GetTexture();

	m_pEffect->SetTexture("g_NormalTex", spTexture->GetTexData()[spTexture->GetMeshIndex()][1]->pTexture);
	
	for (size_t i = 0; i < _dwMaterials; ++i)
	{
		m_pEffect->SetTexture("g_BaseTexture", spTexture->GetTexData()[spTexture->GetMeshIndex()][i]->pTexture);

		pMtrl++;
	}

	m_pEffect->SetTechnique("TShader");

	//m_fTime += GET_DT;

	//_mat worldMat, viewMat, projMat;

	//worldMat = spGC->GetTransform()->GetLastWorldMatrix();
	//viewMat = GET_MAIN_CAM->GetViewMatrix();
	//projMat = GET_MAIN_CAM->GetProjMatrix();

	//m_pEffect->SetMatrix("g_WorldMat", &worldMat);
	//m_pEffect->SetMatrix("g_ViewMat", &viewMat);
	//m_pEffect->SetMatrix("g_ProjMat", &projMat);


	//

	//m_mFinalMat = /*worldMat **/ viewMat * projMat;

	//m_pEffect->SetMatrix("g_ViewProjection", &m_mFinalMat);
	//m_pEffect->SetVector("g_ViewPosition", &_float4(1.f,-1.f,1.f,1.f));



	//// 광원의 방향
	////m_Light_Pos = D3DXVECTOR4(-0.577f, -0.577f, -0.577f, 0.f);
	////D3DXMatrixInverse(&m_mFinalMat, NULL, &worldMat);
	////D3DXVec4Transform(&m_vColor, &m_Light_Pos, &m_mFinalMat);
	////D3DXVec3Normalize((D3DXVECTOR3 *)&m_vColor, (D3DXVECTOR3 *)&m_vColor);
	////m_vColor.w = -1.f;		// 환경광 강도

	////m_pEffect->SetVector("g_WorldLightPos", &m_vColor);

	//// 시점(로컬좌표계)
	//m_pEffect->SetFloat("g_PixelOffsetX", 1.f);
	//m_pEffect->SetFloat("g_PixelOffsetY", 1.f);

	//m_vColor = _float4(0, 0, 0, 1);

	//m_pEffect->SetVector("g_WorldCameraPos", &m_vColor);

	//SP(CTextureC) spTexture = spGC->GetTexture();
	//m_pEffect->SetTexture("g_BumpMap", spTexture->GetTexData()[spTexture->GetMeshIndex()][1]->pTexture);

	//D3DMATERIAL9* pMtrl = &spGC->m_mtrl;

	//size_t _dwMaterials = spGC->GetMesh()->GetMeshDatas().size();

	//for (size_t i = 0; i < _dwMaterials; ++i)
	//{
	//	m_vColor.x = pMtrl->Diffuse.r;
	//	m_vColor.y = pMtrl->Diffuse.g;
	//	m_vColor.z = pMtrl->Diffuse.b;

	//	m_pEffect->SetTexture("g_DiffuseTex", spTexture->GetTexData()[spTexture->GetMeshIndex()][i]->pTexture);

	//	pMtrl++;
	//}	

	//m_vRimColor = _float4(1.f, 0.5f, 0.f, 1.f);

	//m_pEffect->SetFloat("g_RimPower", 2.f);
	//m_pEffect->SetVector("g_RimColor", &m_vRimColor);
	//m_pEffect->SetVector("g_LineColor", &_float4(1.f, 0.f,0.f, 1.f));

}
