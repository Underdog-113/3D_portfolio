#include "EngineStdafx.h"
#include "..\Header\ParticleSystemC.h"
#include "Particle.h"
#include "PSC_Manager.h"

USING(Engine)
CParticleSystemC::CParticleSystemC() :
	m_LifeTime(0.f),
	m_pVertexBuffer(nullptr),
	m_pGraphicDevice(nullptr)
{
}

CParticleSystemC::~CParticleSystemC(void)
{
	OnDestroy();
}

SP(CComponent) CParticleSystemC::MakeClone(CObject * pObject)
{
	SP(CParticleSystemC) spClone(new CParticleSystemC);
	__super::InitClone(spClone, pObject);

	return spClone;
}

void CParticleSystemC::Awake(void)
{
	__super::Awake();
	m_vParticles.reserve(5000);

	

}

void CParticleSystemC::Start(SP(CComponent) spThis)
{
	__super::Start(spThis);


	CPSC_Manager::GetInstance()->AddPSC(std::dynamic_pointer_cast<CParticleSystemC>(spThis));
}

void CParticleSystemC::FixedUpdate(SP(CComponent) spThis)
{
}

void CParticleSystemC::Update(SP(CComponent) spThis)
{
	if (IMKEY_DOWN(KEY_X))
	{

		Engine::BoundingBox boundingBox;
		boundingBox._min = _float3(-10.f, -10.f, -10.f);
		boundingBox._max = _float3(10.f, 10.f, 10.f);
		
		CParticle* pt = new CParticle(&boundingBox, 300);

		pt->Awake();

		m_vParticles.emplace_back(pt);

		InitParticleSetting(GET_DEVICE, L"star");
	}
}

void CParticleSystemC::LateUpdate(SP(CComponent) spThis)
{
	

}

void CParticleSystemC::PreRender(SP(CGraphicsC) spGC)
{	
	for (auto& iter : m_vParticles)
	{
		if (this->GetOwner() != nullptr)
			iter->PreRender(spGC, m_pVertexBuffer, m_pTexture);
	}
}

void CParticleSystemC::PreRender(SP(CGraphicsC) spGC, LPD3DXEFFECT pEffect)
{

}

void CParticleSystemC::Render(SP(CGraphicsC) spGC)
{
	for (auto& iter : m_vParticles)
	{
		if(this->GetOwner() != nullptr)
			iter->Render(spGC, m_pVertexBuffer);
	}
}

void CParticleSystemC::Render(SP(CGraphicsC) spGC, LPD3DXEFFECT pEffect)
{
}

void CParticleSystemC::PostRender(SP(CGraphicsC) spGC)
{
	for (auto& iter : m_vParticles)
	{
		if (this->GetOwner() != nullptr)
			iter->PostRender(spGC);
	}
}

void CParticleSystemC::PostRender(SP(CGraphicsC) spGC, LPD3DXEFFECT pEffect)
{
}

void CParticleSystemC::OnDestroy()
{
	for (auto& particle : m_vParticles)
		particle.reset();

	m_vParticles.clear();

	m_pVertexBuffer->Release();
	m_pVertexBuffer	 = nullptr;
	m_pTexture		 = nullptr;
	m_pGraphicDevice = nullptr;
}

void CParticleSystemC::OnEnable()
{
	__super::OnEnable();
}

void CParticleSystemC::OnDisable()
{
	__super::OnDisable();
}

HRESULT CParticleSystemC::InitParticleSetting(LPDIRECT3DDEVICE9 _Device, std::wstring _texFIleName)
{
	m_pGraphicDevice = _Device;
	DWORD _dwvbSize = 2048;
	HRESULT hr = 0;

	hr = m_pGraphicDevice->CreateVertexBuffer(
		_dwvbSize * sizeof(PARTICLE_DESC),
		D3DUSAGE_DYNAMIC | D3DUSAGE_POINTS | D3DUSAGE_WRITEONLY,
		FVF_Particle,
		D3DPOOL_DEFAULT, // D3DPOOL_MANAGED 와 D3DUSAGE_DYNAMIC는 함께 사용불가.
		&m_pVertexBuffer,
		0);

	if (FAILED(hr))
	{
		MSG_BOX(__FILE__, L"CreateVertexBuffer() - FAILED");
		ABORT;
		return E_FAIL;
	}

	m_pTexture = GET_CUR_SCENE->GetTextureStore()->GetTextureData(_texFIleName)->pTexture;
	if (m_pTexture == nullptr)
	{
		MSG_BOX(__FILE__, L"m_pTexture - FAILED");
		ABORT;
		return E_FAIL;
	}


	return S_OK;
}

void CParticleSystemC::AddParticle(CParticle* pParticle)
{
	ATTRIBUTE attribute;

	pParticle->resetParticle(&attribute);
	pParticle->Add_ParticleAttribute();
	
}
