#include "stdafx.h"
#include "..\Header\Ganesha_Cinema_Circle.h"

_uint CGanesha_Cinema_Circle::m_s_uniqueID = 0;

CGanesha_Cinema_Circle::CGanesha_Cinema_Circle()
{
}


CGanesha_Cinema_Circle::~CGanesha_Cinema_Circle()
{
}

SP(CGanesha_Cinema_Circle) CGanesha_Cinema_Circle::Create(_bool isStatic, Engine::CScene * pScene)
{
	SP(CGanesha_Cinema_Circle) spInstance(new CGanesha_Cinema_Circle, Engine::SmartDeleter<CGanesha_Cinema_Circle>);
	spInstance->SetIsStatic(isStatic);
	spInstance->SetScene(pScene);
	spInstance->Awake();

	return spInstance;
}

SP(Engine::CObject) CGanesha_Cinema_Circle::MakeClone()
{
	SP(CGanesha_Cinema_Circle) spClone(new CGanesha_Cinema_Circle, Engine::SmartDeleter<CGanesha_Cinema_Circle>);
	__super::InitClone(spClone);

	spClone->m_spTransform = spClone->GetComponent<Engine::CTransformC>();
	spClone->m_spMesh = spClone->GetComponent<Engine::CMeshC>();
	spClone->m_spGraphics = spClone->GetComponent<Engine::CGraphicsC>();
	spClone->m_spShader = spClone->GetComponent<Engine::CShaderC>();
	spClone->m_spTexture = spClone->GetComponent<Engine::CTextureC>();

	return spClone;
}

void CGanesha_Cinema_Circle::Awake()
{
	__super::Awake();
	_float _size = 0.05f;
	m_spTransform->SetSize(_float3(_size, _size, _size));
	m_spMesh->SetMeshData(L"Ganesha_Cinema_Circle");
	m_spMesh->SetIsEffectMesh(true);
	m_spGraphics->SetRenderID((_int)Engine::ERenderID::AlphaBlend);
	m_spTexture->AddTexture(L"AttackHint_Circle_02");
	m_spTexture->AddTexture(L"Sign");
	m_spShader->AddShader((_int)EShaderID::AlphaMaskShader);

}

void CGanesha_Cinema_Circle::Start()
{
	__super::Start();
	m_fAlpha = 0.2f;
	m_size = m_spTransform->GetSize();

}

void CGanesha_Cinema_Circle::FixedUpdate()
{
	__super::FixedUpdate();

}

void CGanesha_Cinema_Circle::Update()
{
	__super::Update();
	m_fAlpha = 0.2f;
	_float _size = 1.f * GET_DT;

	m_spTransform->AddSize(_float3(_size, _size, _size));

	if (m_spTransform->GetSize().x > m_size.x + 0.3f)
	{
		m_spTransform->SetSize(m_size);
	}

}

void CGanesha_Cinema_Circle::LateUpdate()
{
	__super::LateUpdate();

}

void CGanesha_Cinema_Circle::PreRender(LPD3DXEFFECT pEffect)
{
	m_spMesh->PreRender(m_spGraphics, pEffect);
	pEffect->SetFloat("gAlpha", m_fAlpha);
	pEffect->SetBool("gPlayingAnim", false);
	pEffect->CommitChanges();
}

void CGanesha_Cinema_Circle::Render(LPD3DXEFFECT pEffect)
{
	m_spMesh->Render(m_spGraphics, pEffect);

}

void CGanesha_Cinema_Circle::PostRender(LPD3DXEFFECT pEffect)
{
	m_spMesh->PostRender(m_spGraphics, pEffect);

}

void CGanesha_Cinema_Circle::OnDestroy()
{
	__super::OnDestroy();

}

void CGanesha_Cinema_Circle::OnEnable()
{
	__super::OnEnable();

}

void CGanesha_Cinema_Circle::OnDisable()
{
	__super::OnDisable();

}

void CGanesha_Cinema_Circle::SetBasicName()
{
	m_name = m_objectKey + std::to_wstring(m_s_uniqueID++);

}
