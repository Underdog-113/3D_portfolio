#include "stdafx.h"
#include "..\Header\Robot_Impact.h"

_uint CRobot_Impact::m_s_uniqueID = 0;

CRobot_Impact::CRobot_Impact()
{
}


CRobot_Impact::~CRobot_Impact()
{
}

SP(CRobot_Impact) CRobot_Impact::Create(_bool isStatic, Engine::CScene * pScene)
{
	SP(CRobot_Impact) spInstance(new CRobot_Impact, Engine::SmartDeleter<CRobot_Impact>);
	spInstance->SetIsStatic(isStatic);
	spInstance->SetScene(pScene);
	spInstance->Awake();

	return spInstance;
}

SP(Engine::CObject) CRobot_Impact::MakeClone()
{
	SP(CRobot_Impact) spClone(new CRobot_Impact, Engine::SmartDeleter<CRobot_Impact>);
	__super::InitClone(spClone);

	spClone->m_spTransform = spClone->GetComponent<Engine::CTransformC>();
	spClone->m_spTransform->SetSize(0.2f, 0.2f, 0.2f);
	spClone->m_spMesh = spClone->GetComponent<Engine::CMeshC>();
	spClone->m_spGraphics = spClone->GetComponent<Engine::CGraphicsC>();
	spClone->m_spShader = spClone->GetComponent<Engine::CShaderC>();
	spClone->m_spTexture = spClone->GetComponent<Engine::CTextureC>();

	return spClone;
}

void CRobot_Impact::Awake()
{
	__super::Awake();
	m_spMesh->SetMeshData(L"Bronya_Impact");
	m_spMesh->SetIsEffectMesh(true);
	m_spGraphics->SetRenderID((_int)Engine::ERenderID::AlphaBlend);
	m_spTexture->AddTexture(L"Wave01");
	m_spTexture->AddTexture(L"Wave01");
	m_spTexture->AddTexture(L"Impact_Red");
	m_spShader->AddShader((_int)EShaderID::DissolveShader);
}

void CRobot_Impact::Start()
{
	__super::Start();

	_float3 size = { 8.f, 2.f, 8.f };

	SP(Engine::CObject) spImpactSmoke = Engine::GET_CUR_SCENE->ADD_CLONE(L"Robot_Impact_Smoke", true);
	spImpactSmoke->GetTransform()->SetPosition(this->GetTransform()->GetPosition());
	spImpactSmoke->GetTransform()->SetPositionY(this->GetTransform()->GetPosition().y - 0.4f);
	spImpactSmoke->GetTransform()->SetSize(size);

	m_fAlpha = 1.f;
}

void CRobot_Impact::FixedUpdate()
{
	__super::FixedUpdate();

}

void CRobot_Impact::Update()
{
	__super::Update();

	if (m_fAlpha <= 0.f)
	{
		this->SetDeleteThis(true);
	}

	m_fAlpha -= 0.5f * GET_DT;


}

void CRobot_Impact::LateUpdate()
{
	__super::LateUpdate();	
}

void CRobot_Impact::PreRender(LPD3DXEFFECT pEffect)
{
	m_spMesh->PreRender(m_spGraphics, pEffect);
	pEffect->SetFloat("gAlpha", m_fAlpha);
	pEffect->SetBool("g_zWriteEnabled", true);
	pEffect->CommitChanges();

}

void CRobot_Impact::Render(LPD3DXEFFECT pEffect)
{
	m_spMesh->Render(m_spGraphics, pEffect);

}

void CRobot_Impact::PostRender(LPD3DXEFFECT pEffect)
{
	m_spMesh->PostRender(m_spGraphics, pEffect);
}

void CRobot_Impact::OnDestroy()
{
	__super::OnDestroy();

}

void CRobot_Impact::OnEnable()
{
	__super::OnEnable();

}

void CRobot_Impact::OnDisable()
{
	__super::OnDisable();

}

void CRobot_Impact::SetBasicName()
{
	m_name = m_objectKey + std::to_wstring(m_s_uniqueID++);
}