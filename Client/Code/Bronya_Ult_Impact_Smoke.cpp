#include "stdafx.h"
#include "..\Header\Bronya_Ult_Impact_Smoke.h"

_uint CBronya_Ult_Impact_Smoke::m_s_uniqueID = 0;

CBronya_Ult_Impact_Smoke::CBronya_Ult_Impact_Smoke()
{
}


CBronya_Ult_Impact_Smoke::~CBronya_Ult_Impact_Smoke()
{
}

SP(CBronya_Ult_Impact_Smoke) CBronya_Ult_Impact_Smoke::Create(_bool isStatic, Engine::CScene * pScene)
{
	SP(CBronya_Ult_Impact_Smoke) spInstance(new CBronya_Ult_Impact_Smoke, Engine::SmartDeleter<CBronya_Ult_Impact_Smoke>);
	spInstance->SetIsStatic(isStatic);
	spInstance->SetScene(pScene);
	spInstance->Awake();

	return spInstance;
}

SP(Engine::CObject) CBronya_Ult_Impact_Smoke::MakeClone()
{
	SP(CBronya_Ult_Impact_Smoke) spClone(new CBronya_Ult_Impact_Smoke, Engine::SmartDeleter<CBronya_Ult_Impact_Smoke>);
	__super::InitClone(spClone);

	spClone->m_spTransform = spClone->GetComponent<Engine::CTransformC>();
	spClone->m_spMesh = spClone->GetComponent<Engine::CMeshC>();
	spClone->m_spGraphics = spClone->GetComponent<Engine::CGraphicsC>();
	spClone->m_spShader = spClone->GetComponent<Engine::CShaderC>();
	spClone->m_spTexture = spClone->GetComponent<Engine::CTextureC>();

	return spClone;
}

void CBronya_Ult_Impact_Smoke::Awake()
{
	__super::Awake();

}

void CBronya_Ult_Impact_Smoke::Start()
{
	__super::Start();
	m_fAlpha = 1.f;
}

void CBronya_Ult_Impact_Smoke::FixedUpdate()
{
	__super::FixedUpdate();

}

void CBronya_Ult_Impact_Smoke::Update()
{
	__super::Update();

	if (m_fAlpha <= 0)
	{
		this->SetDeleteThis(true);
	}

	m_fAlpha -= 0.5f * GET_DT;
}

void CBronya_Ult_Impact_Smoke::LateUpdate()
{
	__super::LateUpdate();
	Billboard();
}

void CBronya_Ult_Impact_Smoke::PreRender(LPD3DXEFFECT pEffect)
{
	m_spMesh->PreRender(m_spGraphics, pEffect);
	pEffect->SetFloat("gAlpha", m_fAlpha);
}

void CBronya_Ult_Impact_Smoke::Render(LPD3DXEFFECT pEffect)
{
	m_spMesh->Render(m_spGraphics, pEffect);

}

void CBronya_Ult_Impact_Smoke::PostRender(LPD3DXEFFECT pEffect)
{
	m_spMesh->PostRender(m_spGraphics, pEffect);

}

void CBronya_Ult_Impact_Smoke::OnDestroy()
{
	__super::OnDestroy();

}

void CBronya_Ult_Impact_Smoke::OnEnable()
{
	__super::OnEnable();

}

void CBronya_Ult_Impact_Smoke::OnDisable()
{
	__super::OnDisable();

}

void CBronya_Ult_Impact_Smoke::SetBasicName()
{
	m_name = m_objectKey + std::to_wstring(m_s_uniqueID++);

}

void CBronya_Ult_Impact_Smoke::Billboard()
{
	_mat matWorld, matView, matBill;

	matView = Engine::GET_MAIN_CAM->GetViewMatrix();

	D3DXMatrixIdentity(&matBill);

	memcpy(&matBill.m[0][0], &matView.m[0][0], sizeof(_float3));
	memcpy(&matBill.m[1][0], &matView.m[1][0], sizeof(_float3));
	memcpy(&matBill.m[2][0], &matView.m[2][0], sizeof(_float3));

	D3DXMatrixInverse(&matBill, 0, &matBill);

	matWorld = m_spGraphics->GetTransform()->GetWorldMatrix();

	m_spGraphics->GetTransform()->SetWorldMatrix(matBill * matWorld);
}
