#include "stdafx.h"
#include "..\Header\MonsterDieParticle.h"

_uint CMonsterDieParticle::m_s_uniqueID = 0;

CMonsterDieParticle::CMonsterDieParticle()
{
}


CMonsterDieParticle::~CMonsterDieParticle()
{
}

SP(CMonsterDieParticle) CMonsterDieParticle::Create(_bool isStatic, Engine::CScene * pScene)
{
	SP(CMonsterDieParticle) spInstance(new CMonsterDieParticle, Engine::SmartDeleter<CMonsterDieParticle>);
	spInstance->SetIsStatic(isStatic);
	spInstance->SetScene(pScene);
	spInstance->Awake();

	return spInstance;
}

SP(Engine::CObject) CMonsterDieParticle::MakeClone()
{
	SP(CMonsterDieParticle) spClone(new CMonsterDieParticle, Engine::SmartDeleter<CMonsterDieParticle>);
	__super::InitClone(spClone);
	spClone->m_spTransform = spClone->GetComponent<Engine::CTransformC>();
	spClone->m_spGraphics = spClone->GetComponent<Engine::CGraphicsC>();
	spClone->m_spTexture = spClone->GetComponent<Engine::CTextureC>();
	spClone->m_spRectTex = spClone->GetComponent<Engine::CRectTexC>();
	spClone->m_spShader = spClone->GetComponent<Engine::CShaderC>();
	spClone->m_bBillboard = true;

	return spClone;
}

void CMonsterDieParticle::Awake()
{
	__super::Awake();
	m_spTexture->AddTexture(L"DieParticle");
	m_spTexture->AddTexture(L"DieParticle");
	m_spGraphics->SetRenderID((_int)Engine::ERenderID::Effect);
	m_spShader->AddShader((_int)EShaderID::SoftEffectShader_Glow);
	m_spTransform->SetSize(0.07f, 0.07f, 0.07f);
}

void CMonsterDieParticle::Start()
{
	__super::Start();

	InitParticle();

	m_fAlphaWidth = 1.f;
	m_fAlphaHeight = 1.f;
	m_TilingX = 0;
	m_TilingY = 0;

	m_maxXIndex = 0;
	m_maxYIndex = 0;
	m_fTIme = 0.f;
}

void CMonsterDieParticle::FixedUpdate()
{
	__super::FixedUpdate();

}

void CMonsterDieParticle::Update()
{
	__super::Update();

	if (m_spTransform->GetSize().x <= 0.f || m_spTransform->GetSize().y <= 0.f || m_spTransform->GetSize().z <= 0.f)
	{
		this->SetDeleteThis(true);
	}

	movement();
}

void CMonsterDieParticle::LateUpdate()
{
	__super::LateUpdate();

}

void CMonsterDieParticle::PreRender(LPD3DXEFFECT pEffect)
{
	m_spRectTex->PreRender(m_spGraphics, pEffect);
	pEffect->SetInt("TilingX", m_TilingX);
	pEffect->SetInt("TilingY", m_TilingY);
	pEffect->SetFloat("gWidth", m_fAlphaWidth);
	pEffect->SetFloat("gHeight", m_fAlphaHeight);
	pEffect->SetBool("g_zWriteEnabled", true);
	pEffect->SetFloat("g_fGlow", 0.2f);
	pEffect->CommitChanges();
}

void CMonsterDieParticle::Render(LPD3DXEFFECT pEffect)
{
	m_spRectTex->Render(m_spGraphics, pEffect);

}

void CMonsterDieParticle::PostRender(LPD3DXEFFECT pEffect)
{
	m_spRectTex->PostRender(m_spGraphics, pEffect);

}

void CMonsterDieParticle::OnDestroy()
{
	__super::OnDestroy();

}

void CMonsterDieParticle::OnEnable()
{
	__super::OnEnable();

}

void CMonsterDieParticle::OnDisable()
{
	__super::OnDisable();

}

void CMonsterDieParticle::SetBasicName()
{
	m_name = m_objectKey + std::to_wstring(m_s_uniqueID++);

}

void CMonsterDieParticle::InitParticle()
{
	_float3 InitRot = _float3((rand() % -180) + 180.f, (rand() % -180) + 180.f, (rand() % -180) + 180.f);

	m_spTransform->AddRotation(InitRot);
	m_spTransform->SetPosition(m_spTransform->GetOwner()->GetTransform()->GetPosition());
	m_tmpScale = m_spTransform->GetSize();
}

void CMonsterDieParticle::movement()
{
	m_spTransform->AddSize(-_float3(0.3f, 0.3f, 0.3f) * GET_DT * 0.2f);
	m_spTransform->AddPosition(m_spTransform->GetForward() * GET_DT * 2.5f);
}
