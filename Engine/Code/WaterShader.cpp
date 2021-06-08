#include "EngineStdafx.h"
#include "..\Header\WaterShader.h"

USING(Engine)

CWaterShader::CWaterShader()
{
}

CShader * CWaterShader::Create()
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
}

void CWaterShader::SetUpConstantTable(SP(CGraphicsC) spGC)
{
	LPDIRECT3DDEVICE9 pDevice = GET_DEVICE;
	
	_mat worldMat, viewMat, projMat;

	worldMat = spGC->GetTransform()->GetLastWorldMatrix();

	viewMat = GET_MAIN_CAM->GetViewMatrix();
	projMat = GET_MAIN_CAM->GetProjMatrix();

	_m = worldMat * viewMat * projMat;
	m_pEffect->SetMatrix("g_mWVP", &_m);

	// 광원의 방향
	_Light_Pos = D3DXVECTOR4(-0.577f, -0.577f, -0.577f, 0.f);
	D3DXMatrixInverse(&_m, NULL, &worldMat);
	D3DXVec4Transform(&_v, &_Light_Pos, &_m);
	D3DXVec3Normalize((D3DXVECTOR3 *)&_v, (D3DXVECTOR3 *)&_v);
	_v.w = -1.f;		// 환경광 강도

	m_pEffect->SetVector("g_vLightDir", &_v);

	// 시점(로컬좌표계)

	_v = D3DXVECTOR4(0, 0, 0, 1);
	m_pEffect->SetVector("g_vEyePos", &_v);
		

	SP(CTextureC) spTexture = spGC->GetTexture();
	m_pEffect->SetTexture("g_NormalMap", spTexture->GetTexData()[spTexture->GetMeshIndex()][1]->pTexture);

	
	D3DMATERIAL9* pMtrl = &spGC->m_mtrl;

	size_t _dwMaterials = spGC->GetMesh()->GetMeshDatas().size();

	for (size_t i = 0; i < _dwMaterials; ++i)
	{
		_v.x = pMtrl->Diffuse.r;
		_v.y = pMtrl->Diffuse.g;
		_v.z = pMtrl->Diffuse.b;
		m_pEffect->SetVector("g_vColor", &_v);
		m_pEffect->SetTexture("g_DecaleTex", spTexture->GetTexData()[spTexture->GetMeshIndex()][i]->pTexture);
		pMtrl++;
	}
}
