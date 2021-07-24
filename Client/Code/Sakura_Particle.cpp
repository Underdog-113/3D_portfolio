#include "stdafx.h"
#include "..\Header\Sakura_Particle.h"

_uint CSakura_Particle::m_s_uniqueID = 0;

CSakura_Particle::CSakura_Particle()
{
}


CSakura_Particle::~CSakura_Particle()
{
}

SP(CSakura_Particle) CSakura_Particle::Create(_bool isStatic, Engine::CScene * pScene)
{
	SP(CSakura_Particle) spInstance(new CSakura_Particle, Engine::SmartDeleter<CSakura_Particle>);
	spInstance->SetIsStatic(isStatic);
	spInstance->SetScene(pScene);
	spInstance->Awake();

	return spInstance;
}

SP(Engine::CObject) CSakura_Particle::MakeClone()
{
	SP(CSakura_Particle) spClone(new CSakura_Particle, Engine::SmartDeleter<CSakura_Particle>);
	__super::InitClone(spClone);
	spClone->m_spTransform = spClone->GetComponent<Engine::CTransformC>();
	spClone->m_spGraphics = spClone->GetComponent<Engine::CGraphicsC>();
	spClone->m_spTexture = spClone->GetComponent<Engine::CTextureC>();
	spClone->m_spRectTex = spClone->GetComponent<Engine::CRectTexC>();
	spClone->m_spShader = spClone->GetComponent<Engine::CShaderC>();
	spClone->m_spCollision = spClone->GetComponent<Engine::CCollisionC>();
	spClone->m_bBillboard = true;

	return spClone;
}

void CSakura_Particle::Awake()
{
	__super::Awake();
	m_spTexture->AddTexture(L"LaserColor");
	m_spTexture->AddTexture(L"Effect_Wave06");
	m_spGraphics->SetRenderID((_int)Engine::ERenderID::NonAlpha);
	m_spShader->AddShader((_int)EShaderID::SoftEffectShader_Glow);
	m_spTransform->SetSize(0.2f, 0.2f, 0.2f);
}

void CSakura_Particle::Start()
{
	__super::Start();
	m_spTransform->AddRotationX(D3DXToRadian(rand() % -180) + 180);
	m_spTransform->AddRotationY(D3DXToRadian(rand() % -180) + 180);
	m_spTransform->AddRotationZ(D3DXToRadian(rand() % -180) + 180);
	m_spTransform->SetPosition(m_spTransform->GetOwner()->GetTransform()->GetPosition());
	m_tmpScale = m_spTransform->GetSize();

	m_fAlphaWidth = 1.f;
	m_fAlphaHeight = 1.f;
	m_TilingX = 0;
	m_TilingY = 0;

	m_maxXIndex = 0;
	m_maxYIndex = 0;
	m_fTIme = 0.f;
}

void CSakura_Particle::FixedUpdate()
{
	__super::FixedUpdate();

}

void CSakura_Particle::Update()
{
	__super::Update();


	if (m_spTransform->GetSize().x <= 0.f || m_spTransform->GetSize().y <= 0.f || m_spTransform->GetSize().z <= 0.f)
	{
		m_spTransform->AddRotationX(D3DXToRadian(rand() % -180) + 180);
		m_spTransform->AddRotationY(D3DXToRadian(rand() % -180) + 180);
		m_spTransform->AddRotationZ(D3DXToRadian(rand() % -180) + 180);
		m_spTransform->SetPosition(m_spTransform->GetOwner()->GetTransform()->GetPosition());
		m_spTransform->SetSize(m_tmpScale);
	}
	m_spTransform->AddSize(-_float3(0.05f,0.05f,0.05f) * GET_DT * 0.05f);
	m_spTransform->AddPosition(-m_spTransform->GetForward() * GET_DT * 5.f);
}

void CSakura_Particle::LateUpdate()
{
	__super::LateUpdate();	
}

void CSakura_Particle::PreRender(LPD3DXEFFECT pEffect)
{
	m_spRectTex->PreRender(m_spGraphics, pEffect);
	pEffect->SetInt("TilingX", m_TilingX);
	pEffect->SetInt("TilingY", m_TilingY);
	pEffect->SetFloat("gWidth", m_fAlphaWidth);
	pEffect->SetFloat("gHeight", m_fAlphaHeight);
	pEffect->SetBool("g_zWriteEnabled", false);
	pEffect->SetFloat("g_fGlow", 0.2f);
	pEffect->CommitChanges();
}

void CSakura_Particle::Render(LPD3DXEFFECT pEffect)
{
	m_spRectTex->Render(m_spGraphics, pEffect);

}

void CSakura_Particle::PostRender(LPD3DXEFFECT pEffect)
{
	m_spRectTex->PostRender(m_spGraphics, pEffect);

}

void CSakura_Particle::OnDestroy()
{
	__super::OnDestroy();

}

void CSakura_Particle::OnEnable()
{
	__super::OnEnable();

}

void CSakura_Particle::OnDisable()
{
	__super::OnDisable();

}

void CSakura_Particle::SetBasicName()
{
	m_name = m_objectKey + std::to_wstring(m_s_uniqueID++);

}
