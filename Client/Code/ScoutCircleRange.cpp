#include "stdafx.h"
#include "..\Header\ScoutCircleRange.h"

#include "MO_Scout.h"

_uint CScoutCircleRange::m_s_uniqueID = 0;

CScoutCircleRange::CScoutCircleRange()
{
}


CScoutCircleRange::~CScoutCircleRange()
{
}

SP(CScoutCircleRange) CScoutCircleRange::Create(_bool isStatic, Engine::CScene * pScene)
{
	SP(CScoutCircleRange) spInstance(new CScoutCircleRange, Engine::SmartDeleter<CScoutCircleRange>);
	spInstance->SetIsStatic(isStatic);
	spInstance->SetScene(pScene);
	spInstance->Awake();

	return spInstance;
}

SP(Engine::CObject) CScoutCircleRange::MakeClone()
{
	SP(CScoutCircleRange) spClone(new CScoutCircleRange, Engine::SmartDeleter<CScoutCircleRange>);
	__super::InitClone(spClone);

	spClone->m_spTransform = spClone->GetComponent<Engine::CTransformC>();
	spClone->m_spTransform->SetSize(0.1f, 0.f, 0.1f);
	spClone->m_spMesh = spClone->GetComponent<Engine::CMeshC>();
	spClone->m_spGraphics = spClone->GetComponent<Engine::CGraphicsC>();
	spClone->m_spTexture = spClone->GetComponent<Engine::CTextureC>();
	spClone->m_spShader = spClone->GetComponent<Engine::CShaderC>();

	return spClone;
}

void CScoutCircleRange::Awake()
{
	__super::Awake();

}

void CScoutCircleRange::Start()
{
	__super::Start();
	m_fTime = 0.f;
	m_fAlpha = 0.3f;
}

void CScoutCircleRange::FixedUpdate()
{
	__super::FixedUpdate();

}

void CScoutCircleRange::Update()
{
	__super::Update();
	//if (!m_bSpawn)
		m_fTime += GET_DT;

	if (!m_bSpawn && m_fTime >= 3.f)
	{
		m_spScoutMeteor = Engine::GET_CUR_SCENE->GetObjectFactory()->AddClone(L"ScoutMeteor", true);

		_float3 pos = this->GetTransform()->GetPosition();
		m_spScoutMeteor->GetTransform()->SetPositionX(pos.x);
		m_spScoutMeteor->GetTransform()->SetPositionZ(pos.z);
		m_bSpawn = true;
	}

	if (m_bSpawn && m_fTime >= 3.5f)
	{
		// active attackball
		static_cast<CMO_Scout*>(m_pBallShooter)->ActiveAttackBall(1.f, HitInfo::Str_Low, HitInfo::CC_None, &m_atkMat, 0.48f);
		m_fTime = 0.f;
	}
	else if (m_bSpawn && m_spScoutMeteor->GetDeleteThis())
	{
		// sound
		Engine::CSoundManager::GetInstance()->StopSound((_uint)m_channelID);
		Engine::CSoundManager::GetInstance()->StartSound(L"Scout_UpAttack_2.wav", (_uint)m_channelID);

		// unactive attackball
		static_cast<CMO_Scout*>(m_pBallShooter)->UnActiveAttackBall();
		this->SetDeleteThis(true);
	}

	m_fSize += 0.01f * GET_DT;

	this->GetTransform()->SetSize(_float3(m_fSize, 0.f, m_fSize));
}

void CScoutCircleRange::LateUpdate()
{
	__super::LateUpdate();

}

void CScoutCircleRange::PreRender(LPD3DXEFFECT pEffect)
{
	m_spMesh->PreRender(m_spGraphics, pEffect);
	pEffect->SetFloat("gAlpha", m_fAlpha);
}

void CScoutCircleRange::Render(LPD3DXEFFECT pEffect)
{
	m_spMesh->Render(m_spGraphics, pEffect);
}

void CScoutCircleRange::PostRender(LPD3DXEFFECT pEffect)
{
	m_spMesh->PostRender(m_spGraphics, pEffect);
}

void CScoutCircleRange::OnDestroy()
{
	__super::OnDestroy();
}

void CScoutCircleRange::OnEnable()
{
	__super::OnEnable();
}

void CScoutCircleRange::OnDisable()
{
	__super::OnDisable();
}

void CScoutCircleRange::SetBasicName()
{
	m_name = m_objectKey + std::to_wstring(m_s_uniqueID++);
}
