#include "stdafx.h"
#include "..\Header\Ganesha_Dome.h"

_uint CGanesha_Dome::m_s_uniqueID = 0;


CGanesha_Dome::CGanesha_Dome()
{
}


CGanesha_Dome::~CGanesha_Dome()
{
}

SP(CGanesha_Dome) CGanesha_Dome::Create(_bool isStatic, Engine::CScene * pScene)
{
	SP(CGanesha_Dome) spInstance(new CGanesha_Dome, Engine::SmartDeleter<CGanesha_Dome>);
	spInstance->SetIsStatic(isStatic);
	spInstance->SetScene(pScene);
	spInstance->Awake();

	return spInstance;
}

SP(Engine::CObject) CGanesha_Dome::MakeClone()
{
	SP(CGanesha_Dome) spClone(new CGanesha_Dome, Engine::SmartDeleter<CGanesha_Dome>);
	__super::InitClone(spClone);

	spClone->m_spTransform = spClone->GetComponent<Engine::CTransformC>();
	spClone->m_spTransform->SetRotationZ(D3DXToRadian(180.f));
	spClone->m_spTransform->SetSize(_float3(8.f, 8.f, 8.f));
	spClone->m_spMesh = spClone->GetComponent<Engine::CMeshC>();
	spClone->m_spGraphics = spClone->GetComponent<Engine::CGraphicsC>();
	spClone->m_spShader = spClone->GetComponent<Engine::CShaderC>();
	spClone->m_spTexture = spClone->GetComponent<Engine::CTextureC>();

	return spClone;
}

void CGanesha_Dome::Awake()
{
	__super::Awake();

}

void CGanesha_Dome::Start()
{
	__super::Start();
	m_fSize = m_spTransform->GetSize().x;
	m_fAlpha = 0.25f;
}

void CGanesha_Dome::FixedUpdate()
{
	__super::FixedUpdate();
}

void CGanesha_Dome::Update()
{
	__super::Update();

	_float _size = 0.f;
	_size += 30.f * GET_DT;

	if (this->GetTransform()->GetSize().x >= m_fSize + 10.f)
	{
		this->GetTransform()->SetSize(_float3(m_fSize, m_fSize, m_fSize));
	}

	this->GetTransform()->AddSize(_float3(_size, _size, _size) );
}

void CGanesha_Dome::LateUpdate()
{
	__super::LateUpdate();

}

void CGanesha_Dome::PreRender(LPD3DXEFFECT pEffect)
{
	m_spMesh->PreRender(m_spGraphics, pEffect);
	pEffect->SetFloat("gAlpha", m_fAlpha);
	pEffect->SetBool("gPlayingAnim", false);

	pEffect->CommitChanges();
}

void CGanesha_Dome::Render(LPD3DXEFFECT pEffect)
{
	m_spMesh->Render(m_spGraphics, pEffect);

}

void CGanesha_Dome::PostRender(LPD3DXEFFECT pEffect)
{
	m_spMesh->PostRender(m_spGraphics, pEffect);

}

void CGanesha_Dome::OnDestroy()
{
	__super::OnDestroy();

}

void CGanesha_Dome::OnEnable()
{
	__super::OnEnable();

}

void CGanesha_Dome::OnDisable()
{
	__super::OnDisable();

}

void CGanesha_Dome::SetBasicName()
{
	m_name = m_objectKey + std::to_wstring(m_s_uniqueID++);

}
