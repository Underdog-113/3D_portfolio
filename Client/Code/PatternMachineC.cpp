#include "stdafx.h"
#include "PatternMachineC.h"

#include "ClientPatterns.h"
#include "Monster.h"

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
	spClone->m_vPatterns = m_vPatterns;

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

	std::cout << "cost : " << m_curCost << std::endl;
	std::cout << "================================= " << std::endl;

	if (false == m_previewMode &&
		Pattern_Type::TypeEnd != m_vPatterns.size() &&
		m_vIndices.empty())
	{
		SortingPatterns();
		return;
	}

	_float3 pos = m_pOwner->GetTransform()->GetPosition();

	if (Engine::IMKEY_DOWN(MOUSE_WHEEL))
	{
		m_previewMode = (false == m_previewMode) ? m_previewMode = true : m_previewMode = false;
		m_vIndices.clear();
	}

	//if (Engine::IMKEY_DOWN(KEY_Q))
	//{
	//	m_onDie = true;
	//	static_cast<CMonster*>(m_pOwner)->GetStat()->SetCurHp(0.f);
	//	//m_onHitH = true;
	//}
	//
	//if (Engine::IMKEY_DOWN(KEY_E))
	//{
	//	m_onHitL= true;
	//}

	// born 실행 (1번만)
	PlayBornPattern();
	
	// die 실행 (hp가 0일 때 1번만)
	PlayDiePattern();

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
	// hit, die 패턴이면 base 패턴 종료
	if ((true == m_onHitL ||
		true == m_onHitH || 
		true == m_onHitFrontL || 
		true == m_onHitFront ||
		true == m_onDie) 
		&& true == m_onBase)
	{
		m_onBase = false;
	}
	// hit, die, select 패턴이 아니면
	else if ((false == m_onHitL &&
			false == m_onHitH &&  
			false == m_onHitFrontL &&
			false == m_onHitFront &&
			false == m_onDie) &&
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
	if (true == m_onDie)
		m_vPatterns[Pattern_Type::Die]->Pattern(m_pOwner);
}

void CPatternMachineC::PlayHitPattern()
{
	if (true == m_onDie)
		return;

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
		// 시연회 모드가 아니면 랜덤하게 패턴 정렬
		if (false == m_previewMode)
		{
			index = rand() % (size - Pattern_Type::TypeEnd) + Pattern_Type::TypeEnd;
		}
		// 시연회 모드라면 순서대로 패턴 정렬
		else if (true == m_previewMode)
		{
			index = i + Pattern_Type::TypeEnd;
		}

		m_vIndices.emplace_back(index);

		// 시연회 모드 패턴 마지막에 base 패턴 넣기
		if (true == m_previewMode && size - 1 == i)
		{
			m_vIndices.emplace_back(Pattern_Type::Base);
		}
	}
}

void CPatternMachineC::PlaySelectPattern()
{
	// base, die패턴 중이거나 select가 비었다면
	if (true == m_onBase || true == m_onDie || m_vIndices.empty())
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
