#include "stdafx.h"
#include "..\Header\CloudObject.h"

_uint CCloudObject::m_s_uniqueID = 0;

CCloudObject::CCloudObject()
{
}


CCloudObject::~CCloudObject()
{
	OnDestroy();

}

SP(CCloudObject) CCloudObject::Create(_bool isStatic, Engine::CScene * pScene)
{
	SP(CCloudObject) spInstance(new CCloudObject, Engine::SmartDeleter<CCloudObject>);
	spInstance->SetIsStatic(isStatic);
	spInstance->SetScene(pScene);
	spInstance->Awake();

	return spInstance;
}

SP(Engine::CObject) CCloudObject::MakeClone(void)
{
	SP(CCloudObject) spClone(new CCloudObject, Engine::SmartDeleter<CCloudObject>);
	__super::InitClone(spClone);


	spClone->m_spTransform = spClone->GetComponent<Engine::CTransformC>();
	spClone->m_spMesh = spClone->GetComponent<Engine::CMeshC>();
	spClone->m_spGraphics = spClone->GetComponent<Engine::CGraphicsC>();
	spClone->m_spTexture = spClone->GetComponent<Engine::CTextureC>();
	spClone->m_spShader = spClone->GetComponent<Engine::CShaderC>();

	return spClone;
}

void CCloudObject::Awake(void)
{
	__super::Awake();

	m_addExtra = true;

	m_spMesh = AddComponent<Engine::CMeshC>();
	m_spMesh->SetMeshData(L"Cloud");
	m_spMesh->SetIsEffectMesh(true);
	m_spGraphics = AddComponent<Engine::CGraphicsC>();
	m_spShader = AddComponent<Engine::CShaderC>();
	m_spTexture = AddComponent<Engine::CTextureC>();
	m_spTexture->AddTexture(L"Background_Cloud_01");
	m_spTexture->AddTexture(L"Background_Cloud_01");
	m_spShader->AddShader((_int)EShaderID::AlphaMaskShader);
}

void CCloudObject::Start(void)
{
	__super::Start();
	m_spGraphics->SetRenderID((_int)Engine::ERenderID::AlphaBlend);
	m_fTempPosZ = m_spTransform->GetPosition().z;
	m_fAlpha = 0.f;
}

void CCloudObject::FixedUpdate(void)
{
	__super::FixedUpdate();

}

void CCloudObject::Update(void)
{
	__super::Update();

	if (m_spTransform->GetPosition().z > -1.f)
	{
		m_spTransform->AddPositionZ(-2.f * GET_DT);
		m_fAlpha += 0.01f * GET_DT;
	}

	if (m_spTransform->GetPosition().z <= -1.f)
	{
		m_spTransform->SetPositionZ(m_fTempPosZ);
		m_fAlpha = 0.f;
	}
}

void CCloudObject::LateUpdate(void)
{
	__super::LateUpdate();

}

void CCloudObject::PreRender(LPD3DXEFFECT pEffect)
{
	m_spMesh->PreRender(m_spGraphics, pEffect);

	pEffect->SetFloat("gAlpha", m_fAlpha);
	pEffect->SetBool("g_zWriteEnabled", false);
	pEffect->SetBool("g_AlphaTestEnabled", true);
	pEffect->CommitChanges();	
}

void CCloudObject::Render(LPD3DXEFFECT pEffect)
{
	m_spMesh->Render(m_spGraphics, pEffect);

}

void CCloudObject::PostRender(LPD3DXEFFECT pEffect)
{
	m_spMesh->PostRender(m_spGraphics, pEffect);

}

void CCloudObject::OnDestroy(void)
{
	__super::OnDestroy();

}

void CCloudObject::OnEnable(void)
{
	__super::OnEnable();

}

void CCloudObject::OnDisable(void)
{
	__super::OnDisable();

}

void CCloudObject::SetBasicName(void)
{
	m_name = m_objectKey + std::to_wstring(m_s_uniqueID++);

}
