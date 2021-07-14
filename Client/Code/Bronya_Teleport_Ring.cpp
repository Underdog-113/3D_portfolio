#include "stdafx.h"
#include "..\Header\Bronya_Teleport_Ring.h"

_uint CBronya_Teleport_Ring::m_s_uniqueID = 0;

CBronya_Teleport_Ring::CBronya_Teleport_Ring()
{
}


CBronya_Teleport_Ring::~CBronya_Teleport_Ring()
{
}

SP(CBronya_Teleport_Ring) CBronya_Teleport_Ring::Create(_bool isStatic, Engine::CScene * pScene)
{
	SP(CBronya_Teleport_Ring) spInstance(new CBronya_Teleport_Ring, Engine::SmartDeleter<CBronya_Teleport_Ring>);
	spInstance->SetIsStatic(isStatic);
	spInstance->SetScene(pScene);
	spInstance->Awake();

	return spInstance;
}

SP(Engine::CObject) CBronya_Teleport_Ring::MakeClone(void)
{
	SP(CBronya_Teleport_Ring) spClone(new CBronya_Teleport_Ring, Engine::SmartDeleter<CBronya_Teleport_Ring>);

	__super::InitClone(spClone);

	spClone->m_spTransform = spClone->GetComponent<Engine::CTransformC>();
	spClone->m_spMesh = spClone->GetComponent<Engine::CMeshC>();
	spClone->m_spGraphics = spClone->GetComponent<Engine::CGraphicsC>();
	spClone->m_spShader = spClone->GetComponent<Engine::CShaderC>();
	spClone->m_spTexture = spClone->GetComponent<Engine::CTextureC>();

	return spClone;
}

void CBronya_Teleport_Ring::Awake(void)
{
	__super::Awake();

}

void CBronya_Teleport_Ring::Start(void)
{
	__super::Start();
	m_fAlpha = 1.f;
}

void CBronya_Teleport_Ring::FixedUpdate(void)
{
	__super::FixedUpdate();

}

void CBronya_Teleport_Ring::Update(void)
{
	__super::Update();

	if (m_fAlpha <= 0.f)
	{
		this->SetDeleteThis(true);
	}
	_float _size = -0.5f * GET_DT;

	m_spTransform->AddSize(_float3(_size, _size, _size));

	m_fAlpha -= 0.7f * GET_DT;
}

void CBronya_Teleport_Ring::LateUpdate(void)
{
	__super::LateUpdate();
}

void CBronya_Teleport_Ring::PreRender(LPD3DXEFFECT pEffect)
{
	m_spMesh->PreRender(m_spGraphics, pEffect);

	pEffect->SetFloat("gAlpha", m_fAlpha);

	pEffect->CommitChanges();
}

void CBronya_Teleport_Ring::Render(LPD3DXEFFECT pEffect)
{
	m_spMesh->Render(m_spGraphics, pEffect);

}

void CBronya_Teleport_Ring::PostRender(LPD3DXEFFECT pEffect)
{
	m_spMesh->PostRender(m_spGraphics, pEffect);

}

void CBronya_Teleport_Ring::OnDestroy(void)
{
	__super::OnDestroy();

}

void CBronya_Teleport_Ring::OnEnable(void)
{
	__super::OnEnable();

}

void CBronya_Teleport_Ring::OnDisable(void)
{
	__super::OnDisable();

}

void CBronya_Teleport_Ring::SetBasicName(void)
{
	m_name = m_objectKey + std::to_wstring(m_s_uniqueID++);

}