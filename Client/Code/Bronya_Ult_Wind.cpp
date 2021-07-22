#include "stdafx.h"
#include "..\Header\Bronya_Ult_Wind.h"

_uint CBronya_Ult_Wind::m_s_uniqueID = 0;

CBronya_Ult_Wind::CBronya_Ult_Wind()
{
}


CBronya_Ult_Wind::~CBronya_Ult_Wind()
{
}

SP(CBronya_Ult_Wind) CBronya_Ult_Wind::Create(_bool isStatic, Engine::CScene * pScene)
{
	SP(CBronya_Ult_Wind) spInstance(new CBronya_Ult_Wind, Engine::SmartDeleter<CBronya_Ult_Wind>);
	spInstance->SetIsStatic(isStatic);
	spInstance->SetScene(pScene);
	spInstance->Awake();

	return spInstance;
}

SP(Engine::CObject) CBronya_Ult_Wind::MakeClone()
{
	SP(CBronya_Ult_Wind) spClone(new CBronya_Ult_Wind, Engine::SmartDeleter<CBronya_Ult_Wind>);
	__super::InitClone(spClone);

	spClone->m_spTransform = spClone->GetComponent<Engine::CTransformC>();
	spClone->m_spMesh = spClone->GetComponent<Engine::CMeshC>();
	spClone->m_spGraphics = spClone->GetComponent<Engine::CGraphicsC>();
	spClone->m_spShader = spClone->GetComponent<Engine::CShaderC>();
	spClone->m_spTexture = spClone->GetComponent<Engine::CTextureC>();

	return spClone;
}

void CBronya_Ult_Wind::Awake()
{
	__super::Awake();
	m_spMesh->SetMeshData(L"Bronya_Plane2");
	m_spMesh->SetIsEffectMesh(true);
	m_spGraphics->SetRenderID((_int)Engine::ERenderID::AlphaBlend);
	m_spTexture->AddTexture(L"Impact_Red");
	m_spTexture->AddTexture(L"CircleRing_01");
	m_spShader->AddShader((_int)EShaderID::AlphaMaskShader);
}

void CBronya_Ult_Wind::Start()
{
	__super::Start();
	m_fAngle = 0.f;
	m_fAlpha = 1.f;
}

void CBronya_Ult_Wind::FixedUpdate()
{
	__super::FixedUpdate();

}

void CBronya_Ult_Wind::Update()
{
	__super::Update();

	_mat matRot;

	m_fAngle += D3DXToRadian(30) * GET_DT;

	D3DXMatrixRotationAxis(&matRot, &m_spTransform->GetForward(), m_fAngle);
	m_spTransform->SetParentRotMatrix(matRot);
}

void CBronya_Ult_Wind::LateUpdate()
{
	__super::LateUpdate();

}

void CBronya_Ult_Wind::PreRender(LPD3DXEFFECT pEffect)
{
	m_spMesh->PreRender(m_spGraphics, pEffect);
	pEffect->SetFloat("gAlpha", m_fAlpha);
	pEffect->CommitChanges();

}

void CBronya_Ult_Wind::Render(LPD3DXEFFECT pEffect)
{
	m_spMesh->Render(m_spGraphics, pEffect);

}

void CBronya_Ult_Wind::PostRender(LPD3DXEFFECT pEffect)
{
	m_spMesh->PostRender(m_spGraphics, pEffect);

}

void CBronya_Ult_Wind::OnDestroy()
{
	__super::OnDestroy();

}

void CBronya_Ult_Wind::OnEnable()
{
	__super::OnEnable();

}

void CBronya_Ult_Wind::OnDisable()
{
	__super::OnDisable();

}

void CBronya_Ult_Wind::SetBasicName()
{
	m_name = m_objectKey + std::to_wstring(m_s_uniqueID++);

}
