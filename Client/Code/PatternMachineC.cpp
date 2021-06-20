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

	if (m_vIndices.empty())
	{
		SortingPatterns();
		return;
	}

	//std::cout << "Cost : " << m_curCost << std::endl;

	// born 실행 (1번만)
	//m_vPatterns[Pattern_Type::Born]->Pattern();

	// die 실행
	//GetDeleteThis();

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
	if (!m_select)
		m_vPatterns[Pattern_Type::Base]->Pattern(m_pOwner);
}

void CPatternMachineC::PlayBornPattern()
{
	m_vPatterns[Pattern_Type::Born]->Pattern(m_pOwner);
}

void CPatternMachineC::PlayDiePattern()
{
	m_vPatterns[Pattern_Type::Die]->Pattern(m_pOwner);
}

void CPatternMachineC::PlayHitPattern()
{
	if (m_hit)
		m_vPatterns[Pattern_Type::Hit]->Pattern(m_pOwner);
}

void CPatternMachineC::SortingPatterns()
{
	size_t size = m_vPatterns.size();
	_int index;

	for (_int i = 0; i < size; ++i)
	{
		index = rand() % (size - 4) + 4;
		m_vIndices.emplace_back(index);
	}
}

void CPatternMachineC::PlaySelectPattern()
{
	_int index = m_vIndices.back();
	_float cost = m_vPatterns[index]->GetCost();

	// cost가 충분한지 확인
	if (m_curCost < cost)
	{
		m_select = false;
		return;
	}

	std::cout << "bCost : " << m_curCost << std::endl;

	m_select = true;
	m_curCost -= cost;
	m_vIndices.pop_back();
	m_vPatterns[index]->Pattern(m_pOwner);

	std::cout << "aCost : " << m_curCost << std::endl;
	std::cout << "=============================" << std::endl;
}
