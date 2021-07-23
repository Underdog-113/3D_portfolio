#include "stdafx.h"
#include "..\Header\SpiderExplosion_Base.h"

_uint CSpiderExplosion_Base::m_s_uniqueID = 0;

CSpiderExplosion_Base::CSpiderExplosion_Base()
{
}


CSpiderExplosion_Base::~CSpiderExplosion_Base()
{
}

SP(CSpiderExplosion_Base) CSpiderExplosion_Base::Create(_bool isStatic, Engine::CScene * pScene)
{
	SP(CSpiderExplosion_Base) spInstance(new CSpiderExplosion_Base, Engine::SmartDeleter<CSpiderExplosion_Base>);
	spInstance->SetIsStatic(isStatic);
	spInstance->SetScene(pScene);
	spInstance->Awake();

	return spInstance;
}

SP(Engine::CObject) CSpiderExplosion_Base::MakeClone(void)
{
	SP(CSpiderExplosion_Base) spClone(new CSpiderExplosion_Base, Engine::SmartDeleter<CSpiderExplosion_Base>);
	__super::InitClone(spClone);

	spClone->m_spTransform = spClone->GetComponent<Engine::CTransformC>();
	spClone->m_spMesh = spClone->GetComponent<Engine::CMeshC>();
	spClone->m_spGraphics = spClone->GetComponent<Engine::CGraphicsC>();
	spClone->m_spTexture = spClone->GetComponent<Engine::CTextureC>();
	spClone->m_spShader = spClone->GetComponent<Engine::CShaderC>();
	return spClone;
}

void CSpiderExplosion_Base::Awake(void)
{
	__super::Awake();
	_float _size = 0.5f;
	m_spTransform->SetSize(_float3(_size, _size, _size));
	m_spTransform->AddRotationX(D3DXToRadian(180));
	m_spMesh->SetMeshData(L"Ganesha_Dome");
	m_spMesh->SetIsEffectMesh(true);
	m_spGraphics->SetRenderID((_int)Engine::ERenderID::Effect);
	m_spTexture->AddTexture(L"Grenade_Explosion");
	m_spTexture->AddTexture(L"noise_rough");
	m_spTexture->AddTexture(L"Spider_Explosion_1");
	m_spShader->AddShader((_int)EShaderID::DissolveShader_Glow);
}

void CSpiderExplosion_Base::Start(void)
{
	__super::Start();
	SP(Engine::CObject) spObj = Engine::GET_CUR_SCENE->GetObjectFactory()->AddClone(L"SpiderExplosion", true, (_uint)Engine::ELayerID::Effect);
	spObj->GetTransform()->SetPosition(m_spTransform->GetPosition());

	spObj = Engine::GET_CUR_SCENE->GetObjectFactory()->AddClone(L"SpiderImpact", true, (_uint)Engine::ELayerID::Effect);
	spObj->GetTransform()->SetPosition(m_spTransform->GetPosition());
	spObj->GetTransform()->AddPositionY(0.15f);

	m_fSize = 0.f;
	m_fAlpha = 0.6f;
}

void CSpiderExplosion_Base::FixedUpdate(void)
{
	__super::FixedUpdate();

}

void CSpiderExplosion_Base::Update(void)
{
	__super::Update();

	if (m_fAlpha <= 0.f)
	{
		this->SetDeleteThis(true);
	}

	m_fSize = 0.5f * GET_DT;

	m_spTransform->AddSize(_float3(m_fSize, m_fSize, m_fSize));

	m_fAlpha -= 0.5f * GET_DT;
}

void CSpiderExplosion_Base::LateUpdate(void)
{
	__super::LateUpdate();

}

void CSpiderExplosion_Base::PreRender(LPD3DXEFFECT pEffect)
{
	m_spMesh->PreRender(m_spGraphics, pEffect);
	pEffect->SetFloat("gAlpha", m_fAlpha);
	pEffect->SetBool("g_zWriteEnabled", true);
	pEffect->SetBool("gTrailCheck", false);

	pEffect->CommitChanges();
}

void CSpiderExplosion_Base::Render(LPD3DXEFFECT pEffect)
{
	m_spMesh->Render(m_spGraphics, pEffect);

}

void CSpiderExplosion_Base::PostRender(LPD3DXEFFECT pEffect)
{
	m_spMesh->PostRender(m_spGraphics, pEffect);

}

void CSpiderExplosion_Base::OnDestroy(void)
{
	__super::OnDestroy();

}

void CSpiderExplosion_Base::OnEnable(void)
{
	__super::OnEnable();

}

void CSpiderExplosion_Base::OnDisable(void)
{
	__super::OnDisable();

}

void CSpiderExplosion_Base::SetBasicName(void)
{
	m_name = m_objectKey + std::to_wstring(m_s_uniqueID++);

}
