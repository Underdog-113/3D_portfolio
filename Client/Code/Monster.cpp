#include "stdafx.h"
#include "..\Header\Monster.h"


CMonster::CMonster()
{
}

SP(Engine::CObject) CMonster::MakeClone(void)
{
	return SP(CObject)();
}

void CMonster::Awake(void)
{
	__super::Awake();
}

void CMonster::Start(void)
{
	__super::Start();
	PickComponentToRender();
}

void CMonster::FixedUpdate(void)
{
	__super::FixedUpdate();
}

void CMonster::Update(void)
{
	__super::Update();
}

void CMonster::LateUpdate(void)
{
	__super::LateUpdate();
}

void CMonster::OnDestroy(void)
{
	__super::OnDestroy();
}

void CMonster::OnEnable(void)
{
	__super::OnEnable();
}

void CMonster::OnDisable(void)
{
	__super::OnDisable();
}

void CMonster::SetBasicName(void)
{
}

void CMonster::PickComponentToRender(void)
{
	SP(Engine::CMeshC)		spMesh = GetComponent<Engine::CMeshC>();
	SP(Engine::CRectTexC)	spRectTex = GetComponent<Engine::CRectTexC>();

	if (spMesh != nullptr)
	{
		m_spComponentToRender = spMesh;
		return;
	}
	else if (spRectTex != nullptr)
	{
		m_spComponentToRender = spRectTex;
		return;
	}
}
