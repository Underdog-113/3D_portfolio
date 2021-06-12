#include "Stdafx.h"
#include "UiAnimCtrC.h"

CUiAnimCtrC::CUiAnimCtrC()
{
}

CUiAnimCtrC::~CUiAnimCtrC()
{
	OnDestroy();
}

SP(Engine::CComponent) CUiAnimCtrC::MakeClone(Engine::CObject *pObject)
{
	SP(CUiAnimCtrC) spClone(new CUiAnimCtrC);
	__super::InitClone(spClone, pObject);

	return spClone;
}

void CUiAnimCtrC::Awake()
{
	__super::Awake();

	m_componentID = (_int)m_s_componentID;
	m_curAnimValue = 0;
}

void CUiAnimCtrC::Start(SP(CComponent) spThis)
{
	__super::Start(spThis);
	m_time = m_animSpeed;
}

void CUiAnimCtrC::FixedUpdate(SP(CComponent) spThis)
{

}

void CUiAnimCtrC::Update(SP(CComponent) spThis)
{
	m_time -= GET_DT;

	if (m_time <= 0)
	{
		m_curAnimValue++;
		GetOwner()->GetComponent<Engine::CTextureC>()->SetTexIndex(m_curAnimValue);

		if (m_curAnimValue == m_animCount)
		{
			m_curAnimValue = 0;
		}

		m_time = m_animSpeed;
	}
}

void CUiAnimCtrC::LateUpdate(SP(CComponent) spThis)
{

}

void CUiAnimCtrC::OnDestroy()
{
}

void CUiAnimCtrC::OnEnable()
{
	__super::OnEnable();
}

void CUiAnimCtrC::OnDisable()
{
	__super::OnDisable();
}