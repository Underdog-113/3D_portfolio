#include "stdafx.h"
#include "..\Header\Bronya_TeleportBase.h"

_uint CBronya_TeleportBase::m_s_uniqueID = 0;

CBronya_TeleportBase::CBronya_TeleportBase()
{
}


CBronya_TeleportBase::~CBronya_TeleportBase()
{
}

SP(CBronya_TeleportBase) CBronya_TeleportBase::Create(_bool isStatic, Engine::CScene * pScene)
{
	SP(CBronya_TeleportBase) spInstance(new CBronya_TeleportBase, Engine::SmartDeleter<CBronya_TeleportBase>);
	spInstance->SetIsStatic(isStatic);
	spInstance->SetScene(pScene);
	spInstance->Awake();

	return spInstance;
}

SP(Engine::CObject) CBronya_TeleportBase::MakeClone()
{
	SP(CBronya_TeleportBase) spClone(new CBronya_TeleportBase, Engine::SmartDeleter<CBronya_TeleportBase>);
	__super::InitClone(spClone);

	spClone->m_spTransform = spClone->GetComponent<Engine::CTransformC>();
	spClone->m_spMesh = spClone->GetComponent<Engine::CMeshC>();
	spClone->m_spGraphics = spClone->GetComponent<Engine::CGraphicsC>();
	spClone->m_spShader = spClone->GetComponent<Engine::CShaderC>();
	spClone->m_spTexture = spClone->GetComponent<Engine::CTextureC>();

	return spClone;
}

void CBronya_TeleportBase::Awake()
{
	__super::Awake();

}

void CBronya_TeleportBase::Start()
{
	__super::Start();

}

void CBronya_TeleportBase::FixedUpdate()
{
	__super::FixedUpdate();

}

void CBronya_TeleportBase::Update()
{
	__super::Update();

}

void CBronya_TeleportBase::LateUpdate()
{
	__super::LateUpdate();

}

void CBronya_TeleportBase::PreRender(LPD3DXEFFECT pEffect)
{
	m_spMesh->PreRender(m_spGraphics, pEffect);
	pEffect->SetFloat("gAlpha", m_fAlpha);
	pEffect->SetBool("gPlayingAnim", false);
	pEffect->CommitChanges();

}

void CBronya_TeleportBase::Render(LPD3DXEFFECT pEffect)
{
	m_spMesh->Render(m_spGraphics, pEffect);

}

void CBronya_TeleportBase::PostRender(LPD3DXEFFECT pEffect)
{
	m_spMesh->PostRender(m_spGraphics, pEffect);

}

void CBronya_TeleportBase::OnDestroy()
{
	__super::OnDestroy();

}

void CBronya_TeleportBase::OnEnable()
{
	__super::OnEnable();

}

void CBronya_TeleportBase::OnDisable()
{
	__super::OnDisable();
}

void CBronya_TeleportBase::SetBasicName()
{
	m_name = m_objectKey + std::to_wstring(m_s_uniqueID++);	
}
