#include "stdafx.h"
#include "..\Header\SpiderImpact.h"

_uint CSpiderImpact::m_s_uniqueID = 0;

CSpiderImpact::CSpiderImpact()
{
}


CSpiderImpact::~CSpiderImpact()
{
}

SP(CSpiderImpact) CSpiderImpact::Create(_bool isStatic, Engine::CScene * pScene)
{
	SP(CSpiderImpact) spInstance(new CSpiderImpact, Engine::SmartDeleter<CSpiderImpact>);
	spInstance->SetIsStatic(isStatic);
	spInstance->SetScene(pScene);
	spInstance->Awake();

	return spInstance;
}

SP(Engine::CObject) CSpiderImpact::MakeClone()
{
	SP(CSpiderImpact) spClone(new CSpiderImpact, Engine::SmartDeleter<CSpiderImpact>);
	__super::InitClone(spClone);

	spClone->m_spTransform = spClone->GetComponent<Engine::CTransformC>();
	spClone->m_spMesh = spClone->GetComponent<Engine::CMeshC>();
	spClone->m_spGraphics = spClone->GetComponent<Engine::CGraphicsC>();
	spClone->m_spShader = spClone->GetComponent<Engine::CShaderC>();
	spClone->m_spTexture = spClone->GetComponent<Engine::CTextureC>();

	return spClone;
}

void CSpiderImpact::Awake()
{
	__super::Awake();
	_float _size = 0.2f;
	m_spTransform->SetSize(_float3(_size, 0.3f, _size));
	m_spMesh->SetMeshData(L"Bronya_Impact");
	m_spMesh->SetIsEffectMesh(true);
	m_spGraphics->SetRenderID((_int)Engine::ERenderID::AlphaBlend);
	m_spTexture->AddTexture(L"Grenade_Explosion");
	m_spTexture->AddTexture(L"Wave01");
	m_spTexture->AddTexture(L"Spider_Explosion_1");
	m_spShader->AddShader((_int)EShaderID::DissolveShader);

}

void CSpiderImpact::Start()
{
	__super::Start();



	m_fAlpha = 0.5f;
}

void CSpiderImpact::FixedUpdate()
{
	__super::FixedUpdate();

}

void CSpiderImpact::Update()
{
	__super::Update();

	if (m_fAlpha <= 0.f)
	{
		this->SetDeleteThis(true);
	}

	m_fAlpha -= 0.5f * GET_DT;
}

void CSpiderImpact::LateUpdate()
{
	__super::LateUpdate();
}

void CSpiderImpact::PreRender(LPD3DXEFFECT pEffect)
{
	m_spMesh->PreRender(m_spGraphics, pEffect);
	pEffect->SetFloat("gAlpha", m_fAlpha);
	pEffect->SetBool("g_zWriteEnabled", false);
	pEffect->CommitChanges();
}

void CSpiderImpact::Render(LPD3DXEFFECT pEffect)
{
	m_spMesh->Render(m_spGraphics, pEffect);

}

void CSpiderImpact::PostRender(LPD3DXEFFECT pEffect)
{
	m_spMesh->PostRender(m_spGraphics, pEffect);

}

void CSpiderImpact::OnDestroy()
{
	__super::OnDestroy();

}

void CSpiderImpact::OnEnable()
{
	__super::OnEnable();

}

void CSpiderImpact::OnDisable()
{
	__super::OnDisable();

}

void CSpiderImpact::SetBasicName()
{
	m_name = m_objectKey + std::to_wstring(m_s_uniqueID++);

}
