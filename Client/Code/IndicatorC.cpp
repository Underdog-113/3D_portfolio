#include "Stdafx.h"
#include "IndicatorC.h"
#include "Valkyrie.h"

CIndicatorC::CIndicatorC()
{
}

CIndicatorC::~CIndicatorC()
{
	OnDestroy();
}

SP(Engine::CComponent) CIndicatorC::MakeClone(Engine::CObject *pObject)
{
	SP(CIndicatorC) spClone(new CIndicatorC);
	__super::InitClone(spClone, pObject);

	return spClone;
}

void CIndicatorC::Awake()
{
	__super::Awake();

	m_componentID = (_int)m_s_componentID;
}

void CIndicatorC::Start(SP(CComponent) spThis)
{
	__super::Start(spThis);

}

void CIndicatorC::FixedUpdate(SP(CComponent) spThis)
{
}

void CIndicatorC::Update(SP(CComponent) spThis)
{
	if (m_target == nullptr || m_target->GetDeleteThis())
	{
		m_target = nullptr;
		GetOwner()->SetIsEnabled(false);
		return;
	}
	CValkyrie* m_currentValkyrie = CStageControlTower::GetInstance()->GetCurrentActor();

	_float3 pos = m_currentValkyrie->GetTransform()->GetPosition();
	pos.y -= 0.5f;

	GetOwner()->GetTransform()->SetPosition(pos);

	_float3 targetPos = m_target->GetTransform()->GetPosition();
	_float3 dir = targetPos - pos;
	D3DXVec3Normalize(&dir, &dir);
	dir.y = 0;

	GetOwner()->GetTransform()->SetGoalForward(dir);
	GetOwner()->GetTransform()->SetSlerpOn(true);
}

void CIndicatorC::LateUpdate(SP(CComponent) spThis)
{

}

void CIndicatorC::OnDestroy()
{
}

void CIndicatorC::OnEnable()
{
	__super::OnEnable();
}

void CIndicatorC::OnDisable()
{
	__super::OnDisable();
	m_target = nullptr;
}