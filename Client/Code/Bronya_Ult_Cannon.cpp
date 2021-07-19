#include "stdafx.h"
#include "..\Header\Bronya_Ult_Cannon.h"

_uint CBronya_Ult_Cannon::m_s_uniqueID = 0;

CBronya_Ult_Cannon::CBronya_Ult_Cannon()
{
}


CBronya_Ult_Cannon::~CBronya_Ult_Cannon()
{
}

SP(CBronya_Ult_Cannon) CBronya_Ult_Cannon::Create(_bool isStatic, Engine::CScene * pScene)
{
	SP(CBronya_Ult_Cannon) spInstance(new CBronya_Ult_Cannon, Engine::SmartDeleter<CBronya_Ult_Cannon>);
	spInstance->SetIsStatic(isStatic);
	spInstance->SetScene(pScene);
	spInstance->Awake();

	return spInstance;
}

SP(Engine::CObject) CBronya_Ult_Cannon::MakeClone()
{
	SP(CBronya_Ult_Cannon) spClone(new CBronya_Ult_Cannon, Engine::SmartDeleter<CBronya_Ult_Cannon>);
	__super::InitClone(spClone);

	spClone->m_spTransform = spClone->GetComponent<Engine::CTransformC>();
	spClone->m_spTransform->SetSize(0.4f, 0.4f, 0.4f);
	spClone->m_spMesh = spClone->GetComponent<Engine::CMeshC>();
	spClone->m_spGraphics = spClone->GetComponent<Engine::CGraphicsC>();
	spClone->m_spShader = spClone->GetComponent<Engine::CShaderC>();
	spClone->m_spTexture = spClone->GetComponent<Engine::CTextureC>();

	return spClone;
}

void CBronya_Ult_Cannon::Awake()
{
	__super::Awake();

}

void CBronya_Ult_Cannon::Start()
{
	__super::Start();

	m_fTmpPosZ = m_spTransform->GetPosition().z;
	m_fAlpha = 0.7f;
}

void CBronya_Ult_Cannon::FixedUpdate()
{
	__super::FixedUpdate();

}

void CBronya_Ult_Cannon::Update()
{
	__super::Update();

	if (m_fTmpPosZ - 0.5f <= m_spTransform->GetPosition().z)
	{
		m_spTransform->AddPosition(-m_spTransform->GetForward() * GET_DT * 0.5f);
	}
}

void CBronya_Ult_Cannon::LateUpdate()
{
	__super::LateUpdate();

}

void CBronya_Ult_Cannon::PreRender(LPD3DXEFFECT pEffect)
{
	m_spMesh->PreRender(m_spGraphics, pEffect);
	pEffect->SetFloat("gAlpha", m_fAlpha);
	pEffect->SetBool("g_zWriteEnabled", true);
	pEffect->SetBool("g_AlphaTestEnabled", false);
	pEffect->CommitChanges();

}

void CBronya_Ult_Cannon::Render(LPD3DXEFFECT pEffect)
{
	m_spMesh->Render(m_spGraphics, pEffect);

}

void CBronya_Ult_Cannon::PostRender(LPD3DXEFFECT pEffect)
{
	m_spMesh->PostRender(m_spGraphics, pEffect);

}

void CBronya_Ult_Cannon::OnDestroy()
{
	__super::OnDestroy();

}

void CBronya_Ult_Cannon::OnEnable()
{
	__super::OnEnable();

}

void CBronya_Ult_Cannon::OnDisable()
{
	__super::OnDisable();

}

void CBronya_Ult_Cannon::SetBasicName()
{
	m_name = m_objectKey + std::to_wstring(m_s_uniqueID++);

}
