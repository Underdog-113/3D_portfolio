#include "Stdafx.h"
#include "GlitterC.h"
#include "Object.h"

CGlitterC::CGlitterC()
{
}

CGlitterC::~CGlitterC()
{
	OnDestroy();
}

SP(Engine::CComponent) CGlitterC::MakeClone(Engine::CObject *pObject)
{
	SP(CGlitterC) spClone(new CGlitterC);
	__super::InitClone(spClone, pObject);

	return spClone;
}

void CGlitterC::Awake()
{
	__super::Awake();

	m_componentID = (_int)m_s_componentID;
}

void CGlitterC::Start(SP(CComponent) spThis)
{
	__super::Start(spThis);
}

void CGlitterC::FixedUpdate(SP(CComponent) spThis)
{

}

void CGlitterC::Update(SP(CComponent) spThis)
{
	if (m_A1Timer >= 0)
	{
		GetOwner()->GetComponent<Engine::CTextureC>()->SetColor(D3DXCOLOR(1, 1, 1, 1));
		m_A1Timer -= GET_DT;
	}
	else if (m_A0Timer >= 0)
	{
		GetOwner()->GetComponent<Engine::CTextureC>()->SetColor(D3DXCOLOR(1, 1, 1, 0));
		m_A0Timer -= GET_DT;
	}
	else
	{
		m_A0Timer = m_A0TimerMax;
		m_A1Timer = m_A1TimerMax;
	}

	std::cout << GetOwner()->GetComponent<Engine::CTextureC>()->GetColor().a << std::endl;
}

void CGlitterC::LateUpdate(SP(CComponent) spThis)
{

}

void CGlitterC::OnDestroy()
{
}

void CGlitterC::OnEnable()
{
	__super::OnEnable();

	m_A0Timer = m_A0TimerMax;
	m_A1Timer = m_A1TimerMax;
}

void CGlitterC::OnDisable()
{
	__super::OnDisable();
}

void CGlitterC::AddGlitterData(_float a1TimerMax, _float a0TimerMax)
{
	m_A1Timer = a1TimerMax;
	m_A1TimerMax = a1TimerMax;

	m_A0Timer = a0TimerMax;
	m_A0TimerMax = a0TimerMax;
}
