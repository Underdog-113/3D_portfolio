#include "stdafx.h"
#include "PatternMachineC.h"

#include "ClientPatterns.h"
#include "Monster.h"

#include "Valkyrie.h"

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

	if (false == m_previewMode &&
		Pattern_Type::TypeEnd != m_vPatterns.size() &&
		m_vIndices.empty())
	{
		SortingPatterns();
		return;
	}

	_float3 pos = m_pOwner->GetTransform()->GetPosition();

	if (Engine::IMKEY_DOWN(KEY_5))
	{
		m_onAirborne = true;
		static_cast<CMonster*>(m_pOwner)->GetStat()->SetCurBreakGauge(0.f);
	}

	//if (Engine::IMKEY_DOWN(MOUSE_WHEEL))
	//{
	//	//m_onAirborne = true;
	//	//static_cast<CMonster*>(m_pOwner)->GetStat()->SetCurBreakGauge(0.f);

	//	//m_onDie = true;
	//	//static_cast<CMonster*>(m_pOwner)->GetStat()->SetCurHp(0.f);

	//	//m_onStun = true;
	//	//static_cast<CMonster*>(m_pOwner)->GetStat()->SetOnSuperArmor(false);
	//	//static_cast<CMonster*>(m_pOwner)->GetStat()->SetCurBreakGauge(0.f);

	//	//m_pOwner->GetComponent<CPatternMachineC>()->SetOnHitL(true);

	//	if (14 > m_vRingEffect.size())
	//	{
	//		SP(Engine::CObject) effect = Engine::GET_CUR_SCENE->GetObjectFactory()->AddClone(L"Bronya_Ult_Ring", true);
	//		//SP(Engine::CObject) effect = Engine::GET_CUR_SCENE->GetObjectFactory()->AddClone(L"Bronya_Ult_Range", true);
	//		effect->GetTransform()->SetPosition(_float3(186.21f, -3.69f, -17.06f));
	//		//effect->GetTransform()->SetSize(0.3f, 0.3f, 0.3f);
	//		m_vRingEffect.emplace_back(effect);
	//	}
	//}

	//if (Engine::IMKEY_PRESS(KEY_SHIFT) && Engine::IMKEY_DOWN(KEY_X))
	//{
	//	_int index = m_curIndex - 1;
	//	
	//	if (0 > index)
	//	{
	//		m_curIndex = 0;
	//	}
	//	else if (index < m_vRingEffect.size())
	//	{
	//		m_curIndex = index;
	//	}
	//	std::cout << "Index : " << m_curIndex << std::endl;
	//}
	//else if (Engine::IMKEY_PRESS(KEY_SHIFT) && Engine::IMKEY_DOWN(KEY_C))
	//{
	//	_int index = m_curIndex + 1;

	//	if (14 < index)
	//	{
	//		m_curIndex = 14;
	//	}
	//	else if (index < m_vRingEffect.size())
	//	{
	//		m_curIndex = index;
	//	}
	//	std::cout << "Index : " << m_curIndex << std::endl;
	//}
	//
	//if (Engine::IMKEY_PRESS(KEY_SHIFT) && Engine::IMKEY_PRESS(KEY_W))
	//{
	//	m_vRingEffect[m_curIndex]->GetTransform()->AddPositionZ(0.05f);
	//}
	//else if (Engine::IMKEY_PRESS(KEY_SHIFT) && Engine::IMKEY_PRESS(KEY_A))
	//{
	//	m_vRingEffect[m_curIndex]->GetTransform()->AddPositionX(0.05f);
	//}
	//else if (Engine::IMKEY_PRESS(KEY_SHIFT) && Engine::IMKEY_PRESS(KEY_D))
	//{
	//	m_vRingEffect[m_curIndex]->GetTransform()->AddPositionX(-0.05f);
	//}
	//else if (Engine::IMKEY_PRESS(KEY_SHIFT) && Engine::IMKEY_PRESS(KEY_S))
	//{
	//	m_vRingEffect[m_curIndex]->GetTransform()->AddPositionZ(-0.05f);
	//}
	//else if (Engine::IMKEY_PRESS(KEY_SHIFT) && Engine::IMKEY_PRESS(KEY_Q))
	//{
	//	m_vRingEffect[m_curIndex]->GetTransform()->AddPositionY(0.05f);
	//}
	//else if (Engine::IMKEY_PRESS(KEY_SHIFT) && Engine::IMKEY_PRESS(KEY_E))
	//{
	//	m_vRingEffect[m_curIndex]->GetTransform()->AddPositionY(-0.05f);
	//}

	//if (Engine::IMKEY_DOWN(MOUSE_RIGHT))
	//{
	//	//_float3 pos = m_pOwner->GetTransform()->GetPosition();
	//	//_float3 pos = CStageControlTower::GetInstance()->GetCurrentActor()->GetTransform()->GetForward();
	//	_float3 pos = CStageControlTower::GetInstance()->GetCurrentActor()->GetTransform()->GetPosition();
	//	std::cout << "x : " << pos.x << std::endl;
	//	std::cout << "y : " << pos.y << std::endl;
	//	std::cout << "z : " << pos.z << std::endl;
	//	std::cout << "======================" << std::endl;
	//}

	// born 실행 (1번만)
	PlayBornPattern();

	if (false == m_onBorn)
	{
		return;
	}

	// die 실행 (hp가 0일 때 1번만)
	PlayDiePattern();

	// select 실행
	PlaySelectPattern();

	// base 실행
	PlayBasePattern();

	// hit, airborne 실행
	PlayHitPattern();

	//std::cout << "BP	  : " << static_cast<CMonster*>(m_pOwner)->GetStat()->GetCurBreakGauge() << std::endl;
	//std::cout << "HP	  : " << static_cast<CMonster*>(m_pOwner)->GetStat()->GetCurHp() << std::endl;
	//std::cout << "Pattern  : " << std::endl;
}

void CPatternMachineC::LateUpdate(SP(Engine::CComponent) spThis)
{
}

void CPatternMachineC::OnDestroy()
{
}

void CPatternMachineC::OnEnable()
{
	__super::OnEnable();
}

void CPatternMachineC::OnDisable()
{
	__super::OnDisable();
}

void CPatternMachineC::AddNecessaryPatterns(SP(CATBPattern) pBorn, SP(CATBPattern) pDie, SP(CATBPattern) pBase, SP(CATBPattern) pHit, SP(CATBPattern) pAirborne, SP(CATBPattern) pStun)
{
	m_vPatterns.emplace_back(pBorn);
	m_vPatterns.emplace_back(pDie);
	m_vPatterns.emplace_back(pBase);
	m_vPatterns.emplace_back(pHit);
	m_vPatterns.emplace_back(pAirborne);
	m_vPatterns.emplace_back(pStun);
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
		true == m_onDie ||
		true == m_onAirborne ||
		true == m_onStun) &&
		true == m_onBase)
	{
		m_onBase = false;
	}
	// hit, die, select 패턴이 아니면
	else if (false == m_onHitL &&
			false == m_onHitH &&  
			false == m_onHitFrontL &&
			false == m_onHitFront &&
			false == m_onDie &&
			false == m_onAirborne &&
			false == m_onSelect &&
			false == m_onStun)
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
	
	// 에어본 상태라면
	if (true == m_onAirborne &&
		nullptr != m_vPatterns[Pattern_Type::Airborne])
	{
		m_vPatterns[Pattern_Type::Airborne]->Pattern(m_pOwner);
	}
	// 스턴 상태라면
	else if (true == m_onStun &&
		nullptr != m_vPatterns[Pattern_Type::Stun])
	{
		m_vPatterns[Pattern_Type::Stun]->Pattern(m_pOwner);
	}
	// 피격 상태라면
	else if (true == m_onHitL ||
			 true == m_onHitH ||
			 true == m_onHitFrontL ||
			 true == m_onHitFront)
	{
		m_vPatterns[Pattern_Type::Hit]->Pattern(m_pOwner);
	}
}

void CPatternMachineC::SortingPatterns()
{
	size_t size = m_vPatterns.size();
	_int index;

	if (Pattern_Type::TypeEnd == size)
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

		// select pattern이 끝났다면
		if (false == m_onSelect)
			m_vIndices.pop_back();

		return;
	}

	// 궁극기라면
	if (60.f <= cost)
	{
		// cost가 너무 낮다면
		if ((cost - 10) > m_curCost)
		{
			std::cout << "skip" << std::endl;
			m_curCost += 20.f;
			m_vIndices.pop_back();
			return;
		}
	}
	else if (50.f <= cost)
	{
		if ((cost - 10) > m_curCost)
		{
			std::cout << "skip" << std::endl;
			m_curCost += 13.f;
			m_vIndices.pop_back();
			return;
		}
	}

	// cost가 충분하지 않다면
	if (m_curCost < cost)
	{
		return;
	}

	std::cout << "Before Cost : " << m_curCost << std::endl;

	m_onSelect = true;
	m_curCost -= cost;

	std::cout << "After Cost : " << m_curCost << std::endl;
	std::cout << "=============================" << std::endl;
	return;
}
