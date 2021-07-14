#include "stdafx.h"
#include "..\Header\Bronya_Impact_Ring.h"

_uint CBronya_Impact_Ring::m_s_uniqueID = 0;


CBronya_Impact_Ring::CBronya_Impact_Ring()
{
}


CBronya_Impact_Ring::~CBronya_Impact_Ring()
{
}

SP(CBronya_Impact_Ring) CBronya_Impact_Ring::Create(_bool isStatic, Engine::CScene * pScene)
{
	SP(CBronya_Impact_Ring) spInstance(new CBronya_Impact_Ring, Engine::SmartDeleter<CBronya_Impact_Ring>);
	spInstance->SetIsStatic(isStatic);
	spInstance->SetScene(pScene);
	spInstance->Awake();

	return spInstance;
}

SP(Engine::CObject) CBronya_Impact_Ring::MakeClone()
{
	SP(CBronya_Impact_Ring) spClone(new CBronya_Impact_Ring, Engine::SmartDeleter<CBronya_Impact_Ring>);
	__super::InitClone(spClone);

	spClone->m_spTransform = spClone->GetComponent<Engine::CTransformC>();
	spClone->m_spMesh = spClone->GetComponent<Engine::CMeshC>();
	spClone->m_spGraphics = spClone->GetComponent<Engine::CGraphicsC>();
	spClone->m_spShader = spClone->GetComponent<Engine::CShaderC>();
	spClone->m_spTexture = spClone->GetComponent<Engine::CTextureC>();

	return spClone;
}

void CBronya_Impact_Ring::Awake()
{
	__super::Awake();

}

void CBronya_Impact_Ring::Start()
{
	__super::Start();
	m_fAlpha = 1.f;
}

void CBronya_Impact_Ring::FixedUpdate()
{
	__super::FixedUpdate();

}

void CBronya_Impact_Ring::Update()
{
	__super::Update();

	if (m_fAlpha <= 0.f)
	{
		this->SetDeleteThis(true);
	}

	m_fAlpha -= 3.f * GET_DT;
}

void CBronya_Impact_Ring::LateUpdate()
{
	__super::LateUpdate();

}

void CBronya_Impact_Ring::PreRender(LPD3DXEFFECT pEffect)
{
	m_spMesh->PreRender(m_spGraphics, pEffect);
	pEffect->SetFloat("gAlpha", m_fAlpha);

	pEffect->CommitChanges();

}

void CBronya_Impact_Ring::Render(LPD3DXEFFECT pEffect)
{
	m_spMesh->Render(m_spGraphics, pEffect);

}

void CBronya_Impact_Ring::PostRender(LPD3DXEFFECT pEffect)
{
	m_spMesh->PostRender(m_spGraphics, pEffect);

}

void CBronya_Impact_Ring::OnDestroy()
{
	__super::OnDestroy();

}

void CBronya_Impact_Ring::OnEnable()
{
	__super::OnEnable();

}

void CBronya_Impact_Ring::OnDisable()
{
	__super::OnDisable();

}

void CBronya_Impact_Ring::SetBasicName()
{
	m_name = m_objectKey + std::to_wstring(m_s_uniqueID++);

}