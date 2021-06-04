#include "stdafx.h"
#include "..\Header\AirPlane.h"


CAirPlane::CAirPlane()
{
}

SP(Engine::CObject) CAirPlane::MakeClone(void)
{
	return SP(CObject)();
}

void CAirPlane::Awake(void)
{
	__super::Awake();
}

void CAirPlane::Start(void)
{
	__super::Start();
}

void CAirPlane::FixedUpdate(void)
{
	__super::FixedUpdate();
}

void CAirPlane::Update(void)
{
	__super::Update();
}

void CAirPlane::LateUpdate(void)
{
	__super::LateUpdate();
}

void CAirPlane::OnDestroy(void)
{
	__super::OnDestroy();
}

void CAirPlane::OnEnable(void)
{
	__super::OnEnable();
}

void CAirPlane::OnDisable(void)
{
	__super::OnDisable();
}

void CAirPlane::SetBasicName(void)
{
}

