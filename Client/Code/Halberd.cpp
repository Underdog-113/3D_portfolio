#include "stdafx.h"
#include "..\Header\Halberd.h"


CHalberd::CHalberd()
{
}

SP(Engine::CObject) CHalberd::MakeClone(void)
{
	return SP(CObject)();
}

void CHalberd::Awake(void)
{
	__super::Awake();
}

void CHalberd::Start(void)
{
	__super::Start();
}

void CHalberd::FixedUpdate(void)
{
	__super::FixedUpdate();
}

void CHalberd::Update(void)
{
	__super::Update();
}

void CHalberd::LateUpdate(void)
{
	__super::LateUpdate();
}

void CHalberd::OnDestroy(void)
{
	__super::OnDestroy();
}

void CHalberd::OnEnable(void)
{
	__super::OnEnable();
}

void CHalberd::OnDisable(void)
{
	__super::OnDisable();
}

void CHalberd::SetBasicName(void)
{
}
