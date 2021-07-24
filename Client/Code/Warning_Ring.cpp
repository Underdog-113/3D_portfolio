#include "stdafx.h"
#include "..\Header\Warning_Ring.h"

_uint CWarning_Ring::m_s_uniqueID = 0;

CWarning_Ring::CWarning_Ring()
{
}


CWarning_Ring::~CWarning_Ring()
{
}

SP(CWarning_Ring) CWarning_Ring::Create(_bool isStatic, Engine::CScene * pScene)
{
	SP(CWarning_Ring) spInstance(new CWarning_Ring, Engine::SmartDeleter<CWarning_Ring>);
	spInstance->SetIsStatic(isStatic);
	spInstance->SetScene(pScene);
	spInstance->Awake();

	return spInstance;
}

SP(Engine::CObject) CWarning_Ring::MakeClone()
{
	SP(CWarning_Ring) spClone(new CWarning_Ring, Engine::SmartDeleter<CWarning_Ring>);
	__super::InitClone(spClone);

	spClone->m_spTransform = spClone->GetComponent<Engine::CTransformC>();
	spClone->m_spMesh = spClone->GetComponent<Engine::CMeshC>();
	spClone->m_spGraphics = spClone->GetComponent<Engine::CGraphicsC>();
	spClone->m_spShader = spClone->GetComponent<Engine::CShaderC>();
	spClone->m_spTexture = spClone->GetComponent<Engine::CTextureC>();

	return spClone;
}

void CWarning_Ring::Awake()
{
	__super::Awake();
	m_spMesh->SetMeshData(L"Warning_Ring");
	m_spMesh->SetIsEffectMesh(true);
	m_spGraphics->SetRenderID((_int)Engine::ERenderID::AlphaBlend);
	m_spTexture->AddTexture(L"Warning_2");
	m_spTexture->AddTexture(L"Sign");
	m_spShader->AddShader((_int)EShaderID::AlphaMaskShader);
	m_spTransform->SetSizeY(0.f);

}

void CWarning_Ring::Start()
{
	__super::Start();
	Engine::CSoundManager::GetInstance()->StopSound((_uint)EChannelID::WARNING);
	Engine::CSoundManager::GetInstance()->StartSound(L"Warning_Start.wav", (_uint)EChannelID::WARNING);
	m_fAlpha = 1.f;
	m_fUVSpeed = 0.f;
	m_isSpawn = false;
	m_fTime = 0.f;
}

void CWarning_Ring::FixedUpdate()
{
	__super::FixedUpdate();

}

void CWarning_Ring::Update()
{
	__super::Update();

	if(!m_isSpawn)
	{
		m_fTime += GET_DT;
		if (m_fTime >= 0.5f)
		{
			Engine::CSoundManager::GetInstance()->StopSound((_uint)EChannelID::WARNING);
			Engine::CSoundManager::GetInstance()->StartSound(L"Warning_Loop.wav", (_uint)EChannelID::WARNING);
			m_isSpawn = true;
			m_fTime = 0.f;
		}
	}

	_bool bCheck = Engine::CSoundManager::GetInstance()->IsPlaying((_uint)EChannelID::WARNING);

	if (m_isSpawn)
	{
		m_fTime += GET_DT;

		if (m_fTime >= 2.f)
		{
			if (m_spTransform->GetSize().y > 0)
			{
				m_spTransform->AddSizeY(-3.5f * GET_DT);
			}
			else if (m_spTransform->GetSize().y <= 0)
			{
				this->SetDeleteThis(true);
			}
		}
	}
	else
	{
		if (m_spTransform->GetSize().y < 1)
		{
			m_spTransform->AddSizeY(3.5f * GET_DT);
		}
	}

	m_fUVSpeed += 0.3f * GET_DT;

}

void CWarning_Ring::LateUpdate()
{
	__super::LateUpdate();

}

void CWarning_Ring::PreRender(LPD3DXEFFECT pEffect)
{
	m_spMesh->PreRender(m_spGraphics, pEffect);
	pEffect->SetFloat("gAlpha", m_fAlpha);
	pEffect->SetFloat("gSpeed", m_fUVSpeed);
	pEffect->SetBool("gPlayingAnim", true);
	pEffect->SetBool("g_zWriteEnabled", true);

	pEffect->CommitChanges();
}

void CWarning_Ring::Render(LPD3DXEFFECT pEffect)
{
	m_spMesh->Render(m_spGraphics, pEffect);

}

void CWarning_Ring::PostRender(LPD3DXEFFECT pEffect)
{
	m_spMesh->PostRender(m_spGraphics, pEffect);

}

void CWarning_Ring::OnDestroy()
{
	__super::OnDestroy();

}

void CWarning_Ring::OnEnable()
{
	__super::OnEnable();

}

void CWarning_Ring::OnDisable()
{
	__super::OnDisable();

}

void CWarning_Ring::SetBasicName()
{
	m_name = m_objectKey + std::to_wstring(m_s_uniqueID++);

}
