#include "Stdafx.h"
#include "MonsterSliderC.h"
#include "Object.h"

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
			// 반짝이게 하고 내려가야함
		}
		else if (!m_bWhiteCheck)
		{
			m_sliderOwner->SetValue(m_sliderOwner->GetValue() - GET_DT * 5);
		}
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
