#include "stdafx.h"
#include "CrossBloodHug.h"


CCrossBloodHug::CCrossBloodHug()
{
}


CCrossBloodHug::~CCrossBloodHug()
{
	OnDestroy();
}

SP(CCrossBloodHug) CCrossBloodHug::Create(_bool isStatic, Engine::CScene * pScene)
{
	SP(CCrossBloodHug) spInstance(new CCrossBloodHug, Engine::SmartDeleter<CCrossBloodHug>);
	spInstance->SetIsStatic(isStatic);
	spInstance->SetScene(pScene);
	spInstance->Awake();

	return spInstance;
}

SP(Engine::CObject) CCrossBloodHug::MakeClone(void)
{
	SP(CCrossBloodHug) spClone(new CCrossBloodHug, Engine::SmartDeleter<CCrossBloodHug>);
	__super::InitClone(spClone);

	spClone->m_spTransform = spClone->GetComponent<Engine::CTransformC>();
	spClone->m_spMesh = spClone->GetComponent<Engine::CMeshC>();
	spClone->m_spGraphics = spClone->GetComponent<Engine::CGraphicsC>();
	spClone->m_spShader = spClone->GetComponent<Engine::CShaderC>();
	spClone->m_spTexture = spClone->GetComponent<Engine::CTextureC>();

	return spClone;
}

void CCrossBloodHug::Awake(void)
{
}

void CCrossBloodHug::Start(void)
{
}

void CCrossBloodHug::FixedUpdate(void)
{
}

void CCrossBloodHug::Update(void)
{
}

void CCrossBloodHug::LateUpdate(void)
{
}

void CCrossBloodHug::PreRender(LPD3DXEFFECT pEffect)
{
}

void CCrossBloodHug::Render(LPD3DXEFFECT pEffect)
{
}

void CCrossBloodHug::PostRender(LPD3DXEFFECT pEffect)
{
}

void CCrossBloodHug::OnDestroy(void)
{
}

void CCrossBloodHug::OnEnable(void)
{
}

void CCrossBloodHug::OnDisable(void)
{
}

void CCrossBloodHug::SetBasicName(void)
{
}
