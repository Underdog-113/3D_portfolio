#include "Stdafx.h"
#include "OneConversationC.h"
#include "SpItemC.h"
#include "StageControlTower.h"
#include "Valkyrie.h"

CSpItemC::CSpItemC()
{
}

CSpItemC::~CSpItemC()
{
	OnDestroy();
}

SP(Engine::CComponent) CSpItemC::MakeClone(Engine::CObject *pObject)
{
	SP(CSpItemC) spClone(new CSpItemC);
	__super::InitClone(spClone, pObject);

	return spClone;
}

void CSpItemC::Awake()
{
	__super::Awake();

	m_componentID = (_int)m_s_componentID;
}

void CSpItemC::Start(SP(CComponent) spThis)
{
	__super::Start(spThis);

	m_oldY = GetOwner()->GetTransform()->GetPosition().y;
	m_init = true;
	m_currentValkyrie = nullptr;
	m_dir = 1;
	m_enable = false;
}

void CSpItemC::FixedUpdate(SP(CComponent) spThis)
{

}

void CSpItemC::Update(SP(CComponent) spThis)
{
	if (m_init)
	{
		m_init = false;
	}

	if (!m_enable && m_oldY > GetOwner()->GetTransform()->GetPosition().y)
	{
		GetOwner()->DeleteComponent<Engine::CRigidBodyC>();
		m_enable = true;
	}

	if (m_enable)
	{
		UpDown();

		m_currentValkyrie = CStageControlTower::GetInstance()->GetCurrentActor();
		if (m_currentValkyrie == nullptr)
		{
			return;
		}

		_float3 pos = GetOwner()->GetTransform()->GetPosition();
		pos.y = m_oldY;
		if (Engine::Direction(m_currentValkyrie->GetTransform()->GetPosition(), pos) <= 0.3f)
		{
			_float value = min(m_currentValkyrie->GetStat()->GetCurSp() + (_float)m_spValue, m_currentValkyrie->GetStat()->GetMaxSp());
			m_currentValkyrie->GetStat()->SetCurSp(value);
			GetOwner()->SetDeleteThis(true);
		}
	}
}

void CSpItemC::LateUpdate(SP(CComponent) spThis)
{

}

void CSpItemC::OnDestroy()
{
}

void CSpItemC::OnEnable()
{
	__super::OnEnable();
}

void CSpItemC::OnDisable()
{
	__super::OnDisable();
}

void CSpItemC::AddDataInit(_int spValue, _float force)
{
	m_spValue = spValue;
	m_force = force;
}

void CSpItemC::UpDown()
{
	_float value = 0.15f;
	if (GetOwner()->GetTransform()->GetPosition().y >= m_oldY + value)
		m_dir = -0.5f;
	if (GetOwner()->GetTransform()->GetPosition().y <= m_oldY - value)
		m_dir = 0.5f;

	GetOwner()->GetTransform()->AddRotationY(1 * GET_DT);
	GetOwner()->GetTransform()->AddPositionY(m_dir * GET_DT);
}

