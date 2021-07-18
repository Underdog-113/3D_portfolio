#include "stdafx.h"
#include "..\Header\Kiana_WSkill_Circle.h"

// 생성할 때 플레이어가 바라보는 방향으로 회전시켜줘야댐

CKiana_WSkill_Circle::CKiana_WSkill_Circle()
{
}


CKiana_WSkill_Circle::~CKiana_WSkill_Circle()
{
}

SP(CKiana_WSkill_Circle) CKiana_WSkill_Circle::Create(_bool isStatic, Engine::CScene * pScene)
{
	SP(CKiana_WSkill_Circle) spInstance(new CKiana_WSkill_Circle, Engine::SmartDeleter<CKiana_WSkill_Circle>);
	spInstance->SetIsStatic(isStatic);
	spInstance->SetScene(pScene);
	spInstance->Awake();

	return spInstance;
}

SP(Engine::CObject) CKiana_WSkill_Circle::MakeClone()
{
	SP(CKiana_WSkill_Circle) spClone(new CKiana_WSkill_Circle, Engine::SmartDeleter<CKiana_WSkill_Circle>);
	__super::InitClone(spClone);

	spClone->m_spTransform = spClone->GetComponent<Engine::CTransformC>();
	spClone->m_spMesh = spClone->GetComponent<Engine::CMeshC>();
	spClone->m_spGraphics = spClone->GetComponent<Engine::CGraphicsC>();
	spClone->m_spTexture = spClone->GetComponent<Engine::CTextureC>();
	spClone->m_spShader = spClone->GetComponent<Engine::CShaderC>();

	return spClone;
}

void CKiana_WSkill_Circle::Awake()
{
	__super::Awake();
	_float _size = 0.01f;
	m_spTransform->SetSize(_float3(_size, _size, _size));
	m_spMesh->SetMeshData(L"Wall_barrier");
	m_spMesh->SetIsEffectMesh(true);
	m_spGraphics->SetRenderID((_int)Engine::ERenderID::AlphaBlend);
	m_spTexture->AddTexture(L"K_TrailTex");
	m_spTexture->AddTexture(L"Kiana_WSkill");
	m_spShader->AddShader((_int)EShaderID::AlphaMaskShader);
}

void CKiana_WSkill_Circle::Start()
{
	__super::Start();
	m_fAlpha = 1.f;
	m_bCheck = false;
}

void CKiana_WSkill_Circle::FixedUpdate()
{
	__super::FixedUpdate();

}

void CKiana_WSkill_Circle::Update()
{
	__super::Update();

	if (m_spTransform->GetSize().x < 0.05f)
	{
		_float _size = 0.5f * GET_PLAYER_DT;
		m_spTransform->AddSize(_float3(_size, _size, _size));
	}
	if (m_spTransform->GetSize().x >= 0.05f)
	{
		m_bCheck = true;
	}

	if (m_bCheck)
	{
		m_fAlpha -= 0.7f * GET_PLAYER_DT;

		if (m_fAlpha <= 0.f)
		{
			this->SetDeleteThis(true);
		}
	}


}

void CKiana_WSkill_Circle::LateUpdate()
{
	__super::LateUpdate();

}

void CKiana_WSkill_Circle::PreRender(LPD3DXEFFECT pEffect)
{
	m_spMesh->PreRender(m_spGraphics, pEffect);
	pEffect->SetFloat("gAlpha", m_fAlpha);
}

void CKiana_WSkill_Circle::Render(LPD3DXEFFECT pEffect)
{
	m_spMesh->Render(m_spGraphics, pEffect);

}

void CKiana_WSkill_Circle::PostRender(LPD3DXEFFECT pEffect)
{
	m_spMesh->PostRender(m_spGraphics, pEffect);

}

void CKiana_WSkill_Circle::OnDestroy()
{
	__super::OnDestroy();

}

void CKiana_WSkill_Circle::OnEnable()
{
	__super::OnEnable();

}

void CKiana_WSkill_Circle::OnDisable()
{
	__super::OnDisable();

}

void CKiana_WSkill_Circle::SetBasicName()
{
}
