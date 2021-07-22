#include "stdafx.h"
#include "..\Header\Bronya_Teleport_Laser.h"

_uint CBronya_Teleport_Laser::m_s_uniqueID = 0;

CBronya_Teleport_Laser::CBronya_Teleport_Laser()
{
}


CBronya_Teleport_Laser::~CBronya_Teleport_Laser()
{
}

SP(CBronya_Teleport_Laser) CBronya_Teleport_Laser::Create(_bool isStatic, Engine::CScene * pScene)
{
	SP(CBronya_Teleport_Laser) spInstance(new CBronya_Teleport_Laser, Engine::SmartDeleter<CBronya_Teleport_Laser>);
	spInstance->SetIsStatic(isStatic);
	spInstance->SetScene(pScene);
	spInstance->Awake();

	return spInstance;
}

SP(Engine::CObject) CBronya_Teleport_Laser::MakeClone()
{
	SP(CBronya_Teleport_Laser) spClone(new CBronya_Teleport_Laser, Engine::SmartDeleter<CBronya_Teleport_Laser>);
	__super::InitClone(spClone);

	spClone->m_spTransform = spClone->GetComponent<Engine::CTransformC>();
	spClone->m_spMesh = spClone->GetComponent<Engine::CMeshC>();
	spClone->m_spGraphics = spClone->GetComponent<Engine::CGraphicsC>();
	spClone->m_spShader = spClone->GetComponent<Engine::CShaderC>();
	spClone->m_spTexture = spClone->GetComponent<Engine::CTextureC>();

	return spClone;
}

void CBronya_Teleport_Laser::Awake()
{
	__super::Awake();

}

void CBronya_Teleport_Laser::Start()
{
	__super::Start();
	m_fAlpha = 1.f;

	m_bCheck = false;
}

void CBronya_Teleport_Laser::FixedUpdate()
{
	__super::FixedUpdate();

}

void CBronya_Teleport_Laser::Update()
{
	__super::Update();

}

void CBronya_Teleport_Laser::LateUpdate()
{
	__super::LateUpdate();	
}

void CBronya_Teleport_Laser::PreRender(LPD3DXEFFECT pEffect)
{
	m_spMesh->PreRender(m_spGraphics, pEffect);
	pEffect->SetFloat("gAlpha", m_fAlpha);
	pEffect->SetBool("g_zWriteEnabled", true);
	pEffect->CommitChanges();

	_mat matWorld, matView, matBill;

	matView = Engine::GET_MAIN_CAM->GetViewMatrix();

	D3DXMatrixIdentity(&matBill);

	matBill._11 = matView._11;
	matBill._13 = matView._13;
	matBill._31 = matView._31;
	matBill._33 = matView._33;

	D3DXMatrixInverse(&matBill, 0, &matBill);

	matWorld = m_spGraphics->GetTransform()->GetWorldMatrix();

	m_spGraphics->GetTransform()->SetWorldMatrix(matBill * matWorld);
}

void CBronya_Teleport_Laser::Render(LPD3DXEFFECT pEffect)
{
	m_spMesh->Render(m_spGraphics, pEffect);

}

void CBronya_Teleport_Laser::PostRender(LPD3DXEFFECT pEffect)
{
	m_spMesh->PostRender(m_spGraphics, pEffect);
}

void CBronya_Teleport_Laser::OnDestroy()
{
	__super::OnDestroy();

}

void CBronya_Teleport_Laser::OnEnable()
{
	__super::OnEnable();

}

void CBronya_Teleport_Laser::OnDisable()
{
	__super::OnDisable();

}

void CBronya_Teleport_Laser::SetBasicName()
{
	m_name = m_objectKey + std::to_wstring(m_s_uniqueID++);

}
