#include "stdafx.h"
#include "..\Header\Bronya_Cannon_Charge.h"

_uint CBronya_Cannon_Charge::m_s_uniqueID = 0;

CBronya_Cannon_Charge::CBronya_Cannon_Charge()
{
}


CBronya_Cannon_Charge::~CBronya_Cannon_Charge()
{
}

SP(CBronya_Cannon_Charge) CBronya_Cannon_Charge::Create(_bool isStatic, Engine::CScene * pScene)
{
	SP(CBronya_Cannon_Charge) spInstance(new CBronya_Cannon_Charge, Engine::SmartDeleter<CBronya_Cannon_Charge>);
	spInstance->SetIsStatic(isStatic);
	spInstance->SetScene(pScene);
	spInstance->Awake();

	return spInstance;
}

SP(Engine::CObject) CBronya_Cannon_Charge::MakeClone()
{
	SP(CBronya_Cannon_Charge) spClone(new CBronya_Cannon_Charge, Engine::SmartDeleter<CBronya_Cannon_Charge>);
	__super::InitClone(spClone);

	spClone->m_spTransform = spClone->GetComponent<Engine::CTransformC>();
	spClone->m_spTransform->SetRotationZ(D3DXToRadian(90.f));
	spClone->m_spMesh = spClone->GetComponent<Engine::CMeshC>();
	spClone->m_spGraphics = spClone->GetComponent<Engine::CGraphicsC>();
	spClone->m_spShader = spClone->GetComponent<Engine::CShaderC>();
	spClone->m_spTexture = spClone->GetComponent<Engine::CTextureC>();

	return spClone;
}

void CBronya_Cannon_Charge::Awake()
{
	__super::Awake();

}

void CBronya_Cannon_Charge::Start()
{
	__super::Start();
	m_fAlpha = 1.f;
}

void CBronya_Cannon_Charge::FixedUpdate()
{
	__super::FixedUpdate();

}

void CBronya_Cannon_Charge::Update()
{
	__super::Update();

	m_spTransform->AddRotationY(15.f * GET_DT);

	m_fTime += 3.f *  GET_DT;
}

void CBronya_Cannon_Charge::LateUpdate()
{
	__super::LateUpdate();

}

void CBronya_Cannon_Charge::PreRender(LPD3DXEFFECT pEffect)
{
	m_spMesh->PreRender(m_spGraphics, pEffect);
	pEffect->SetFloat("gAlpha", m_fAlpha);
}

void CBronya_Cannon_Charge::Render(LPD3DXEFFECT pEffect)
{
	m_spMesh->Render(m_spGraphics, pEffect);

}

void CBronya_Cannon_Charge::PostRender(LPD3DXEFFECT pEffect)
{
	m_spMesh->PostRender(m_spGraphics, pEffect);

}

void CBronya_Cannon_Charge::OnDestroy()
{
	__super::OnDestroy();

}

void CBronya_Cannon_Charge::OnEnable()
{
	__super::OnEnable();

}

void CBronya_Cannon_Charge::OnDisable()
{
	__super::OnDisable();

}

void CBronya_Cannon_Charge::SetBasicName()
{
	m_name = m_objectKey + std::to_wstring(m_s_uniqueID++);

}
