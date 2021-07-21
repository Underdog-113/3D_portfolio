#include "stdafx.h"
#include "..\Header\Ganesha_Cinema_Dome.h"

_uint CGanesha_Cinema_Dome::m_s_uniqueID = 0;

CGanesha_Cinema_Dome::CGanesha_Cinema_Dome()
{
}


CGanesha_Cinema_Dome::~CGanesha_Cinema_Dome()
{
}

SP(CGanesha_Cinema_Dome) CGanesha_Cinema_Dome::Create(_bool isStatic, Engine::CScene * pScene)
{
	SP(CGanesha_Cinema_Dome) spInstance(new CGanesha_Cinema_Dome, Engine::SmartDeleter<CGanesha_Cinema_Dome>);
	spInstance->SetIsStatic(isStatic);
	spInstance->SetScene(pScene);
	spInstance->Awake();

	return spInstance;
}

SP(Engine::CObject) CGanesha_Cinema_Dome::MakeClone()
{
	SP(CGanesha_Cinema_Dome) spClone(new CGanesha_Cinema_Dome, Engine::SmartDeleter<CGanesha_Cinema_Dome>);
	__super::InitClone(spClone);

	spClone->m_spTransform = spClone->GetComponent<Engine::CTransformC>();
	spClone->m_spMesh = spClone->GetComponent<Engine::CMeshC>();
	spClone->m_spGraphics = spClone->GetComponent<Engine::CGraphicsC>();
	spClone->m_spShader = spClone->GetComponent<Engine::CShaderC>();
	spClone->m_spTexture = spClone->GetComponent<Engine::CTextureC>();
	return spClone;
}

void CGanesha_Cinema_Dome::Awake()
{
	__super::Awake();
	_float size = 0.05f;
	m_spTransform->SetSize(_float3(size, size, size));
	m_spMesh->SetMeshData(L"Ganesha_Cinema_Dome");
	m_spMesh->SetIsEffectMesh(true);
	m_spGraphics->SetRenderID((_int)Engine::ERenderID::NonAlpha);
	m_spTexture->AddTexture(L"AttackHint_Circle_02");
	m_spTexture->AddTexture(L"Sign");
	m_spShader->AddShader((_int)EShaderID::AlphaMaskGlowShader);
}

void CGanesha_Cinema_Dome::Start()
{
	__super::Start();
	m_fAlpha = 0.1f;
	m_size = m_spTransform->GetSize();
}

void CGanesha_Cinema_Dome::FixedUpdate()
{
	__super::FixedUpdate();

}

void CGanesha_Cinema_Dome::Update()
{
	__super::Update();

	_float _size = 1.f * GET_DT;

	m_spTransform->AddSize(_float3(_size, _size, _size));

	if (m_spTransform->GetSize().x > m_size.x + 0.2)
	{
		_int iRand = rand() % 4;

		for (_int i = 0; i < 3; ++i)
		{
			SP(Engine::CObject) spObj = Engine::GET_CUR_SCENE->GetObjectFactory()->AddClone(L"Ganesha_Cinema_Lightning", true, (_uint)Engine::ELayerID::Effect);
			spObj->GetTransform()->SetPosition(_float3(m_spTransform->GetPosition().x + _float(rand() % 3 - 0.8f), m_spTransform->GetPosition().y, m_spTransform->GetPosition().z + _float(rand() % 2) - 0.5f));
		}
		m_spTransform->SetSize(m_size);
	}
}

void CGanesha_Cinema_Dome::LateUpdate()
{
	__super::LateUpdate();

}

void CGanesha_Cinema_Dome::PreRender(LPD3DXEFFECT pEffect)
{
	m_spMesh->PreRender(m_spGraphics, pEffect);
	pEffect->SetFloat("gAlpha", m_fAlpha);
	pEffect->SetBool("gPlayingAnim", false);
	pEffect->CommitChanges();
}

void CGanesha_Cinema_Dome::Render(LPD3DXEFFECT pEffect)
{
	m_spMesh->Render(m_spGraphics, pEffect);

}

void CGanesha_Cinema_Dome::PostRender(LPD3DXEFFECT pEffect)
{
	m_spMesh->PostRender(m_spGraphics, pEffect);

}

void CGanesha_Cinema_Dome::OnDestroy()
{
	__super::OnDestroy();

}

void CGanesha_Cinema_Dome::OnEnable()
{
	__super::OnEnable();

}

void CGanesha_Cinema_Dome::OnDisable()
{
	__super::OnDisable();

}

void CGanesha_Cinema_Dome::SetBasicName()
{
	m_name = m_objectKey + std::to_wstring(m_s_uniqueID++);

}
