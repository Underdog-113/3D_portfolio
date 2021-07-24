#include "Stdafx.h"
#include "OneConversationC.h"
#include "StuffItemC.h"
#include "StageControlTower.h"
#include "Valkyrie.h"

CStuffItemC::CStuffItemC()
{
}

CStuffItemC::~CStuffItemC()
{
	OnDestroy();
}

SP(Engine::CComponent) CStuffItemC::MakeClone(Engine::CObject *pObject)
{
	SP(CStuffItemC) spClone(new CStuffItemC);
	__super::InitClone(spClone, pObject);

	return spClone;
}

void CStuffItemC::Awake()
{
	__super::Awake();

	m_componentID = (_int)m_s_componentID;
}

void CStuffItemC::Start(SP(CComponent) spThis)
{
	__super::Start(spThis);

	GetOwner()->GetTransform()->SetRotationX(124);
	m_oldY = GetOwner()->GetTransform()->GetPosition().y;
	m_init = true;
	m_currentValkyrie = nullptr;
	m_dir = 1;
	m_enable = false;
}

void CStuffItemC::FixedUpdate(SP(CComponent) spThis)
{

}

void CStuffItemC::Update(SP(CComponent) spThis)
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
		if (Engine::Direction(m_currentValkyrie->GetTransform()->GetPosition(), pos) <= 0.35)
		{
			CDropItemManager::GetInstance()->AddItemList(m_itemValue);
			GetOwner()->SetDeleteThis(true);
		}
	}
}

void CStuffItemC::LateUpdate(SP(CComponent) spThis)
{

}

void CStuffItemC::OnDestroy()
{
}

void CStuffItemC::OnEnable()
{
	__super::OnEnable();
}

void CStuffItemC::OnDisable()
{
	__super::OnDisable();
}

void CStuffItemC::AddDataInit(ItemSave itemValue, _float force)
{
	m_itemValue = itemValue;
	m_force = force;
}

void CStuffItemC::UpDown()
{
	_float value = 0.15f;
	if (GetOwner()->GetTransform()->GetPosition().y >= m_oldY + value)
		m_dir = -0.2f;
	if (GetOwner()->GetTransform()->GetPosition().y <= m_oldY - value)
		m_dir = 0.2f;

	GetOwner()->GetTransform()->AddRotationY(1 * GET_DT);
	GetOwner()->GetTransform()->AddPositionY(m_dir * GET_DT);
}

