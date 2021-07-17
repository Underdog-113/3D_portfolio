#include "Stdafx.h"
#include "QteC.h"

CQteC::CQteC()
{
}

CQteC::~CQteC()
{
	OnDestroy();
}

SP(Engine::CComponent) CQteC::MakeClone(Engine::CObject *pObject)
{
	SP(CQteC) spClone(new CQteC);
	__super::InitClone(spClone, pObject);

	return spClone;
}

void CQteC::Awake()
{
	__super::Awake();

	m_componentID = (_int)m_s_componentID;
}

void CQteC::Start(SP(CComponent) spThis)
{
	__super::Start(spThis);
	m_oldScale = GetOwner()->GetTransform()->GetSize();
	m_value = m_minSize;
}

void CQteC::FixedUpdate(SP(CComponent) spThis)
{

}

void CQteC::Update(SP(CComponent) spThis)
{
	GetOwner()->GetComponent<Engine::CTransformC>()->SetSize(m_oldScale * m_value);

	if (m_value <= m_maxSize )
	{
		m_value = m_value + (GET_DT * m_speed);
	}
	else
	{
		m_value = m_minSize;
	}
}

void CQteC::LateUpdate(SP(CComponent) spThis)
{

}

void CQteC::OnDestroy()
{
}

void CQteC::OnEnable()
{
	__super::OnEnable();
}

void CQteC::OnDisable()
{
	__super::OnDisable();
}

void CQteC::AddData(_float minSize, _float maxSize, _float speed)
{
	m_minSize = minSize;
	m_maxSize = maxSize;
	m_speed = speed;
}
