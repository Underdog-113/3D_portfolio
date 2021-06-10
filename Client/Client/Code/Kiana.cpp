#include "stdafx.h"
#include "..\Header\Kiana.h"


Kiana::Kiana()
{
}


Kiana::~Kiana()
{
	OnDestroy();
}

SP(Engine::CObject) Kiana::MakeClone(void)
{
	SP(Kiana) spClone(new Kiana, Engine::SmartDeleter<Kiana>);

	return spClone;;
}

void Kiana::Awake(void)
{
}

void Kiana::Start(void)
{
}

void Kiana::FixedUpdate(void)
{
}

void Kiana::Update(void)
{
}

void Kiana::LateUpdate(void)
{
}

void Kiana::OnDestroy(void)
{
}

void Kiana::OnEnable(void)
{
}

void Kiana::OnDisable(void)
{
}

void Kiana::SetBasicName(void)
{
}
