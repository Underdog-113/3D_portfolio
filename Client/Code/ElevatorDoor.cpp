#include "stdafx.h"
#include "..\Header\ElevatorDoor.h"
#include "SoundManager.h"

_uint CElevatorDoor::m_s_uniqueID = 0;

CElevatorDoor::CElevatorDoor()
{
}


CElevatorDoor::~CElevatorDoor()
{
}

SP(CElevatorDoor) CElevatorDoor::Create(_bool isStatic, Engine::CScene * pScene)
{
	SP(CElevatorDoor) spInstance(new CElevatorDoor, Engine::SmartDeleter<CElevatorDoor>);
	spInstance->SetIsStatic(isStatic);
	spInstance->SetScene(pScene);
	spInstance->Awake();

	return spInstance;
}

SP(Engine::CObject) CElevatorDoor::MakeClone(void)
{
	SP(CElevatorDoor) spClone(new CElevatorDoor, Engine::SmartDeleter<CElevatorDoor>);
	__super::InitClone(spClone);


	spClone->m_spTransform = spClone->GetComponent<Engine::CTransformC>();
	spClone->m_spMesh = spClone->GetComponent<Engine::CMeshC>();
	spClone->m_spGraphics = spClone->GetComponent<Engine::CGraphicsC>();
	spClone->m_spTexture = spClone->GetComponent<Engine::CTextureC>();
	spClone->m_spShader = spClone->GetComponent<Engine::CShaderC>();

	return spClone;
}

void CElevatorDoor::Awake(void)
{
	__super::Awake();

	m_addExtra = true;

	m_spMesh = AddComponent<Engine::CMeshC>();
	m_spMesh->SetInitTex(true);
	m_spMesh->SetMeshData(L"Elevator_Door");
	m_spGraphics = AddComponent<Engine::CGraphicsC>();
	m_spShader = AddComponent<Engine::CShaderC>();
	m_spShader->AddShader((_int)Engine::EShaderID::MeshShader);
	m_spTexture = AddComponent<Engine::CTextureC>();
	m_spTransform->SetPositionY(-4.f);
	m_spTransform->SetPositionZ(0.6f);
	_uint a = m_spMesh->GetMeshData()->GetSubsetCount();

	for (_uint i = 0; i < m_spMesh->GetMeshData()->GetSubsetCount(); ++i)
	{
		m_spTexture->AddTexture(Engine::RemoveExtension(m_spMesh->GetMeshData()->GetTexList()[i]));
	}
}

void CElevatorDoor::Start(void)
{
	__super::Start();
	Engine::CSoundManager::GetInstance()->StopAll();
	Engine::CSoundManager::GetInstance()->StartSound(L"Elevator_OpenDoor.wav", (_uint)Engine::EChannelID::OUTGAME);

	m_bCheck = false;
	m_spGraphics->SetRenderID((_int)Engine::ERenderID::NonAlpha);
}

void CElevatorDoor::FixedUpdate(void)
{
	__super::FixedUpdate();

}

void CElevatorDoor::Update(void)
{
	__super::Update();

	if (!m_bCheck)
	{
		if (m_spTransform->GetPosition().y >= 0)
		{
			m_bCheck = true;
		}

		if (m_spTransform->GetPosition().y < 0)
		{
			m_spTransform->AddPositionY(3.5f * GET_DT);
		}
	}
}

void CElevatorDoor::LateUpdate(void)
{
	__super::LateUpdate();

}

void CElevatorDoor::PreRender(LPD3DXEFFECT pEffect)
{
	m_spMesh->PreRender(m_spGraphics, pEffect);
	pEffect->CommitChanges();
}

void CElevatorDoor::Render(LPD3DXEFFECT pEffect)
{
	m_spMesh->Render(m_spGraphics, pEffect);

}

void CElevatorDoor::PostRender(LPD3DXEFFECT pEffect)
{
	m_spMesh->PostRender(m_spGraphics, pEffect);

}

void CElevatorDoor::OnDestroy(void)
{
	__super::OnDestroy();

}

void CElevatorDoor::OnEnable(void)
{
	__super::OnEnable();

}

void CElevatorDoor::OnDisable(void)
{
	__super::OnDisable();

}

void CElevatorDoor::SetBasicName(void)
{
	m_name = m_objectKey + std::to_wstring(m_s_uniqueID++);

}
