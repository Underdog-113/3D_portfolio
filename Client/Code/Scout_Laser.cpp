#include "stdafx.h"
#include "..\Header\Scout_Laser.h"

_uint CScout_Laser::m_s_uniqueID = 0;

CScout_Laser::CScout_Laser()
{
}


CScout_Laser::~CScout_Laser()
{
}

SP(CScout_Laser) CScout_Laser::Create(_bool isStatic, Engine::CScene * pScene)
{
	SP(CScout_Laser) spInstance(new CScout_Laser, Engine::SmartDeleter<CScout_Laser>);
	spInstance->SetIsStatic(isStatic);
	spInstance->SetScene(pScene);
	spInstance->Awake();

	return spInstance;
}

SP(Engine::CObject) CScout_Laser::MakeClone()
{
	SP(CScout_Laser) spClone(new CScout_Laser, Engine::SmartDeleter<CScout_Laser>);
	__super::InitClone(spClone);

	spClone->m_spTransform = spClone->GetComponent<Engine::CTransformC>();
	spClone->m_spMesh = spClone->GetComponent<Engine::CMeshC>();
	spClone->m_spGraphics = spClone->GetComponent<Engine::CGraphicsC>();
	spClone->m_spTexture = spClone->GetComponent<Engine::CTextureC>();
	spClone->m_spShader = spClone->GetComponent<Engine::CShaderC>();

	return spClone;
}

void CScout_Laser::Awake()
{
	__super::Awake();
	m_spTransform->SetSizeX(1.f);
	m_spTransform->SetSizeY(1.f);
	m_spTransform->SetSizeZ(1.f);
	m_spMesh->SetMeshData(L"Scout_Laser");
	m_spTexture->AddTexture(L"BallColor");
	m_spTexture->AddTexture(L"BallColor");
	m_spShader->AddShader((_int)EShaderID::AlphaMaskGlowShader);
	m_spGraphics->SetRenderID((_int)Engine::ERenderID::NonAlpha);
}

void CScout_Laser::Start()
{
	__super::Start();
	m_fAlpha = 1.f;

}

void CScout_Laser::FixedUpdate()
{
	__super::FixedUpdate();

}

void CScout_Laser::Update()
{
	__super::Update();

	if (m_spTransform->GetSize().z <= 0)
	{
		this->SetDeleteThis(true);
	}
	_float size = -2.f * GET_DT;
	m_spTransform->AddSize(_float3(size, size, size));
}

void CScout_Laser::LateUpdate()
{
	__super::LateUpdate();

}

void CScout_Laser::PreRender(LPD3DXEFFECT pEffect)
{
	m_spMesh->PreRender(m_spGraphics, pEffect);
	pEffect->SetFloat("gAlpha", m_fAlpha);
	pEffect->SetBool("g_bAlphaCtrl", false);
	pEffect->CommitChanges();
}

void CScout_Laser::Render(LPD3DXEFFECT pEffect)
{
	m_spMesh->Render(m_spGraphics, pEffect);
}

void CScout_Laser::PostRender(LPD3DXEFFECT pEffect)
{
	m_spMesh->PostRender(m_spGraphics, pEffect);
}

void CScout_Laser::OnDestroy()
{
	__super::OnDestroy();
}

void CScout_Laser::OnEnable()
{
	__super::OnEnable();

}

void CScout_Laser::OnDisable()
{
	__super::OnDisable();

}

void CScout_Laser::SetBasicName()
{
	m_name = m_objectKey + std::to_wstring(m_s_uniqueID++);

}
