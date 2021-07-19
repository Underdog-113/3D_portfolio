#include "stdafx.h"
#include "..\Header\Elevator_L_Door.h"

_uint CElevator_L_Door::m_s_uniqueID = 0;

CElevator_L_Door::CElevator_L_Door()
{
}


CElevator_L_Door::~CElevator_L_Door()
{
	OnDestroy();

}

SP(CElevator_L_Door) CElevator_L_Door::Create(_bool isStatic, Engine::CScene * pScene)
{
	SP(CElevator_L_Door) spInstance(new CElevator_L_Door, Engine::SmartDeleter<CElevator_L_Door>);
	spInstance->SetIsStatic(isStatic);
	spInstance->SetScene(pScene);
	spInstance->Awake();

	return spInstance;
}

SP(Engine::CObject) CElevator_L_Door::MakeClone(void)
{
	SP(CElevator_L_Door) spClone(new CElevator_L_Door, Engine::SmartDeleter<CElevator_L_Door>);
	__super::InitClone(spClone);

	spClone->m_spTransform = spClone->GetComponent<Engine::CTransformC>();
	spClone->m_spMesh = spClone->GetComponent<Engine::CMeshC>();
	spClone->m_spGraphics = spClone->GetComponent<Engine::CGraphicsC>();
	spClone->m_spTexture = spClone->GetComponent<Engine::CTextureC>();
	spClone->m_spShader = spClone->GetComponent<Engine::CShaderC>();

	return spClone;
}

void CElevator_L_Door::Awake(void)
{
	__super::Awake();

	m_addExtra = true;
	m_spMesh = AddComponent<Engine::CMeshC>();
	m_spMesh->SetInitTex(true);
	m_spMesh->SetMeshData(L"Elevator_L_Door");
	m_spGraphics = AddComponent<Engine::CGraphicsC>();
	m_spShader = AddComponent<Engine::CShaderC>();
	m_spShader->AddShader((_int)Engine::EShaderID::MeshShader);
	m_spTexture = AddComponent<Engine::CTextureC>();
}

void CElevator_L_Door::Start(void)
{
	__super::Start();

	m_spTransform->SetPosition(_float3(-0.7f, 0.48f, -1.88f));
	m_spGraphics->SetRenderID((_int)Engine::ERenderID::NonAlpha);
	m_bDoorCheck = false;

}

void CElevator_L_Door::FixedUpdate(void)
{
	__super::FixedUpdate();

}

void CElevator_L_Door::Update(void)
{
	__super::Update();

	if (m_bDoorCheck)
	{
		if (m_spTransform->GetPosition().y < 4.f)
		{
			m_spTransform->AddPositionY(2.5f * GET_DT);
		}
	}
}

void CElevator_L_Door::LateUpdate(void)
{
	__super::LateUpdate();

}

void CElevator_L_Door::PreRender(LPD3DXEFFECT pEffect)
{
	m_spMesh->PreRender(m_spGraphics, pEffect);
	pEffect->CommitChanges();
}

void CElevator_L_Door::Render(LPD3DXEFFECT pEffect)
{
	m_spMesh->Render(m_spGraphics, pEffect);

}

void CElevator_L_Door::PostRender(LPD3DXEFFECT pEffect)
{
	m_spMesh->PostRender(m_spGraphics, pEffect);

}

void CElevator_L_Door::OnDestroy(void)
{
	__super::OnDestroy();

}

void CElevator_L_Door::OnEnable(void)
{
	__super::OnEnable();

}

void CElevator_L_Door::OnDisable(void)
{
	__super::OnDisable();

}

void CElevator_L_Door::SetBasicName(void)
{
	m_name = m_objectKey + std::to_wstring(m_s_uniqueID++);

}
