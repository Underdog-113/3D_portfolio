#include "stdafx.h"
#include "..\Header\Bronya_Impact_Ring.h"

_uint CBronya_Impact_Ring::m_s_uniqueID = 0;


CBronya_Impact_Ring::CBronya_Impact_Ring()
{
}


CBronya_Impact_Ring::~CBronya_Impact_Ring()
{
}

SP(CBronya_Impact_Ring) CBronya_Impact_Ring::Create(_bool isStatic, Engine::CScene * pScene)
{
	SP(CBronya_Impact_Ring) spInstance(new CBronya_Impact_Ring, Engine::SmartDeleter<CBronya_Impact_Ring>);
	spInstance->SetIsStatic(isStatic);
	spInstance->SetScene(pScene);
	spInstance->Awake();

	return spInstance;
}

SP(Engine::CObject) CBronya_Impact_Ring::MakeClone()
{
	SP(CBronya_Impact_Ring) spClone(new CBronya_Impact_Ring, Engine::SmartDeleter<CBronya_Impact_Ring>);
	__super::InitClone(spClone);

	spClone->m_spTransform = spClone->GetComponent<Engine::CTransformC>();
	spClone->m_spMesh = spClone->GetComponent<Engine::CMeshC>();
	spClone->m_spGraphics = spClone->GetComponent<Engine::CGraphicsC>();
	spClone->m_spShader = spClone->GetComponent<Engine::CShaderC>();
	spClone->m_spTexture = spClone->GetComponent<Engine::CTextureC>();

	return spClone;
}

void CBronya_Impact_Ring::Awake()
{
	__super::Awake();
	m_spMesh->SetMeshData(L"Bronya_Impact_ring");
	m_spMesh->SetIsEffectMesh(true);
	m_spGraphics->SetRenderID((_int)Engine::ERenderID::Effect);
	m_spTexture->AddTexture(L"Impact_Red");
	m_spTexture->AddTexture(L"Eff_Noise_08");
	m_spTexture->AddTexture(L"Impact_Red");
	m_spShader->AddShader((_int)EShaderID::DissolveShader);
}

void CBronya_Impact_Ring::Start()
{
	__super::Start();
	m_fAlpha = 1.f;
}

void CBronya_Impact_Ring::FixedUpdate()
{
	__super::FixedUpdate();

}

void CBronya_Impact_Ring::Update()
{
	__super::Update();

	if (m_fAlpha <= 0.f)
	{
		this->SetDeleteThis(true);
	}

	m_fAlpha -= 1.5f * GET_DT;
}

void CBronya_Impact_Ring::LateUpdate()
{
	__super::LateUpdate();

}

void CBronya_Impact_Ring::PreRender(LPD3DXEFFECT pEffect)
{
	m_spMesh->PreRender(m_spGraphics, pEffect);
	pEffect->SetFloat("gAlpha", m_fAlpha);
	pEffect->SetBool("g_zWriteEnabled", false);
	pEffect->CommitChanges();

}

void CBronya_Impact_Ring::Render(LPD3DXEFFECT pEffect)
{
	m_spMesh->Render(m_spGraphics, pEffect);

}

void CBronya_Impact_Ring::PostRender(LPD3DXEFFECT pEffect)
{
	m_spMesh->PostRender(m_spGraphics, pEffect);

}

void CBronya_Impact_Ring::OnDestroy()
{
	__super::OnDestroy();

}

void CBronya_Impact_Ring::OnEnable()
{
	__super::OnEnable();

}

void CBronya_Impact_Ring::OnDisable()
{
	__super::OnDisable();

}

void CBronya_Impact_Ring::SetBasicName()
{
	m_name = m_objectKey + std::to_wstring(m_s_uniqueID++);

}
