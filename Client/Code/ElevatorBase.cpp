#include "stdafx.h"
#include "..\Header\ElevatorBase.h"
#include "ClientScene.h"

_uint CElevatorBase::m_s_uniqueID = 0;
CElevatorBase::CElevatorBase()
{
}


CElevatorBase::~CElevatorBase()
{
}

SP(CElevatorBase) CElevatorBase::Create(_bool isStatic, Engine::CScene * pScene)
{
	SP(CElevatorBase) spInstance(new CElevatorBase, Engine::SmartDeleter<CElevatorBase>);
	spInstance->SetIsStatic(isStatic);
	spInstance->SetScene(pScene);
	spInstance->Awake();

	return spInstance;
}

SP(Engine::CObject) CElevatorBase::MakeClone(void)
{
	SP(CElevatorBase) spClone(new CElevatorBase, Engine::SmartDeleter<CElevatorBase>);
	__super::InitClone(spClone);


	spClone->m_spTransform = spClone->GetComponent<Engine::CTransformC>();
	spClone->m_spMesh = spClone->GetComponent<Engine::CMeshC>();
	spClone->m_spGraphics = spClone->GetComponent<Engine::CGraphicsC>();
	spClone->m_spTexture = spClone->GetComponent<Engine::CTextureC>();
	spClone->m_spShader = spClone->GetComponent<Engine::CShaderC>();

	return spClone;
}

void CElevatorBase::Awake(void)
{
	__super::Awake();

	m_addExtra = true;

	m_spMesh = AddComponent<Engine::CMeshC>();
	m_spMesh->SetInitTex(true);
	m_spMesh->SetMeshData(L"Elevator_Base");
	m_spGraphics = AddComponent<Engine::CGraphicsC>();
	m_spShader = AddComponent<Engine::CShaderC>();
	m_spShader->AddShader((_int)Engine::EShaderID::MeshShader);
	m_spTexture = AddComponent<Engine::CTextureC>();

	for (_uint i = 0; i < m_spMesh->GetMeshData()->GetSubsetCount(); ++i)
	{
		m_spTexture->AddTexture(Engine::RemoveExtension(m_spMesh->GetMeshData()->GetTexList()[i]));
	}
}

void CElevatorBase::Start(void)
{
	__super::Start();

	if (Engine::GET_CUR_SCENE->GetSceneID() == (_int)ESceneID::MainRoom)
		m_spMesh->SetMeshData(L"Elevator_Base_2");


	m_spGraphics->SetRenderID((_int)Engine::ERenderID::NonAlpha);
}

void CElevatorBase::FixedUpdate(void)
{
	__super::FixedUpdate();

}

void CElevatorBase::Update(void)
{
	__super::Update();

	if (Engine::GET_CUR_SCENE->GetSceneID() == (_int)ESceneID::MainRoom)
	{
		m_spTexture->ChangeTexture(L"Elevator_Display03", 0, 2);
		m_spTexture->ChangeTexture(L"Elevator_Display03", 2, 0);

	}
	if (m_bLoadCheck && static_cast<Engine::CSlider*>(GET_CUR_CLIENT_SCENE->FindObjectByName(L"Slidr_0").get())->GetValue() == 100)
	{
		m_spTexture->ChangeTexture(L"Elevator_Display03", 0, 3);
		m_spTexture->ChangeTexture(L"Elevator_Display03", 3, 0);
		m_bLoadCheck = false;
	}
}

void CElevatorBase::LateUpdate(void)
{
	__super::LateUpdate();

}

void CElevatorBase::PreRender(LPD3DXEFFECT pEffect)
{
	m_spMesh->PreRender(m_spGraphics, pEffect);
	pEffect->CommitChanges();

}

void CElevatorBase::Render(LPD3DXEFFECT pEffect)
{
	m_spMesh->Render(m_spGraphics, pEffect);

}

void CElevatorBase::PostRender(LPD3DXEFFECT pEffect)
{
	m_spMesh->PostRender(m_spGraphics, pEffect);

}

void CElevatorBase::OnDestroy(void)
{
	__super::OnDestroy();

}

void CElevatorBase::OnEnable(void)
{
	__super::OnEnable();

}

void CElevatorBase::OnDisable(void)
{
	__super::OnDisable();

}

void CElevatorBase::SetBasicName(void)
{
	m_name = m_objectKey + std::to_wstring(m_s_uniqueID++);

}
