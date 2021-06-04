#include "stdafx.h"
#include "..\Header\Mecca.h"


CMecca::CMecca()
{
}

SP(Engine::CObject) CMecca::MakeClone(void)
{
	return SP(CObject)();
}

void CMecca::Awake(void)
{
	__super::Awake();
}

void CMecca::Start(void)
{
	__super::Start();
}

void CMecca::FixedUpdate(void)
{
	__super::FixedUpdate();
}

void CMecca::Update(void)
{
	__super::Update();
}

void CMecca::LateUpdate(void)
{
	__super::LateUpdate();
}

void CMecca::OnDestroy(void)
{
	__super::OnDestroy();
}

void CMecca::OnEnable(void)
{
	__super::OnEnable();
}

void CMecca::OnDisable(void)
{
	__super::OnDisable();
}

void CMecca::SetBasicName(void)
{
}


CMecca::~CMecca()
{
}
