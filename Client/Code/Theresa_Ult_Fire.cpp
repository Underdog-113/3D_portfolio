#include "stdafx.h"
#include "..\Header\Theresa_Ult_Fire.h"

_uint CTheresa_Ult_Fire::m_s_uniqueID = 0;

CTheresa_Ult_Fire::CTheresa_Ult_Fire()
{
}


CTheresa_Ult_Fire::~CTheresa_Ult_Fire()
{
}

SP(CTheresa_Ult_Fire) CTheresa_Ult_Fire::Create(_bool isStatic, Engine::CScene * pScene)
{
	SP(CTheresa_Ult_Fire) spInstance(new CTheresa_Ult_Fire, Engine::SmartDeleter<CTheresa_Ult_Fire>);
	spInstance->SetIsStatic(isStatic);
	spInstance->SetScene(pScene);
	spInstance->Awake();

	return spInstance;
}

SP(Engine::CObject) CTheresa_Ult_Fire::MakeClone()
{
	SP(CTheresa_Ult_Fire) spClone(new CTheresa_Ult_Fire, Engine::SmartDeleter<CTheresa_Ult_Fire>);

	__super::InitClone(spClone);

	spClone->m_spTransform = spClone->GetComponent<Engine::CTransformC>();
	m_spTransform->SetSizeY(2.f);

	spClone->m_spMesh = spClone->GetComponent<Engine::CMeshC>();
	spClone->m_spGraphics = spClone->GetComponent<Engine::CGraphicsC>();
	spClone->m_spShader = spClone->GetComponent<Engine::CShaderC>();
	spClone->m_spTexture = spClone->GetComponent<Engine::CTextureC>();

	return spClone;
}

void CTheresa_Ult_Fire::Awake()
{
	__super::Awake();
}

void CTheresa_Ult_Fire::Start()
{
	__super::Start();
	m_fUVSpeed = 0.f;
	m_fAlpha = 1.f;
}

void CTheresa_Ult_Fire::FixedUpdate()
{
	__super::FixedUpdate();
}

void CTheresa_Ult_Fire::Update()
{
	__super::Update();

	if (m_fAlpha <= 0)
	{
		this->SetDeleteThis(true);
	}

	m_spTransform->AddSizeY(3 * GET_PLAYER_DT);

	m_fAlpha -= 0.5f * GET_PLAYER_DT;
	m_fUVSpeed += GET_PLAYER_DT;
}

void CTheresa_Ult_Fire::LateUpdate()
{
	__super::LateUpdate();
}

void CTheresa_Ult_Fire::PreRender(LPD3DXEFFECT pEffect)
{
	m_spMesh->PreRender(m_spGraphics, pEffect);
	pEffect->SetFloat("gAlpha", m_fAlpha);
	pEffect->SetFloat("gSpeed", m_fUVSpeed);

}

void CTheresa_Ult_Fire::Render(LPD3DXEFFECT pEffect)
{
	m_spMesh->Render(m_spGraphics, pEffect);
}

void CTheresa_Ult_Fire::PostRender(LPD3DXEFFECT pEffect)
{
	m_spMesh->PostRender(m_spGraphics, pEffect);
}

void CTheresa_Ult_Fire::OnDestroy()
{
	__super::OnDestroy();
}

void CTheresa_Ult_Fire::OnEnable()
{
	__super::OnEnable();
}

void CTheresa_Ult_Fire::OnDisable()
{
	__super::OnDisable();
}

void CTheresa_Ult_Fire::SetBasicName()
{
	m_name = m_objectKey + std::to_wstring(m_s_uniqueID++);
}
