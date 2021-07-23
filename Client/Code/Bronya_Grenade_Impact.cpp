#include "stdafx.h"
#include "..\Header\Bronya_Grenade_Impact.h"

_uint CBronya_Grenade_Impact::m_s_uniqueID = 0;

CBronya_Grenade_Impact::CBronya_Grenade_Impact()
{
}


CBronya_Grenade_Impact::~CBronya_Grenade_Impact()
{
}

SP(CBronya_Grenade_Impact) CBronya_Grenade_Impact::Create(_bool isStatic, Engine::CScene * pScene)
{
	SP(CBronya_Grenade_Impact) spInstance(new CBronya_Grenade_Impact, Engine::SmartDeleter<CBronya_Grenade_Impact>);
	spInstance->SetIsStatic(isStatic);
	spInstance->SetScene(pScene);
	spInstance->Awake();

	return spInstance;
}

SP(Engine::CObject) CBronya_Grenade_Impact::MakeClone()
{
	SP(CBronya_Grenade_Impact) spClone(new CBronya_Grenade_Impact, Engine::SmartDeleter<CBronya_Grenade_Impact>);
	__super::InitClone(spClone);

	spClone->m_spTransform = spClone->GetComponent<Engine::CTransformC>();
	spClone->m_spTransform->SetSize(0.2f, 0.2f, 0.2f);
	spClone->m_spMesh = spClone->GetComponent<Engine::CMeshC>();
	spClone->m_spGraphics = spClone->GetComponent<Engine::CGraphicsC>();
	spClone->m_spShader = spClone->GetComponent<Engine::CShaderC>();
	spClone->m_spTexture = spClone->GetComponent<Engine::CTextureC>();

	return spClone;
}

void CBronya_Grenade_Impact::Awake()
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

void CBronya_Grenade_Impact::Start()
{
	__super::Start();
	m_fAlpha = 1.f;

}

void CBronya_Grenade_Impact::FixedUpdate()
{
	__super::FixedUpdate();

}

void CBronya_Grenade_Impact::Update()
{
	__super::Update();

	if (m_fAlpha <= 0.f)
	{
		this->SetDeleteThis(true);
	}

	m_fAlpha -= 3.f * GET_DT;
}

void CBronya_Grenade_Impact::LateUpdate()
{
	__super::LateUpdate();

}

void CBronya_Grenade_Impact::PreRender(LPD3DXEFFECT pEffect)
{
	m_spMesh->PreRender(m_spGraphics, pEffect);
	pEffect->SetFloat("gAlpha", m_fAlpha);
}

void CBronya_Grenade_Impact::Render(LPD3DXEFFECT pEffect)
{
	m_spMesh->Render(m_spGraphics, pEffect);

}

void CBronya_Grenade_Impact::PostRender(LPD3DXEFFECT pEffect)
{
	m_spMesh->PostRender(m_spGraphics, pEffect);

}

void CBronya_Grenade_Impact::OnDestroy()
{
	__super::OnDestroy();

}

void CBronya_Grenade_Impact::OnEnable()
{
	__super::OnEnable();

}

void CBronya_Grenade_Impact::OnDisable()
{
	__super::OnDisable();

}

void CBronya_Grenade_Impact::SetBasicName()
{
	m_name = m_objectKey + std::to_wstring(m_s_uniqueID++);

}
