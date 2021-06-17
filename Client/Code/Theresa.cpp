#include "stdafx.h"
#include "Theresa.h"

#include "FSM_TheresaC.h"

CTheresa::CTheresa()
{
}


CTheresa::~CTheresa()
{
	OnDestroy();
}

SP(CTheresa) CTheresa::Create(_bool isStatic, Engine::CScene * pScene)
{
	SP(CTheresa) spInstance(new CTheresa, Engine::SmartDeleter<CTheresa>);
	spInstance->SetIsStatic(isStatic);
	spInstance->SetScene(pScene);
	spInstance->Awake();

	return spInstance;
}

SP(Engine::CObject) CTheresa::MakeClone(void)
{
	SP(CTheresa) spClone(new CTheresa, Engine::SmartDeleter<CTheresa>);
	__super::InitClone(spClone);

	spClone->m_spTransform = spClone->GetComponent<Engine::CTransformC>();
	spClone->m_spMesh = spClone->GetComponent<Engine::CMeshC>();
	spClone->m_spGraphics = spClone->GetComponent<Engine::CGraphicsC>();
	spClone->m_spShader = spClone->GetComponent<Engine::CShaderC>();
	spClone->m_spTexture = spClone->GetComponent<Engine::CTextureC>();

	spClone->m_spStateMachine = spClone->GetComponent<CFSM_TheresaC>();
	return spClone;
}

void CTheresa::Awake(void)
{
}

void CTheresa::Start(void)
{
}

void CTheresa::FixedUpdate(void)
{
}

void CTheresa::Update(void)
{
}

void CTheresa::LateUpdate(void)
{
}

void CTheresa::PreRender(void)
{
}

void CTheresa::PreRender(LPD3DXEFFECT pEffect)
{
}

void CTheresa::Render(void)
{
}

void CTheresa::Render(LPD3DXEFFECT pEffect)
{
}

void CTheresa::PostRender(void)
{
}

void CTheresa::PostRender(LPD3DXEFFECT pEffect)
{
}

void CTheresa::OnDestroy(void)
{
}

void CTheresa::OnEnable(void)
{
}

void CTheresa::OnDisable(void)
{
}

void CTheresa::SetBasicName(void)
{
}
