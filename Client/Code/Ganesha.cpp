#include "stdafx.h"
#include "..\Header\Ganesha.h"


CGanesha::CGanesha()
{
}

SP(Engine::CObject) CGanesha::MakeClone(void)
{
	return SP(CObject)();
}

void CGanesha::Awake(void)
{
	__super::Awake();
}

void CGanesha::Start(void)
{
	__super::Start();
}

void CGanesha::FixedUpdate(void)
{
	__super::FixedUpdate();
}

void CGanesha::Update(void)
{
	__super::Update();
}

void CGanesha::LateUpdate(void)
{
	__super::LateUpdate();
}

void CGanesha::OnDestroy(void)
{
	__super::OnDestroy();
}

void CGanesha::OnEnable(void)
{
	__super::OnEnable();
}

void CGanesha::OnDisable(void)
{
	__super::OnDisable();
}

void CGanesha::SetBasicName(void)
{
}

