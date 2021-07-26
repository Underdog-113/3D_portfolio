#include "stdafx.h"
#include "..\Header\Bronya_Impact.h"

_uint CBronya_Impact::m_s_uniqueID = 0;


CBronya_Impact::CBronya_Impact()
{
}


CBronya_Impact::~CBronya_Impact()
{
}

SP(CBronya_Impact) CBronya_Impact::Create(_bool isStatic, Engine::CScene * pScene)
{
	SP(CBronya_Impact) spInstance(new CBronya_Impact, Engine::SmartDeleter<CBronya_Impact>);
	spInstance->SetIsStatic(isStatic);
	spInstance->SetScene(pScene);
	spInstance->Awake();

	return spInstance;
}

SP(Engine::CObject) CBronya_Impact::MakeClone()
{
	SP(CBronya_Impact) spClone(new CBronya_Impact, Engine::SmartDeleter<CBronya_Impact>);
	__super::InitClone(spClone);

	spClone->m_spTransform = spClone->GetComponent<Engine::CTransformC>();
	spClone->m_spTransform->SetSize(0.2f, 0.2f, 0.2f);
	spClone->m_spMesh = spClone->GetComponent<Engine::CMeshC>();
	spClone->m_spGraphics = spClone->GetComponent<Engine::CGraphicsC>();
	spClone->m_spShader = spClone->GetComponent<Engine::CShaderC>();
	spClone->m_spTexture = spClone->GetComponent<Engine::CTextureC>();

	return spClone;
}

void CBronya_Impact::Awake()
{
	__super::Awake();
	m_spMesh->SetMeshData(L"Bronya_Impact");
	m_spMesh->SetIsEffectMesh(true);
	m_spGraphics->SetRenderID((_int)Engine::ERenderID::Effect);
	m_spTexture->AddTexture(L"Wave01");
	m_spTexture->AddTexture(L"Wave01");
	m_spTexture->AddTexture(L"Impact_Red");
	m_spShader->AddShader((_int)EShaderID::DissolveShader);
}

void CBronya_Impact::Start()
{
	__super::Start();

	_float3 size = { 16.f, 10.f, 16.f };

	SP(Engine::CObject) spImpactRing = Engine::GET_CUR_SCENE->GetObjectFactory()->AddClone(L"Bronya_Impact_Ring", true);
	spImpactRing->GetTransform()->SetSize(size);
	spImpactRing->GetTransform()->SetPosition(this->GetTransform()->GetPosition());
	spImpactRing->GetTransform()->SetPositionY(this->GetTransform()->GetPosition().y - 0.45f);

	SP(Engine::CObject) spImpactTriRing = Engine::GET_CUR_SCENE->GetObjectFactory()->AddClone(L"Bronya_Impact_TripleRing", true);
	spImpactTriRing->GetTransform()->SetSize(size);
	spImpactTriRing->GetTransform()->SetPosition(this->GetTransform()->GetPosition());
	spImpactTriRing->GetTransform()->SetPositionY(this->GetTransform()->GetPosition().y - 0.45f);

	m_fAlpha = 1.f;
}

void CBronya_Impact::FixedUpdate()
{
	__super::FixedUpdate();

}

void CBronya_Impact::Update()
{
	__super::Update();

	if (m_fAlpha <= 0.f)
	{
		this->SetDeleteThis(true);
	}

	m_fAlpha -= 3.f * GET_DT;
}

void CBronya_Impact::LateUpdate()
{
	__super::LateUpdate();

}

void CBronya_Impact::PreRender(LPD3DXEFFECT pEffect)
{
	m_spMesh->PreRender(m_spGraphics, pEffect);
	pEffect->SetFloat("gAlpha", m_fAlpha);
	pEffect->SetBool("g_zWriteEnabled", true);
	pEffect->CommitChanges();
}

void CBronya_Impact::Render(LPD3DXEFFECT pEffect)
{
	m_spMesh->Render(m_spGraphics, pEffect);

}

void CBronya_Impact::PostRender(LPD3DXEFFECT pEffect)
{
	m_spMesh->PostRender(m_spGraphics, pEffect);

}

void CBronya_Impact::OnDestroy()
{
	__super::OnDestroy();

}

void CBronya_Impact::OnEnable()
{
	__super::OnEnable();

}

void CBronya_Impact::OnDisable()
{
	__super::OnDisable();

}

void CBronya_Impact::SetBasicName()
{
	m_name = m_objectKey + std::to_wstring(m_s_uniqueID++);

}
