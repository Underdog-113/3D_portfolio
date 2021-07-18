#include "Stdafx.h"
#include "OneConversationC.h"
#include "MoneyItemC.h"
#include "StageControlTower.h"
#include "Valkyrie.h"

CMoneyItemC::CMoneyItemC()
{
}

CMoneyItemC::~CMoneyItemC()
{
	OnDestroy();
}

SP(Engine::CComponent) CMoneyItemC::MakeClone(Engine::CObject *pObject)
{
	SP(CMoneyItemC) spClone(new CMoneyItemC);
	__super::InitClone(spClone, pObject);

	return spClone;
}

void CMoneyItemC::Awake()
{
	__super::Awake();

	m_componentID = (_int)m_s_componentID;
}

void CMoneyItemC::Start(SP(CComponent) spThis)
{
	__super::Start(spThis);

	m_oldY = GetOwner()->GetTransform()->GetPosition().y;
	m_init = true;
	m_currentValkyrie = nullptr;
	m_dir = 1;
	m_enable = false;
}

void CMoneyItemC::FixedUpdate(SP(CComponent) spThis)
{

}

void CMoneyItemC::Update(SP(CComponent) spThis)
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
		if (Engine::Direction(m_currentValkyrie->GetTransform()->GetPosition(), pos) <= 0.2f)
		{
			CStageControlTower::GetInstance()->SetGold(CStageControlTower::GetInstance()->GetGold() + m_moneyValue);
			cout << CStageControlTower::GetInstance()->GetGold() << endl;

			GetOwner()->SetDeleteThis(true);
		}
	}
}

void CMoneyItemC::LateUpdate(SP(CComponent) spThis)
{

}

void CMoneyItemC::OnDestroy()
{
}

void CMoneyItemC::OnEnable()
{
	__super::OnEnable();
}

void CMoneyItemC::OnDisable()
{
	__super::OnDisable();
}

void CMoneyItemC::AddDataInit(_int moneyValue, _float force)
{
	m_moneyValue = moneyValue;
	m_force = force;
}

void CMoneyItemC::UpDown()
{
	_float value = 0.5;
	if (GetOwner()->GetTransform()->GetPosition().y >= m_oldY + value)
		m_dir = -1;
	if (GetOwner()->GetTransform()->GetPosition().y <= m_oldY - value)
		m_dir = 1;

	GetOwner()->GetTransform()->AddRotationY(1 * GET_DT);
	GetOwner()->GetTransform()->AddPositionY(m_dir * GET_DT);
}

