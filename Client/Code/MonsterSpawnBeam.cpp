#include "stdafx.h"
#include "..\Header\MonsterSpawnBeam.h"
#include "Monster.h"
#include "SoundManager.h"

CMonsterSpawnBeam::CMonsterSpawnBeam()
{
}


CMonsterSpawnBeam::~CMonsterSpawnBeam()
{
}

SP(CMonsterSpawnBeam) CMonsterSpawnBeam::Create(_bool isStatic, Engine::CScene * pScene)
{
	SP(CMonsterSpawnBeam) spInstance(new CMonsterSpawnBeam, Engine::SmartDeleter<CMonsterSpawnBeam>);
	spInstance->SetIsStatic(isStatic);
	spInstance->SetScene(pScene);
	spInstance->Awake();

	return spInstance;
}

SP(Engine::CObject) CMonsterSpawnBeam::MakeClone()
{
	SP(CMonsterSpawnBeam) spClone(new CMonsterSpawnBeam, Engine::SmartDeleter<CMonsterSpawnBeam>);
	__super::InitClone(spClone);

	spClone->m_spTransform = spClone->GetComponent<Engine::CTransformC>();
	spClone->m_spMesh = spClone->GetComponent<Engine::CMeshC>();
	spClone->m_spGraphics = spClone->GetComponent<Engine::CGraphicsC>();
	spClone->m_spTexture = spClone->GetComponent<Engine::CTextureC>();
	spClone->m_spShader = spClone->GetComponent<Engine::CShaderC>();
	spClone->m_spCollision = spClone->GetComponent<Engine::CCollisionC>();
	return spClone;
}

void CMonsterSpawnBeam::Awake()
{
	__super::Awake();
	m_spMesh->SetMeshData(L"SpawnBeam");
	m_spGraphics->SetRenderID((_int)Engine::ERenderID::Effect);
	m_spTexture->AddTexture(L"Portal_beam_4");
	m_spTexture->AddTexture(L"Portal_beam_4");
	m_spTexture->AddTexture(L"Portal_beam_4");
	m_spShader->AddShader((_int)EShaderID::AlphaMaskGlowShader);
	m_spCollision = AddComponent<Engine::CCollisionC>();
	m_spCollision->
		AddCollider(Engine::CRayCollider::Create((_int)ECollisionID::FloorRay, _float3(0, 0, 0), _float3(0, 0, 1), 2.5f));
	m_spTransform->SetRotationX(D3DXToRadian(90.f));

}

void CMonsterSpawnBeam::Start()
{
	__super::Start();

	AddComponent<Engine::CDebugC>();
	Engine::CSoundManager::GetInstance()->StopSound((_uint)EChannelID::MONSTER_SPAWN);
	Engine::CSoundManager::GetInstance()->StartSound(L"Spawn.wav",(_uint)EChannelID::MONSTER_SPAWN);
	Engine::CSoundManager::GetInstance()->SetVolume((_uint)EChannelID::MONSTER_SPAWN, 0.5f);
	m_bSpawn = false;
	m_fAlpha = 1.f;
}

void CMonsterSpawnBeam::FixedUpdate()
{
	__super::FixedUpdate();
}

void CMonsterSpawnBeam::Update()
{
	__super::Update();

	if (m_bSpawn)
	{
		m_fAlpha -= 1.f * GET_DT;

		if (m_fAlpha <= 0)
		{
			this->SetDeleteThis(true);
		}
	}		

	m_spTransform->AddPositionY(-10.f * GET_DT);
}

void CMonsterSpawnBeam::LateUpdate()
{
	__super::LateUpdate();
}

void CMonsterSpawnBeam::PreRender(LPD3DXEFFECT pEffect)
{
	m_spMesh->PreRender(m_spGraphics, pEffect);
	pEffect->SetFloat("gAlpha", m_fAlpha);
}

void CMonsterSpawnBeam::Render(LPD3DXEFFECT pEffect)
{
	m_spMesh->Render(m_spGraphics, pEffect);
}

void CMonsterSpawnBeam::PostRender(LPD3DXEFFECT pEffect)
{
	m_spMesh->PostRender(m_spGraphics, pEffect);
}

void CMonsterSpawnBeam::OnDestroy()
{
	__super::OnDestroy();
	m_fAlpha = 0.f;
}

void CMonsterSpawnBeam::OnEnable()
{
	__super::OnEnable();
}

void CMonsterSpawnBeam::OnDisable()
{
	__super::OnDisable();
}

void CMonsterSpawnBeam::OnCollisionEnter(Engine::_CollisionInfo ci)
{
	SP(Engine::CObject) spMeshEffect
		= Engine::GET_CUR_SCENE->GetObjectFactory()->AddClone(L"MonsterSpawnEff", true, (_int)Engine::ELayerID::Effect, L"MeshEffect0");

	spMeshEffect->GetTransform()->SetPosition(ci.hitPoint);
	m_spMonster->SetIsEnabled(true);

	m_bSpawn = true;

}

void CMonsterSpawnBeam::OnCollisionStay(Engine::_CollisionInfo ci)
{
}

void CMonsterSpawnBeam::OnCollisionExit(Engine::_CollisionInfo ci)
{
}

void CMonsterSpawnBeam::SetBasicName()
{
}
