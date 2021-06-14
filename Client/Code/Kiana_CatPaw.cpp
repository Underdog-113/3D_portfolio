#include "stdafx.h"
#include "Kiana_CatPaw.h"


CKiana_CatPaw::CKiana_CatPaw()
{
}


CKiana_CatPaw::~CKiana_CatPaw()
{
	OnDestroy();
}

SP(CKiana_CatPaw) CKiana_CatPaw::Create(_bool isStatic, Engine::CScene * pScene)
{
	return SP(CKiana_CatPaw)();
}

SP(Engine::CObject) CKiana_CatPaw::MakeClone(void)
{
	return SP(Engine::CObject)();
}

void CKiana_CatPaw::Awake(void)
{
	__super::Awake();
}

void CKiana_CatPaw::Start(void)
{
	__super::Start();

}

void CKiana_CatPaw::FixedUpdate(void)
{
	__super::FixedUpdate();
}

void CKiana_CatPaw::Update(void)
{
	__super::Update();
}

void CKiana_CatPaw::LateUpdate(void)
{
	__super::LateUpdate();
}

void CKiana_CatPaw::PreRender(void)
{
	m_spMesh->PreRender(m_spGraphics);
}

void CKiana_CatPaw::PreRender(LPD3DXEFFECT pEffect)
{
	m_spMesh->PreRender(m_spGraphics, pEffect);
}

void CKiana_CatPaw::Render(void)
{
	m_spMesh->Render(m_spGraphics);
}

void CKiana_CatPaw::Render(LPD3DXEFFECT pEffect)
{
	m_spMesh->Render(m_spGraphics, pEffect);
}

void CKiana_CatPaw::PostRender(void)
{
	m_spMesh->PostRender(m_spGraphics);
}

void CKiana_CatPaw::PostRender(LPD3DXEFFECT pEffect)
{
	m_spMesh->PreRender(m_spGraphics, pEffect);
}

void CKiana_CatPaw::OnDestroy(void)
{
	__super::OnDestroy();
}

void CKiana_CatPaw::OnEnable(void)
{
	__super::OnEnable();
}

void CKiana_CatPaw::OnDisable(void)
{
	__super::OnDisable();
}
