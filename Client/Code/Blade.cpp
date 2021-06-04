#include "stdafx.h"
#include "..\Header\Blade.h"


CBlade::CBlade()
{
}

SP(Engine::CObject) CBlade::MakeClone(void)
{
	return SP(CObject)();
}

void CBlade::Awake(void)
{
	__super::Awake();
}

void CBlade::Start(void)
{
	__super::Start();
}

void CBlade::FixedUpdate(void)
{
	__super::FixedUpdate();
}

void CBlade::Update(void)
{
	__super::Update();
}

void CBlade::LateUpdate(void)
{
	__super::LateUpdate();
}

void CBlade::OnDestroy(void)
{
	__super::OnDestroy();
}

void CBlade::OnEnable(void)
{
	__super::OnEnable();
}

void CBlade::OnDisable(void)
{
	__super::OnDisable();
}

void CBlade::SetBasicName(void)
{
}

