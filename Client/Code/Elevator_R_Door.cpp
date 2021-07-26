#include "stdafx.h"
#include "..\Header\Elevator_R_Door.h"
#include "SoundManager.h"
#include "ClientScene.h"

_uint CElevator_R_Door::m_s_uniqueID = 0;

CElevator_R_Door::CElevator_R_Door()
{
}


CElevator_R_Door::~CElevator_R_Door()
{
	OnDestroy();
}

SP(CElevator_R_Door) CElevator_R_Door::Create(_bool isStatic, Engine::CScene * pScene)
{
	SP(CElevator_R_Door) spInstance(new CElevator_R_Door, Engine::SmartDeleter<CElevator_R_Door>);
	spInstance->SetIsStatic(isStatic);
	spInstance->SetScene(pScene);
	spInstance->Awake();

	return spInstance;
}

SP(Engine::CObject) CElevator_R_Door::MakeClone(void)
{
	SP(CElevator_R_Door) spClone(new CElevator_R_Door, Engine::SmartDeleter<CElevator_R_Door>);
	__super::InitClone(spClone);

	spClone->m_spTransform = spClone->GetComponent<Engine::CTransformC>();
	spClone->m_spMesh = spClone->GetComponent<Engine::CMeshC>();
	spClone->m_spGraphics = spClone->GetComponent<Engine::CGraphicsC>();
	spClone->m_spTexture = spClone->GetComponent<Engine::CTextureC>();
	spClone->m_spShader = spClone->GetComponent<Engine::CShaderC>();

	return spClone;
}

void CElevator_R_Door::Awake(void)
{
	__super::Awake();

	m_addExtra = true;

	m_spMesh = AddComponent<Engine::CMeshC>();
	m_spMesh->SetInitTex(true);
	m_spMesh->SetMeshData(L"Elevator_R_Door");
	m_spGraphics = AddComponent<Engine::CGraphicsC>();
	m_spShader = AddComponent<Engine::CShaderC>();
	m_spShader->AddShader((_int)Engine::EShaderID::MeshShader);
	m_spTexture = AddComponent<Engine::CTextureC>();
}

void CElevator_R_Door::Start(void)
{
	__super::Start();

	m_spTransform->SetPosition(_float3(-0.3f, -0.61f, -1.8f));

	m_spGraphics->SetRenderID((_int)Engine::ERenderID::NonAlpha);

	Engine::CSoundManager::GetInstance()->StopSound((_uint)Engine::EChannelID::OUTGAME);
	Engine::CSoundManager::GetInstance()->StartSound(L"Elevator_CameraRun.wav", (_uint)Engine::EChannelID::OUTGAME);
	m_bDoorCheck = false;
}

void CElevator_R_Door::FixedUpdate(void)
{
	__super::FixedUpdate();

}

void CElevator_R_Door::Update(void)
{
	__super::Update();

	if (m_bDoorCheck)
	{
		if (m_spTransform->GetPosition().y > -4.f)
		{
			m_spTransform->AddPositionY(-2.5f *GET_DT);
		}

		if (m_spTransform->GetPosition().y <= -4.f)
		{
			SP(Engine::CCamera) spCam = Engine::CCameraManager::GetInstance()->GetCamera(Engine::GET_CUR_SCENE->GetObjectKey() + L"BasicCamera");
			if (spCam->GetTransform()->GetPosition().z < -3.8f)
			{
				m_rotateLerpTimer += GET_DT;
				float inverseRate = 1.f - m_rotateLerpTimer;
				float sLerpTimer = 1.f - inverseRate * inverseRate;

				_float lerpPoint = GetLerpFloat(m_camStartZ, m_camEndZ, sLerpTimer);

				spCam->GetTransform()->SetPositionZ(lerpPoint);
			}

			if (spCam->GetTransform()->GetPosition().z >= -3.8f)
			{
				static_cast<Engine::CCanvas*>(GET_CUR_CLIENT_SCENE->FindObjectByName(L"MainCanvas").get())->SetIsEnabled(true);
				m_bDoorCheck = false;
			}
		}

	}
}



void CElevator_R_Door::LateUpdate(void)
{
	__super::LateUpdate();

}

void CElevator_R_Door::PreRender(LPD3DXEFFECT pEffect)
{
	m_spMesh->PreRender(m_spGraphics, pEffect);
	pEffect->CommitChanges();
}

void CElevator_R_Door::Render(LPD3DXEFFECT pEffect)
{
	m_spMesh->Render(m_spGraphics, pEffect);

}

void CElevator_R_Door::PostRender(LPD3DXEFFECT pEffect)
{
	m_spMesh->PostRender(m_spGraphics, pEffect);

}

void CElevator_R_Door::OnDestroy(void)
{
	__super::OnDestroy();

}

void CElevator_R_Door::OnEnable(void)
{
	__super::OnEnable();

}

void CElevator_R_Door::OnDisable(void)
{
	__super::OnDisable();

}

void CElevator_R_Door::SetBasicName(void)
{
	m_name = m_objectKey + std::to_wstring(m_s_uniqueID++);

}
