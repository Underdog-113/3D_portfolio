#include "stdafx.h"
#include "PatternMachineC.h"

#include "ClientPatterns.h"

CPatternMachineC::CPatternMachineC()
{
}

CPatternMachineC::~CPatternMachineC()
{
	OnDestroy();
}

SP(Engine::CComponent) CPatternMachineC::MakeClone(Engine::CObject * pObject)
{
	SP(CPatternMachineC) spClone(new CPatternMachineC);
	__super::InitClone(spClone, pObject);

	return spClone;
}

void CPatternMachineC::Awake()
{
	__super::Awake();
	m_componentID = (_int)m_s_componentID;
}

void CPatternMachineC::Start(SP(Engine::CComponent) spThis)
{
	__super::Start(spThis);
	m_componentID = (_int)m_s_componentID;
}

void CPatternMachineC::FixedUpdate(SP(Engine::CComponent) spThis)
{
}

void CPatternMachineC::Update(SP(Engine::CComponent) spThis)
{
	m_curCost += GET_DT * 2.f;

	if (m_curCost > m_maxCost)
		m_curCost = m_maxCost;

	if (4 != m_vPatterns.size() && m_vIndices.empty())
	{
		SortingPatterns();
		return;
	}

	//if (Engine::IMKEY_DOWN(KEY_Q))
	//{
	//	m_onHitFrontL = true;
	//}
	//else if (Engine::IMKEY_DOWN(KEY_E))
	//{
	//	m_onHitFront = true;
	//}

	// born 실행 (1번만)
	PlayBornPattern();
	
	// die 실행 (호출 실행)
	//PlayDiePattern();

	// select 실행
	PlaySelectPattern();

	// base 실행
	PlayBasePattern();

	// hit 실행
	PlayHitPattern();
}

void CPatternMachineC::LateUpdate(SP(Engine::CComponent) spThis)
{
}

void CPatternMachineC::OnDestroy()
{
	//__super::OnDestroy();

	//for (auto& state : m_vPatterns)
	//{
	//	SAFE_DELETE(state);
	//}
	//m_vPatterns.clear();
}

void CPatternMachineC::OnEnable()
{
	__super::OnEnable();
}

void CPatternMachineC::OnDisable()
{
	__super::OnDisable();
}

void CPatternMachineC::AddNecessaryPatterns(SP(CATBPattern) pBorn, SP(CATBPattern) pDie, SP(CATBPattern) pBase, SP(CATBPattern) pHit)
{
	m_vPatterns.emplace_back(pBorn);
	m_vPatterns.emplace_back(pDie);
	m_vPatterns.emplace_back(pBase);
	m_vPatterns.emplace_back(pHit);
}

void CPatternMachineC::AddPattern(SP(CATBPattern) pPattern)
{
	if (nullptr == pPattern)
	{
		MSG_BOX(__FILE__, L"pPattern is nullptr");
		ABORT;
	}

	if (m_vPatterns.empty())
	{
		MSG_BOX(__FILE__, L"Call the 'AddNecessaryPatterns' function first");
		ABORT;
	}

	m_vPatterns.emplace_back(pPattern);
}

void CPatternMachineC::PlayBasePattern()
{
	if ((true == m_onHitL ||
		true == m_onHitH || 
		true == m_onHitFrontL || 
		true == m_onHitFront) 
		&& true == m_onBase)
	{
		m_onBase = false;
	}
	else if ((false == m_onHitL &&
			false == m_onHitH &&  
			false == m_onHitFrontL &&
			false == m_onHitFront) &&
			false == m_onSelect)
	{
		m_onBase = true;
		m_vPatterns[Pattern_Type::Base]->Pattern(m_pOwner);
	}
}

void CPatternMachineC::PlayBornPattern()
{
	if (false == m_onBorn)
	{
		m_vPatterns[Pattern_Type::Born]->Pattern(m_pOwner);
		return;
	}
}

void CPatternMachineC::PlayDiePattern()
{
	m_vPatterns[Pattern_Type::Die]->Pattern(m_pOwner);
}

void CPatternMachineC::PlayHitPattern()
{
	if (true == m_onHitL ||
		true == m_onHitH ||
		true == m_onHitFrontL ||
		true == m_onHitFront)
		m_vPatterns[Pattern_Type::Hit]->Pattern(m_pOwner);
}

void CPatternMachineC::SortingPatterns()
{
	size_t size = m_vPatterns.size();
	_int index;

	if (4 == size)
		return;

	for (_int i = 0; i < size; ++i)
	{
		index = rand() % (size - 4) + 4;
		m_vIndices.emplace_back(index);
	}
}

void CPatternMachineC::PlaySelectPattern()
{
	// base패턴 중이거나 select가 비었다면
	if (true == m_onBase || m_vIndices.empty())
		return;

	_int index = m_vIndices.back();
	_float cost = m_vPatterns[index]->GetCost();

	// select pattern이 진행중이라면
	if (true == m_onSelect)
	{
		if (true == m_onHitL ||
			true == m_onHitH ||
			true == m_onHitFrontL ||
			true == m_onHitFront)
			m_onSelect = false;
		else
			m_vPatterns[index]->Pattern(m_pOwner);

		return;
	}
	// select pattern이 끝났다면
	else if (false == m_onSelect)
		m_vIndices.pop_back();

	// cost가 충분하지 않다면
	if (m_curCost < cost)
		return;

	m_onSelect = true;
	m_curCost -= cost;

	//std::cout << "After Cost : " << m_curCost << std::endl;
	//std::cout << "=============================" << std::endl;
}
