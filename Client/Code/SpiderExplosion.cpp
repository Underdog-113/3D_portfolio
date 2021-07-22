#include "stdafx.h"
#include "..\Header\SpiderExplosion.h"

_uint CSpiderExplosion::m_s_uniqueID = 0;

CSpiderExplosion::CSpiderExplosion()
{
}


CSpiderExplosion::~CSpiderExplosion()
{
}

SP(CSpiderExplosion) CSpiderExplosion::Create(_bool isStatic, Engine::CScene * pScene)
{
	SP(CSpiderExplosion) spInstance(new CSpiderExplosion, Engine::SmartDeleter<CSpiderExplosion>);
	spInstance->SetIsStatic(isStatic);
	spInstance->SetScene(pScene);
	spInstance->Awake();

	return spInstance;
}

SP(Engine::CObject) CSpiderExplosion::MakeClone(void)
{
	SP(CSpiderExplosion) spClone(new CSpiderExplosion, Engine::SmartDeleter<CSpiderExplosion>);
	__super::InitClone(spClone);

	spClone->m_spTransform = spClone->GetComponent<Engine::CTransformC>();
	spClone->m_spMesh = spClone->GetComponent<Engine::CMeshC>();
	spClone->m_spGraphics = spClone->GetComponent<Engine::CGraphicsC>();
	spClone->m_spTexture = spClone->GetComponent<Engine::CTextureC>();
	spClone->m_spShader = spClone->GetComponent<Engine::CShaderC>();
	return spClone;
}

void CSpiderExplosion::Awake(void)
{
	__super::Awake();
	_float _size = 0.5f;
	m_spTransform->SetSize(_float3(_size, _size, _size));
	m_spTransform->AddRotationX(D3DXToRadian(180));
	m_spMesh->SetMeshData(L"Ganesha_Dome");
	m_spMesh->SetIsEffectMesh(true);
	m_spGraphics->SetRenderID((_int)Engine::ERenderID::Effect);
	m_spTexture->AddTexture(L"Grenade_Explosion");
	m_spTexture->AddTexture(L"Wave01");
	m_spTexture->AddTexture(L"Spider_Explosion_1");
	m_spShader->AddShader((_int)EShaderID::DissolveShader);
}

void CSpiderExplosion::Start(void)
{
	__super::Start();


	m_fSize = 0.f;
	m_fAlpha = 0.7f;
}

void CSpiderExplosion::FixedUpdate(void)
{
	__super::FixedUpdate();
}

void CSpiderExplosion::Update(void)
{
	__super::Update();

	if (m_fAlpha <= 0.f)
	{
		this->SetDeleteThis(true);
	}

	m_fSize = 1.2f * GET_DT;

	m_spTransform->AddSize(_float3(m_fSize, m_fSize, m_fSize));

	m_fAlpha -= 0.6f * GET_DT;

}

void CSpiderExplosion::LateUpdate(void)
{
	__super::LateUpdate();


}

void CSpiderExplosion::PreRender(LPD3DXEFFECT pEffect)
{
	m_spMesh->PreRender(m_spGraphics, pEffect);
	pEffect->SetFloat("gAlpha", m_fAlpha);
	pEffect->SetBool("gTrailCheck", false);
	pEffect->SetBool("g_zWriteEnabled", true);
	pEffect->CommitChanges();
}

void CSpiderExplosion::Render(LPD3DXEFFECT pEffect)
{
	m_spMesh->Render(m_spGraphics, pEffect);


}

void CSpiderExplosion::PostRender(LPD3DXEFFECT pEffect)
{
	m_spMesh->PostRender(m_spGraphics, pEffect);

}

void CSpiderExplosion::OnDestroy(void)
{
	__super::OnDestroy();

}

void CSpiderExplosion::OnEnable(void)
{
	__super::OnEnable();

}

void CSpiderExplosion::OnDisable(void)
{
	__super::OnDisable();

}

void CSpiderExplosion::SetBasicName(void)
{
	m_name = m_objectKey + std::to_wstring(m_s_uniqueID++);

}