#include "stdafx.h"
#include "..\Header\ElevatorDoor.h"
#include "SoundManager.h"
#include "Elevator_L_Door.h"
#include "Elevator_R_Door.h"

#include "CameraShake.h"

_uint CElevatorDoor::m_s_uniqueID = 0;

CElevatorDoor::CElevatorDoor()
{
}


CElevatorDoor::~CElevatorDoor()
{
	SAFE_DELETE(m_shake);
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


	if (Engine::GET_CUR_SCENE->GetSceneID() == (_int)ESceneID::MainRoom)
	{
		m_sp_L_Door = Engine::GET_CUR_SCENE->ADD_CLONE(L"Elevator_L_Door", true, (_int)Engine::ELayerID::Decoration);
		m_sp_R_Door = Engine::GET_CUR_SCENE->ADD_CLONE(L"Elevator_R_Door", true, (_int)Engine::ELayerID::Decoration);

		m_sp_R_Door->GetTransform()->SetOwner(this);

		m_spTransform->SetPositionZ(-2.4f);
		m_spTransform->SetPositionY(-0.8f);
		m_spTransform->AddPositionX(-0.4f);

		m_spMesh->SetMeshData(L"Elevator_Door_2");
		Engine::CSoundManager::GetInstance()->StopSound((_uint)Engine::EChannelID::OUTGAME);
		Engine::CSoundManager::GetInstance()->StartSound(L"Elevator_OpenDoor.wav", (_uint)Engine::EChannelID::OUTGAME);



		m_shake = new CCameraShake;		
		m_shake->SetCamera(Engine::GET_MAIN_CAM);;

		auto camTr = Engine::GET_MAIN_CAM->GetTransform();
		m_noShakePos = camTr->GetPosition();
		m_noShakeRot = camTr->GetRotation();
	}
	else
	{
		Engine::CSoundManager::GetInstance()->StopSound((_uint)Engine::EChannelID::OUTGAME);
		Engine::CSoundManager::GetInstance()->StartSound(L"Elevator_OpenDoor.wav", (_uint)Engine::EChannelID::OUTGAME);
	}

	m_bMoveCheck = false;
	m_fTimer = 0.f;
	m_spGraphics->SetRenderID((_int)Engine::ERenderID::NonAlpha);


	m_isShaked = false;
}

void CElevatorDoor::FixedUpdate(void)
{
	__super::FixedUpdate();

}

void CElevatorDoor::Update(void)
{
	__super::Update();

	if (m_isShaked)
	{
		ReturnBeforShaking();
		ApplyShaking();
	}

	if (Engine::GET_CUR_SCENE->GetSceneID() == (_int)ESceneID::MainRoom)
	{ 
		if (!m_bMoveCheck)
		{
			if (m_spTransform->GetPosition().y <= -6)
			{
				std::static_pointer_cast<CElevator_L_Door>(m_sp_L_Door)->SetDoorCheck(true);
				std::static_pointer_cast<CElevator_R_Door>(m_sp_R_Door)->SetDoorCheck(true);
				m_bMoveCheck = true;
			}

			if (m_spTransform->GetPosition().y > -6)
			{
				m_spTransform->AddPositionY(-5.5f * GET_DT);
			}
		}

		if (!m_isShaked)
		{
			m_shake->Preset_Elevator();

			m_isShaked = true;
		}

	}
	else
	{
		if (!m_bMoveCheck)
		{
			if (m_spTransform->GetPosition().y >= 0)
			{
				m_bMoveCheck = true;
			}

			if (m_spTransform->GetPosition().y < 0)
			{
				m_spTransform->AddPositionY(3.5f * GET_DT);
			}
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

void CElevatorDoor::ReturnBeforShaking()
{
	auto camTr = Engine::GET_MAIN_CAM->GetTransform();

	if (m_shake->IsShaking())
	{
		camTr->SetPosition(m_noShakePos);
		camTr->SetRotation(m_noShakeRot);
	}
}

void CElevatorDoor::ApplyShaking()
{
	auto mainCam = Engine::GET_MAIN_CAM;
	auto camTr = mainCam->GetTransform();

	if (m_shake->IsShaking())
	{
		m_shake->PlayShake_Pure();

		m_noShakePos = camTr->GetPosition();
		m_noShakeRot = camTr->GetRotation();	// 회전값 기억

		_float3 locOscilation = m_shake->GetLocationOscilation();
		_float3 rotOscilation = m_shake->GetRotateOscilation();
		camTr->AddPosition(locOscilation);
		camTr->AddRotation(rotOscilation);
	}
	else
	{
		m_noShakePos = camTr->GetPosition();
		m_noShakeRot = camTr->GetRotation();
	}
}
