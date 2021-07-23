#include "stdafx.h"
#include "Bronya_Ult_Impact.h"

_uint CBronya_Ult_Impact::m_s_uniqueID = 0;

CBronya_Ult_Impact::CBronya_Ult_Impact()
{
}


CBronya_Ult_Impact::~CBronya_Ult_Impact()
{
}

SP(CBronya_Ult_Impact) CBronya_Ult_Impact::Create(_bool isStatic, Engine::CScene * pScene)
{
	SP(CBronya_Ult_Impact) spInstance(new CBronya_Ult_Impact, Engine::SmartDeleter<CBronya_Ult_Impact>);
	spInstance->SetIsStatic(isStatic);
	spInstance->SetScene(pScene);
	spInstance->Awake();

	return spInstance;
}

SP(Engine::CObject) CBronya_Ult_Impact::MakeClone()
{
	SP(CBronya_Ult_Impact) spClone(new CBronya_Ult_Impact, Engine::SmartDeleter<CBronya_Ult_Impact>);
	__super::InitClone(spClone);

	spClone->m_spTransform = spClone->GetComponent<Engine::CTransformC>();
	spClone->m_spTransform->SetSize(1.f, 1.f, 1.f);
	spClone->m_spMesh = spClone->GetComponent<Engine::CMeshC>();
	spClone->m_spGraphics = spClone->GetComponent<Engine::CGraphicsC>();
	spClone->m_spShader = spClone->GetComponent<Engine::CShaderC>();
	spClone->m_spTexture = spClone->GetComponent<Engine::CTextureC>();

	return spClone;
}

void CBronya_Ult_Impact::Awake()
{
	__super::Awake();
	m_spMesh->SetMeshData(L"Bronya_Impact");
	m_spMesh->SetIsEffectMesh(true);
	m_spGraphics->SetRenderID((_int)Engine::ERenderID::AlphaBlend);
	m_spTexture->AddTexture(L"Wave01");
	m_spTexture->AddTexture(L"Wave01");
	m_spTexture->AddTexture(L"Grenade_Explosion");
	m_spShader->AddShader((_int)EShaderID::DissolveShader);
}

void CBronya_Ult_Impact::Start()
{
	__super::Start();

	m_fAlpha = 1.f;
}

void CBronya_Ult_Impact::FixedUpdate()
{
	__super::FixedUpdate();

}

void CBronya_Ult_Impact::Update()
{
	__super::Update();

	if (m_fAlpha <= 0.f)
	{
		this->SetDeleteThis(true);
	}

	m_fAlpha -= 3.f * GET_DT;
}

void CBronya_Ult_Impact::LateUpdate()
{
	__super::LateUpdate();

}

void CBronya_Ult_Impact::PreRender(LPD3DXEFFECT pEffect)
{
	m_spMesh->PreRender(m_spGraphics, pEffect);
	pEffect->SetFloat("gAlpha", m_fAlpha);
	pEffect->SetBool("g_zWriteEnabled", false);
	pEffect->CommitChanges();
}

void CBronya_Ult_Impact::Render(LPD3DXEFFECT pEffect)
{
	m_spMesh->Render(m_spGraphics, pEffect);

}

void CBronya_Ult_Impact::PostRender(LPD3DXEFFECT pEffect)
{
	m_spMesh->PostRender(m_spGraphics, pEffect);

}

void CBronya_Ult_Impact::OnDestroy()
{
	__super::OnDestroy();

}

void CBronya_Ult_Impact::OnEnable()
{
	__super::OnEnable();

}

void CBronya_Ult_Impact::OnDisable()
{
	__super::OnDisable();

}

void CBronya_Ult_Impact::SetBasicName()
{
	m_name = m_objectKey + std::to_wstring(m_s_uniqueID++);

}
