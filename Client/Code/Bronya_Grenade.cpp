#include "stdafx.h"
#include "..\Header\Bronya_Grenade.h"

_uint CBronya_Grenade::m_s_uniqueID = 0;

CBronya_Grenade::CBronya_Grenade()
{
}


CBronya_Grenade::~CBronya_Grenade()
{
}

SP(CBronya_Grenade) CBronya_Grenade::Create(_bool isStatic, Engine::CScene * pScene)
{
	SP(CBronya_Grenade) spInstance(new CBronya_Grenade, Engine::SmartDeleter<CBronya_Grenade>);
	spInstance->SetIsStatic(isStatic);
	spInstance->SetScene(pScene);
	spInstance->Awake();

	return spInstance;
}

SP(Engine::CObject) CBronya_Grenade::MakeClone()
{
	SP(CBronya_Grenade) spClone(new CBronya_Grenade, Engine::SmartDeleter<CBronya_Grenade>);
	__super::InitClone(spClone);

	spClone->m_spTransform = spClone->GetComponent<Engine::CTransformC>();
	spClone->m_spMesh = spClone->GetComponent<Engine::CMeshC>();
	spClone->m_spGraphics = spClone->GetComponent<Engine::CGraphicsC>();
	spClone->m_spShader = spClone->GetComponent<Engine::CShaderC>();
	spClone->m_spTexture = spClone->GetComponent<Engine::CTextureC>();

	return spClone;
}

void CBronya_Grenade::Awake()
{
	__super::Awake();

}

void CBronya_Grenade::Start()
{
	__super::Start();
	m_fAlpha = 1.f;
	m_fTime = 0.f;
}

void CBronya_Grenade::FixedUpdate()
{
	__super::FixedUpdate();
}

void CBronya_Grenade::Update()
{
	__super::Update();

	if (m_fTime >= 2.5f)
	{
		SP(Engine::CObject) spDome = Engine::GET_CUR_SCENE->GetObjectFactory()->AddClone(L"Bronya_Grenade_Dome", true);
		spDome->GetTransform()->SetPosition(m_spTransform->GetPosition());
		spDome->GetTransform()->SetPositionY(m_spTransform->GetPosition().y - 0.07f);

		SP(Engine::CObject) spImpact = Engine::GET_CUR_SCENE->GetObjectFactory()->AddClone(L"Bronya_Grenade_Impact", true);
		spImpact->GetTransform()->SetPosition(m_spTransform->GetPosition());

		SP(Engine::CObject) spTriRing = Engine::GET_CUR_SCENE->GetObjectFactory()->AddClone(L"Bronya_Grenade_TriRing", true);
		spTriRing->GetTransform()->SetPosition(m_spTransform->GetPosition());
		spTriRing->GetTransform()->SetPositionY(m_spTransform->GetPosition().y - 0.07f);

		this->SetDeleteThis(true);
	}

	m_fTime += GET_DT;

}

void CBronya_Grenade::LateUpdate()
{
	__super::LateUpdate();

}

void CBronya_Grenade::PreRender(LPD3DXEFFECT pEffect)
{
	m_spMesh->PreRender(m_spGraphics, pEffect);
	pEffect->SetFloat("gAlpha", m_fAlpha);

	pEffect->CommitChanges();
}

void CBronya_Grenade::Render(LPD3DXEFFECT pEffect)
{
	m_spMesh->Render(m_spGraphics, pEffect);

}

void CBronya_Grenade::PostRender(LPD3DXEFFECT pEffect)
{
	m_spMesh->PostRender(m_spGraphics, pEffect);

}

void CBronya_Grenade::OnDestroy()
{
	__super::OnDestroy();

}

void CBronya_Grenade::OnEnable()
{
	__super::OnEnable();

}

void CBronya_Grenade::OnDisable()
{
	__super::OnDisable();

}

void CBronya_Grenade::SetBasicName()
{
	m_name = m_objectKey + std::to_wstring(m_s_uniqueID++);
}
