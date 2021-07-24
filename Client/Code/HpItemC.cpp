#include "Stdafx.h"
#include "OneConversationC.h"
#include "HpItemC.h"
#include "StageControlTower.h"
#include "Valkyrie.h"

CHpItemC::CHpItemC()
{
}

CHpItemC::~CHpItemC()
{
	OnDestroy();
}

SP(Engine::CComponent) CHpItemC::MakeClone(Engine::CObject *pObject)
{
	SP(CHpItemC) spClone(new CHpItemC);
	__super::InitClone(spClone, pObject);

	return spClone;
}

void CHpItemC::Awake()
{
	__super::Awake();

	m_componentID = (_int)m_s_componentID;
}

void CHpItemC::Start(SP(CComponent) spThis)
{
	__super::Start(spThis);

	m_oldY = GetOwner()->GetTransform()->GetPosition().y;
	m_init = true;
	m_currentValkyrie = nullptr;
	m_dir = 1;
	m_enable = false;
}

void CHpItemC::FixedUpdate(SP(CComponent) spThis)
{

}

void CHpItemC::Update(SP(CComponent) spThis)
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

		cout << Engine::Direction(m_currentValkyrie->GetTransform()->GetPosition(), pos) << endl;

		if (Engine::Direction(m_currentValkyrie->GetTransform()->GetPosition(), pos) <= 0.35f)
		{
			_float value = min(m_currentValkyrie->GetStat()->GetCurHp() + (_float)m_hpValue, m_currentValkyrie->GetStat()->GetMaxHp());
			m_currentValkyrie->GetStat()->SetCurHp(value);

			GetOwner()->SetDeleteThis(true);
		}
	}
}

void CHpItemC::LateUpdate(SP(CComponent) spThis)
{

}

void CHpItemC::OnDestroy()
{
}

void CHpItemC::OnEnable()
{
	__super::OnEnable();
}

void CHpItemC::OnDisable()
{
	__super::OnDisable();
}

void CHpItemC::AddDataInit(_int hpValue, _float force)
{
	m_hpValue = hpValue;
	m_force = force;
}

void CHpItemC::UpDown()
{
	_float value = 0.15f;
	if (GetOwner()->GetTransform()->GetPosition().y >= m_oldY + value)
		m_dir = -0.2f;
	if (GetOwner()->GetTransform()->GetPosition().y <= m_oldY - value)
		m_dir = 0.2f;

	GetOwner()->GetTransform()->AddRotationY(1 * GET_DT);
	GetOwner()->GetTransform()->AddPositionY(m_dir * GET_DT);
}

