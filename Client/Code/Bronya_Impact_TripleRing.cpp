#include "stdafx.h"
#include "..\Header\Bronya_Impact_TripleRing.h"

_uint CBronya_Impact_TripleRing::m_s_uniqueID = 0;

CBronya_Impact_TripleRing::CBronya_Impact_TripleRing()
{
}


CBronya_Impact_TripleRing::~CBronya_Impact_TripleRing()
{
}

SP(CBronya_Impact_TripleRing) CBronya_Impact_TripleRing::Create(_bool isStatic, Engine::CScene * pScene)
{
	SP(CBronya_Impact_TripleRing) spInstance(new CBronya_Impact_TripleRing, Engine::SmartDeleter<CBronya_Impact_TripleRing>);
	spInstance->SetIsStatic(isStatic);
	spInstance->SetScene(pScene);
	spInstance->Awake();

	return spInstance;
}

SP(Engine::CObject) CBronya_Impact_TripleRing::MakeClone()
{
	SP(CBronya_Impact_TripleRing) spClone(new CBronya_Impact_TripleRing, Engine::SmartDeleter<CBronya_Impact_TripleRing>);
	__super::InitClone(spClone);

	spClone->m_spTransform = spClone->GetComponent<Engine::CTransformC>();
	spClone->m_spMesh = spClone->GetComponent<Engine::CMeshC>();
	spClone->m_spGraphics = spClone->GetComponent<Engine::CGraphicsC>();
	spClone->m_spShader = spClone->GetComponent<Engine::CShaderC>();
	spClone->m_spTexture = spClone->GetComponent<Engine::CTextureC>();

	return spClone;
}

void CBronya_Impact_TripleRing::Awake()
{
	__super::Awake();

}

void CBronya_Impact_TripleRing::Start()
{
	__super::Start();
	m_fAlpha = 1.f;
}

void CBronya_Impact_TripleRing::FixedUpdate()
{
	__super::FixedUpdate();

}

void CBronya_Impact_TripleRing::Update()
{
	__super::Update();

	if (m_fAlpha <= 0.f)
	{
		this->SetDeleteThis(true);
	}

	m_fAlpha -= 3.f * GET_DT;

}

void CBronya_Impact_TripleRing::LateUpdate()
{
	__super::LateUpdate();

}

void CBronya_Impact_TripleRing::PreRender(LPD3DXEFFECT pEffect)
{
	m_spMesh->PreRender(m_spGraphics, pEffect);
	pEffect->SetFloat("gAlpha", m_fAlpha);
}

void CBronya_Impact_TripleRing::Render(LPD3DXEFFECT pEffect)
{
	m_spMesh->Render(m_spGraphics, pEffect);

}

void CBronya_Impact_TripleRing::PostRender(LPD3DXEFFECT pEffect)
{
	m_spMesh->PostRender(m_spGraphics, pEffect);

}

void CBronya_Impact_TripleRing::OnDestroy()
{
	__super::OnDestroy();

}

void CBronya_Impact_TripleRing::OnEnable()
{
	__super::OnEnable();

}

void CBronya_Impact_TripleRing::OnDisable()
{
	__super::OnDisable();

}

void CBronya_Impact_TripleRing::SetBasicName()
{
	m_name = m_objectKey + std::to_wstring(m_s_uniqueID++);

}
