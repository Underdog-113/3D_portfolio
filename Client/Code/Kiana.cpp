#include "stdafx.h"
#include "..\Header\Kiana.h"


Kiana::Kiana()
{
}


Kiana::~Kiana()
{
}

SP(Engine::CObject) Kiana::MakeClone(void)
{
	SP(Kiana) spClone(new Kiana, Engine::SmartDeleter<Kiana>);

	__super::InitClone(spClone);

	spClone->m_spTransform = spClone->GetComponent<Engine::CTransformC>();
	spClone->m_spMesh = spClone->GetComponent<Engine::CMeshC>();
	spClone->m_spGraphics = spClone->GetComponent<Engine::CGraphicsC>();
	spClone->m_spFSM = spClone->GetComponent<FSM_SpiderC>();
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
