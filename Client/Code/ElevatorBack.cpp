#include "stdafx.h"
#include "..\Header\ElevatorBack.h"

_uint CElevatorBack::m_s_uniqueID = 0;

CElevatorBack::CElevatorBack()
{
}


CElevatorBack::~CElevatorBack()
{
	OnDestroy();
}

SP(CElevatorBack) CElevatorBack::Create(_bool isStatic, Engine::CScene * pScene)
{
	SP(CElevatorBack) spInstance(new CElevatorBack, Engine::SmartDeleter<CElevatorBack>);
	spInstance->SetIsStatic(isStatic);
	spInstance->SetScene(pScene);
	spInstance->Awake();

	return spInstance;
}

SP(Engine::CObject) CElevatorBack::MakeClone(void)
{
	SP(CElevatorBack) spClone(new CElevatorBack, Engine::SmartDeleter<CElevatorBack>);
	__super::InitClone(spClone);


	spClone->m_spTransform = spClone->GetComponent<Engine::CTransformC>();
	spClone->m_spMesh = spClone->GetComponent<Engine::CMeshC>();
	spClone->m_spGraphics = spClone->GetComponent<Engine::CGraphicsC>();
	spClone->m_spTexture = spClone->GetComponent<Engine::CTextureC>();
	spClone->m_spShader = spClone->GetComponent<Engine::CShaderC>();

	return spClone;
}

void CElevatorBack::Awake(void)
{
	__super::Awake();

	m_addExtra = true;

	m_spMesh = AddComponent<Engine::CMeshC>();
	m_spMesh->SetInitTex(true);
	m_spGraphics = AddComponent<Engine::CGraphicsC>();
	m_spShader = AddComponent<Engine::CShaderC>();
	m_spShader->AddShader((_int)Engine::EShaderID::MeshShader);
	m_spTexture = AddComponent<Engine::CTextureC>();
}

void CElevatorBack::Start(void)
{
	__super::Start();
	m_spGraphics->SetRenderID((_int)Engine::ERenderID::NonAlpha);
	m_TempPosY = m_spTransform->GetPosition().y;
	m_bSpawnCheck = false;
}

void CElevatorBack::FixedUpdate(void)
{
	__super::FixedUpdate();

}

void CElevatorBack::Update(void)
{
	__super::Update();

	if (m_spTransform->GetPosition().y + m_TempPosY >= -20.f)
	{
		m_spTransform->AddPositionY(-1.5f * GET_DT);
	}

	if (m_spTransform->GetPosition().y + m_TempPosY < -20.f)
	{
		this->SetDeleteThis(true);
	}

}

void CElevatorBack::LateUpdate(void)
{
	__super::LateUpdate();

}

void CElevatorBack::PreRender(LPD3DXEFFECT pEffect)
{
	m_spMesh->PreRender(m_spGraphics, pEffect);
	pEffect->CommitChanges();
}

void CElevatorBack::Render(LPD3DXEFFECT pEffect)
{
	m_spMesh->Render(m_spGraphics, pEffect);

}

void CElevatorBack::PostRender(LPD3DXEFFECT pEffect)
{
	m_spMesh->PostRender(m_spGraphics, pEffect);

}

void CElevatorBack::OnDestroy(void)
{
	__super::OnDestroy();

}

void CElevatorBack::OnEnable(void)
{
	__super::OnEnable();

}

void CElevatorBack::OnDisable(void)
{
	__super::OnDisable();

}

void CElevatorBack::SetBasicName(void)
{
	m_name = m_objectKey + std::to_wstring(m_s_uniqueID++);

}
