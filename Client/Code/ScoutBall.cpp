#include "stdafx.h"
#include "..\Header\ScoutBall.h"

_uint CScoutBall::m_s_uniqueID = 0;

CScoutBall::CScoutBall()
{
}


CScoutBall::~CScoutBall()
{
}

SP(CScoutBall) CScoutBall::Create(_bool isStatic, Engine::CScene * pScene)
{
	SP(CScoutBall) spInstance(new CScoutBall, Engine::SmartDeleter<CScoutBall>);
	spInstance->SetIsStatic(isStatic);
	spInstance->SetScene(pScene);
	spInstance->Awake();

	return spInstance;
}

SP(Engine::CObject) CScoutBall::MakeClone()
{
	SP(CScoutBall) spClone(new CScoutBall, Engine::SmartDeleter<CScoutBall>);
	__super::InitClone(spClone);

	_float tmpSize = 0.03f;
	spClone->m_spTransform = spClone->GetComponent<Engine::CTransformC>();
	spClone->m_spTransform->SetSize(_float3(tmpSize, tmpSize, tmpSize));
	spClone->m_spMesh = spClone->GetComponent<Engine::CMeshC>();
	spClone->m_spGraphics = spClone->GetComponent<Engine::CGraphicsC>();
	spClone->m_spTexture = spClone->GetComponent<Engine::CTextureC>();
	spClone->m_spShader = spClone->GetComponent<Engine::CShaderC>();

	return spClone;
}

void CScoutBall::Awake()
{
	__super::Awake();
	m_spMesh->SetMeshData(L"Scout_Ball");
	m_spGraphics->SetRenderID((_int)Engine::ERenderID::Effect);
	m_spTexture->AddTexture(L"BallColor");
	m_spTexture->AddTexture(L"BallColor");
	m_spShader->AddShader((_int)EShaderID::AlphaMaskGlowShader);
}

void CScoutBall::Start()
{
	__super::Start();
	m_fAlpha = 0.3f;
}

void CScoutBall::FixedUpdate()
{
	__super::FixedUpdate();

}

void CScoutBall::Update()
{
	__super::Update();

	_float size = 0.f;
	if (m_bFlyingBall)
	{
		if (m_spTransform->GetSize().z >= 0.1f)
		{
			this->SetDeleteThis(true);
		}

		size = 0.049f /*0.033f*/ * GET_DT;
	}
	else
	{
		if (m_spTransform->GetSize().z >= 0.1f)
		{
			this->SetDeleteThis(true);
		}

	   size = 0.033f * GET_DT;
	}
	
	
	m_spTransform->AddSize(_float3(size, size, size));

	if (m_ready)
		m_spTransform->AddPosition(m_direction * GET_DT);
}

void CScoutBall::LateUpdate()
{
	__super::LateUpdate();

}

void CScoutBall::PreRender(LPD3DXEFFECT pEffect)
{
	m_spMesh->PreRender(m_spGraphics, pEffect);
	pEffect->SetFloat("gAlpha", m_fAlpha);
	pEffect->SetBool("g_bAlphaCtrl", false);
}

void CScoutBall::Render(LPD3DXEFFECT pEffect)
{
	m_spMesh->Render(m_spGraphics, pEffect);

}

void CScoutBall::PostRender(LPD3DXEFFECT pEffect)
{
	m_spMesh->PostRender(m_spGraphics, pEffect);

}

void CScoutBall::OnDestroy()
{
	__super::OnDestroy();
}

void CScoutBall::OnEnable()
{
	__super::OnEnable();

}

void CScoutBall::OnDisable()
{
	__super::OnDisable();
}

void CScoutBall::SetBasicName()
{
	m_name = m_objectKey + std::to_wstring(m_s_uniqueID++);
}
