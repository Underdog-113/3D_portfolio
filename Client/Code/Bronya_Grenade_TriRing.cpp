#include "stdafx.h"
#include "..\Header\Bronya_Grenade_TriRing.h"

_uint CBronya_Grenade_TriRing::m_s_uniqueID = 0;

CBronya_Grenade_TriRing::CBronya_Grenade_TriRing()
{
}


CBronya_Grenade_TriRing::~CBronya_Grenade_TriRing()
{
}

SP(CBronya_Grenade_TriRing) CBronya_Grenade_TriRing::Create(_bool isStatic, Engine::CScene * pScene)
{
	SP(CBronya_Grenade_TriRing) spInstance(new CBronya_Grenade_TriRing, Engine::SmartDeleter<CBronya_Grenade_TriRing>);
	spInstance->SetIsStatic(isStatic);
	spInstance->SetScene(pScene);
	spInstance->Awake();

	return spInstance;
}

SP(Engine::CObject) CBronya_Grenade_TriRing::MakeClone()
{
	SP(CBronya_Grenade_TriRing) spClone(new CBronya_Grenade_TriRing, Engine::SmartDeleter<CBronya_Grenade_TriRing>);
	__super::InitClone(spClone);

	spClone->m_spTransform = spClone->GetComponent<Engine::CTransformC>();
	spClone->m_spTransform->SetSize(2.f, 2.f, 2.f);
	spClone->m_spMesh = spClone->GetComponent<Engine::CMeshC>();
	spClone->m_spGraphics = spClone->GetComponent<Engine::CGraphicsC>();
	spClone->m_spShader = spClone->GetComponent<Engine::CShaderC>();
	spClone->m_spTexture = spClone->GetComponent<Engine::CTextureC>();

	return spClone;
}

void CBronya_Grenade_TriRing::Awake()
{
	__super::Awake();

}

void CBronya_Grenade_TriRing::Start()
{
	__super::Start();
	m_fAlpha = 1.f;
}

void CBronya_Grenade_TriRing::FixedUpdate()
{
	__super::FixedUpdate();

}

void CBronya_Grenade_TriRing::Update()
{
	__super::Update();

	if (m_fAlpha <= 0.f)
	{
		this->SetDeleteThis(true);
	}

	m_fAlpha -= 3.f * GET_DT;
}

void CBronya_Grenade_TriRing::LateUpdate()
{
	__super::LateUpdate();

}

void CBronya_Grenade_TriRing::PreRender(LPD3DXEFFECT pEffect)
{
	m_spMesh->PreRender(m_spGraphics, pEffect);
	pEffect->SetFloat("gAlpha", m_fAlpha);
}

void CBronya_Grenade_TriRing::Render(LPD3DXEFFECT pEffect)
{
	m_spMesh->Render(m_spGraphics, pEffect);

}

void CBronya_Grenade_TriRing::PostRender(LPD3DXEFFECT pEffect)
{
	m_spMesh->PostRender(m_spGraphics, pEffect);

}

void CBronya_Grenade_TriRing::OnDestroy()
{
	__super::OnDestroy();

}

void CBronya_Grenade_TriRing::OnEnable()
{
	__super::OnEnable();

}

void CBronya_Grenade_TriRing::OnDisable()
{
	__super::OnDisable();

}

void CBronya_Grenade_TriRing::SetBasicName()
{
	m_name = m_objectKey + std::to_wstring(m_s_uniqueID++);

}
