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

	GetOwner()->GetTransform()->SetRotationX(124);
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
		GetOwner()->GetTransform()->AddRotationY(1 * GET_DT);

		m_currentValkyrie = CStageControlTower::GetInstance()->GetCurrentActor();
		if (m_currentValkyrie == nullptr)
		{
			return;
		}

		_float3 pos = GetOwner()->GetTransform()->GetPosition();
		pos.y = m_oldY;
		if (Engine::Direction(m_currentValkyrie->GetTransform()->GetPosition(), pos) <= 0.5f)
		{
			CDropItemManager::GetInstance()->SetGold(CDropItemManager::GetInstance()->GetGold() + m_moneyValue);

			GetOwner()->SetDeleteThis(true);
		}

		if (CBattleUiManager::GetInstance()->GetBattleEnd())
		{
			_float3 pos = m_currentValkyrie->GetTransform()->GetPosition() - GetOwner()->GetComponent<Engine::CTransformC>()->GetPosition();
			GetOwner()->GetComponent<Engine::CTransformC>()->AddPosition(pos * (5.0f * GET_DT));
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
	_float value = 0.15f;
	if (GetOwner()->GetTransform()->GetPosition().y >= m_oldY + value)
		m_dir = -0.2f;
	if (GetOwner()->GetTransform()->GetPosition().y <= m_oldY - value)
		m_dir = 0.2f;

	GetOwner()->GetTransform()->AddRotationY(1 * GET_DT);
	GetOwner()->GetTransform()->AddPositionY(m_dir * GET_DT);
}

