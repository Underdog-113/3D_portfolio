#include "stdafx.h"
#include "CatPaw_Claw.h"


CCatPaw_Claw::CCatPaw_Claw()
{
}


CCatPaw_Claw::~CCatPaw_Claw()
{
	OnDestroy();
}

SP(CCatPaw_Claw) CCatPaw_Claw::Create(_bool isStatic, Engine::CScene * pScene)
{
	return SP(CCatPaw_Claw)();
}

SP(Engine::CObject) CCatPaw_Claw::MakeClone(void)
{
	return SP(Engine::CObject)();
}

void CCatPaw_Claw::Awake(void)
{
	__super::Awake();
}

void CCatPaw_Claw::Start(void)
{
	__super::Start();

}

void CCatPaw_Claw::FixedUpdate(void)
{
	__super::FixedUpdate();
}

void CCatPaw_Claw::Update(void)
{
	__super::Update();
}

void CCatPaw_Claw::LateUpdate(void)
{
	__super::LateUpdate();
}

void CCatPaw_Claw::PreRender(void)
{
	m_spMesh->PreRender(m_spGraphics);
}

void CCatPaw_Claw::PreRender(LPD3DXEFFECT pEffect)
{
	m_spMesh->PreRender(m_spGraphics, pEffect);
}

void CCatPaw_Claw::Render(void)
{
	m_spMesh->Render(m_spGraphics);
}

void CCatPaw_Claw::Render(LPD3DXEFFECT pEffect)
{
	m_spMesh->Render(m_spGraphics, pEffect);
}

void CCatPaw_Claw::PostRender(void)
{
	m_spMesh->PostRender(m_spGraphics);
}

void CCatPaw_Claw::PostRender(LPD3DXEFFECT pEffect)
{
	m_spMesh->PreRender(m_spGraphics, pEffect);
}

void CCatPaw_Claw::OnDestroy(void)
{
	__super::OnDestroy();
}

void CCatPaw_Claw::OnEnable(void)
{
	__super::OnEnable();
}

void CCatPaw_Claw::OnDisable(void)
{
	__super::OnDisable();
}
