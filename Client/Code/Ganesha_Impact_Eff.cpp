#include "stdafx.h"
#include "..\Header\Ganesha_Impact_Eff.h"

_uint CGanesha_Impact_Eff::m_s_uniqueID = 0;

CGanesha_Impact_Eff::CGanesha_Impact_Eff()
{
}


CGanesha_Impact_Eff::~CGanesha_Impact_Eff()
{
}

SP(CGanesha_Impact_Eff) CGanesha_Impact_Eff::Create(_bool isStatic, Engine::CScene * pScene)
{
	SP(CGanesha_Impact_Eff) spInstance(new CGanesha_Impact_Eff, Engine::SmartDeleter<CGanesha_Impact_Eff>);
	spInstance->SetIsStatic(isStatic);
	spInstance->SetScene(pScene);
	spInstance->Awake();

	return spInstance;
}

SP(Engine::CObject) CGanesha_Impact_Eff::MakeClone()
{
	SP(CGanesha_Impact_Eff) spClone(new CGanesha_Impact_Eff, Engine::SmartDeleter<CGanesha_Impact_Eff>);
	__super::InitClone(spClone);

	spClone->m_spTransform = spClone->GetComponent<Engine::CTransformC>();
	spClone->m_spMesh = spClone->GetComponent<Engine::CMeshC>();
	spClone->m_spGraphics = spClone->GetComponent<Engine::CGraphicsC>();
	spClone->m_spTexture = spClone->GetComponent<Engine::CTextureC>();
	spClone->m_spShader = spClone->GetComponent<Engine::CShaderC>();

	return spClone;
}

void CGanesha_Impact_Eff::Awake()
{
	__super::Awake();
	m_spMesh->SetMeshData(L"Robot_Impact");
	m_spMesh->SetIsEffectMesh(true);
	m_spGraphics->SetRenderID((_int)Engine::ERenderID::Effect);
	m_spTexture->AddTexture(L"Gray");
	m_spTexture->AddTexture(L"yun01");
	m_spTexture->AddTexture(L"yun01");
	m_spShader->AddShader((_int)EShaderID::AlphaMaskGlowShader);
}

void CGanesha_Impact_Eff::Start()
{
	__super::Start();
	m_fAlpha = 1.f;
	m_fTime = 0.f;
}

void CGanesha_Impact_Eff::FixedUpdate()
{
	__super::FixedUpdate();
}

void CGanesha_Impact_Eff::Update()
{
	__super::Update();

	if (m_fAlpha <= 0)
	{
		this->SetDeleteThis(true);
	}

	_float3 _size = _float3(0.5f, 0.5f, 0.5f);

	m_fAlpha -= 0.7f * GET_DT;
	m_fTime += 0.2f * GET_DT;
	m_spTransform->AddSize(_size * GET_DT);
}

void CGanesha_Impact_Eff::LateUpdate()
{
	__super::LateUpdate();

}

void CGanesha_Impact_Eff::PreRender(LPD3DXEFFECT pEffect)
{
	m_spMesh->PreRender(m_spGraphics, pEffect);
	pEffect->SetFloat("gAlpha", m_fAlpha);
	pEffect->SetFloat("gSpeed", m_fTime);
	pEffect->SetBool("gPlayingAnim", true);

	pEffect->CommitChanges();
}

void CGanesha_Impact_Eff::Render(LPD3DXEFFECT pEffect)
{
	m_spMesh->Render(m_spGraphics, pEffect);
}

void CGanesha_Impact_Eff::PostRender(LPD3DXEFFECT pEffect)
{
	m_spMesh->PostRender(m_spGraphics, pEffect);
}

void CGanesha_Impact_Eff::OnDestroy()
{
	__super::OnDestroy();

}

void CGanesha_Impact_Eff::OnEnable()
{
	__super::OnEnable();
}

void CGanesha_Impact_Eff::OnDisable()
{
	__super::OnDisable();

}

void CGanesha_Impact_Eff::SetBasicName()
{
	m_name = m_objectKey + std::to_wstring(m_s_uniqueID++);
}
