#include "Stdafx.h"
#include "MonsterSliderC.h"
#include "Object.h"
#include "GlitterC.h"

CMonsterSliderC::CMonsterSliderC()
{
}

CMonsterSliderC::~CMonsterSliderC()
{
	OnDestroy();
}

SP(Engine::CComponent) CMonsterSliderC::MakeClone(Engine::CObject *pObject)
{
	SP(CMonsterSliderC) spClone(new CMonsterSliderC);
	__super::InitClone(spClone, pObject);

	return spClone;
}

void CMonsterSliderC::Awake()
{
	__super::Awake();

	m_componentID = (_int)m_s_componentID;
}

void CMonsterSliderC::Start(SP(CComponent) spThis)
{
	__super::Start(spThis);
	m_sliderOwner = static_cast<Engine::CSlider*>(GetOwner());
	m_bWhiteCheck = true;
	m_speed = 20;
	m_timerMax = 0.2f;
	m_timer = m_timerMax;
}

void CMonsterSliderC::FixedUpdate(SP(CComponent) spThis)
{

}

void CMonsterSliderC::Update(SP(CComponent) spThis)
{
	if (m_monsterSlider->GetValue() < m_sliderOwner->GetValue())
	{
		if (m_bWhiteCheck)
		{
			// 여기서 슬레이드를 번쩍하게 빛내줘야한다.

			m_timer -= GET_DT;
			if (m_timer <= 0)
			{
				m_timer = m_timerMax;
				m_bWhiteCheck = false;
			}
		}
		else if (!m_bWhiteCheck)
		{
			m_sliderOwner->SetValue(m_sliderOwner->GetValue() - GET_DT * m_speed);
		}
	}
	else
	{
		m_bWhiteCheck = true;
	}
}

void CMonsterSliderC::LateUpdate(SP(CComponent) spThis)
{

}

void CMonsterSliderC::OnDestroy()
{
}

void CMonsterSliderC::OnEnable()
{
	__super::OnEnable();
}

void CMonsterSliderC::OnDisable()
{
	__super::OnDisable();
}
