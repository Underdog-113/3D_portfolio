#include "stdafx.h"
#include "..\Header\Portal_Blue.h"

_uint CPortal_Blue::m_s_uniqueID = 0;

CPortal_Blue::CPortal_Blue()
{
}


CPortal_Blue::~CPortal_Blue()
{
	OnDestroy();
}

SP(CPortal_Blue) CPortal_Blue::Create(_bool isStatic, Engine::CScene * pScene)
{
	SP(CPortal_Blue) spInstance(new CPortal_Blue, Engine::SmartDeleter<CPortal_Blue>);
	spInstance->SetIsStatic(isStatic);
	spInstance->SetScene(pScene);
	spInstance->Awake();

	return spInstance;
}

SP(Engine::CObject) CPortal_Blue::MakeClone()
{
	SP(CPortal_Blue) spClone(new CPortal_Blue, Engine::SmartDeleter<CPortal_Blue>);
	__super::InitClone(spClone);

	spClone->m_spTransform = spClone->GetComponent<Engine::CTransformC>();
	spClone->m_spMesh = spClone->GetComponent<Engine::CMeshC>();
	spClone->m_spGraphics = spClone->GetComponent<Engine::CGraphicsC>();
	spClone->m_spShader = spClone->GetComponent<Engine::CShaderC>();
	spClone->m_spTexture = spClone->GetComponent<Engine::CTextureC>();

	return spClone;
}

void CPortal_Blue::Awake()
{
	__super::Awake();
	m_spMesh->SetMeshData(L"Portal_Cylinder");
	m_spMesh->SetIsEffectMesh(true);
	m_spGraphics->SetRenderID((_int)Engine::ERenderID::AlphaBlend);
	m_spTexture->AddTexture(L"BlueprintBG");
	m_spTexture->AddTexture(L"AttackHint_Circle_04");
	m_spShader->AddShader((_int)EShaderID::AlphaMaskShader);
	_float _size = 4.f;
	m_spTransform->SetSize(_float3(_size, _size + 2.f, _size));
}

void CPortal_Blue::Start()
{
	__super::Start();

	m_fAlpha = 1.f;
	m_fUVSpeed = 0.f;
	m_fTime = 0.f;
}

void CPortal_Blue::FixedUpdate()
{
	__super::FixedUpdate();

}

void CPortal_Blue::Update()
{
	__super::Update();

	m_fTime += GET_DT;

	if (m_fTime >= 0.1f)
	{
		_float fX = -0.05f;
		for (_int i = 0; i < 3; ++i)
		{
			m_spBeam = Engine::GET_CUR_SCENE->GetObjectFactory()->AddClone(L"Portal_Beam", true, (_uint)Engine::ELayerID::Effect);
			m_spBeam->GetTransform()->SetPositionX(m_spTransform->GetPosition().x + rand() % 2 * 0.05f + fX);
			m_spBeam->GetTransform()->SetPositionY(m_spTransform->GetPosition().y);
			m_spBeam->GetTransform()->SetPositionZ(m_spTransform->GetPosition().z + rand() % 2 * 0.05f);
			fX += 0.02f;
		}
		m_fTime = 0.f;
	}


	m_fUVSpeed += 1.3f * GET_DT;
}

void CPortal_Blue::LateUpdate()
{
	__super::LateUpdate();

}

void CPortal_Blue::PreRender(LPD3DXEFFECT pEffect)
{
	m_spMesh->PreRender(m_spGraphics, pEffect);
	pEffect->SetFloat("gAlpha", m_fAlpha);
	pEffect->SetFloat("gSpeed", m_fUVSpeed);
	pEffect->SetBool("gPlayingAnim", true);
	pEffect->SetBool("g_zWriteEnabled", false);
	pEffect->CommitChanges();
}

void CPortal_Blue::Render(LPD3DXEFFECT pEffect)
{
	m_spMesh->Render(m_spGraphics, pEffect);

}

void CPortal_Blue::PostRender(LPD3DXEFFECT pEffect)
{
	m_spMesh->PostRender(m_spGraphics, pEffect);

}

void CPortal_Blue::OnDestroy()
{
	__super::OnDestroy();

	if (m_spBeam != nullptr)
		m_spBeam->SetDeleteThis(true);
}

void CPortal_Blue::OnEnable()
{
	__super::OnEnable();

}

void CPortal_Blue::OnDisable()
{
	__super::OnDisable();

}

void CPortal_Blue::SetBasicName()
{
	m_name = m_objectKey + std::to_wstring(m_s_uniqueID++);

}
