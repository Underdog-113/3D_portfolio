#include "stdafx.h"
#include "..\Header\Theresa_Ult_Crack.h"

_uint CTheresa_Ult_Crack::m_s_uniqueID = 0;

CTheresa_Ult_Crack::CTheresa_Ult_Crack()
{
}


CTheresa_Ult_Crack::~CTheresa_Ult_Crack()
{
}

SP(CTheresa_Ult_Crack) CTheresa_Ult_Crack::Create(_bool isStatic, Engine::CScene * pScene)
{

	SP(CTheresa_Ult_Crack) spInstance(new CTheresa_Ult_Crack, Engine::SmartDeleter<CTheresa_Ult_Crack>);
	spInstance->SetIsStatic(isStatic);
	spInstance->SetScene(pScene);
	spInstance->Awake();

	return spInstance;
}

SP(Engine::CObject) CTheresa_Ult_Crack::MakeClone()
{
	SP(CTheresa_Ult_Crack) spClone(new CTheresa_Ult_Crack, Engine::SmartDeleter<CTheresa_Ult_Crack>);

	__super::InitClone(spClone);

	spClone->m_spTransform = spClone->GetComponent<Engine::CTransformC>();
	m_spTransform->SetSizeY(0.f);

	spClone->m_spMesh = spClone->GetComponent<Engine::CMeshC>();
	spClone->m_spGraphics = spClone->GetComponent<Engine::CGraphicsC>();
	spClone->m_spShader = spClone->GetComponent<Engine::CShaderC>();
	spClone->m_spTexture = spClone->GetComponent<Engine::CTextureC>();

	return spClone;
}

void CTheresa_Ult_Crack::Awake()
{
	__super::Awake();

}

void CTheresa_Ult_Crack::Start()
{
	__super::Start();
	m_fAlpha = 1.f;
}

void CTheresa_Ult_Crack::FixedUpdate()
{
	__super::FixedUpdate();

}

void CTheresa_Ult_Crack::Update()
{
	__super::Update();

	if (m_fAlpha <= 0)
	{
		this->SetDeleteThis(true);
	}

	m_fAlpha -= 0.5f * GET_DT;
}

void CTheresa_Ult_Crack::LateUpdate()
{
	__super::LateUpdate();

}

void CTheresa_Ult_Crack::PreRender(LPD3DXEFFECT pEffect)
{
	m_spMesh->PreRender(m_spGraphics, pEffect);
	pEffect->SetFloat("gAlpha", m_fAlpha);
	pEffect->SetBool("gPlayingAnim", false);

}

void CTheresa_Ult_Crack::Render(LPD3DXEFFECT pEffect)
{
	m_spMesh->Render(m_spGraphics, pEffect);
}

void CTheresa_Ult_Crack::PostRender(LPD3DXEFFECT pEffect)
{
	m_spMesh->PostRender(m_spGraphics, pEffect);
}

void CTheresa_Ult_Crack::OnDestroy()
{
	__super::OnDestroy();
}

void CTheresa_Ult_Crack::OnEnable()
{
	__super::OnEnable();
}

void CTheresa_Ult_Crack::OnDisable()
{
	__super::OnDisable();
}

void CTheresa_Ult_Crack::SetBasicName()
{
	m_name = m_objectKey + std::to_wstring(m_s_uniqueID++);
}
