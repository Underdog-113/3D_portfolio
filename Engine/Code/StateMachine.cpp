#include "EngineStdafx.h"
#include "StateMachine.h"
#include "State.h"
#include "FRC.h"

USING(Engine)

CStateMachineC::CStateMachineC()
{
}


CStateMachineC::~CStateMachineC()
{
	OnDestroy();
}

SP(CComponent) CStateMachineC::MakeClone(CObject * pObject)
{
	SP(CStateMachineC) spClone(new CStateMachineC);
	__super::InitClone(spClone, pObject);
	
	for (auto pState : pObject->GetComponent<CStateMachineC>()->GetStateList())
	{
		m_stateList.emplace(pState);
	}

	return spClone;
}

void CStateMachineC::Awake(void)
{
	__super::Awake();
	m_componentID = (_int)m_s_componentID;

	for (auto state : m_stateList)
	{
		state.second->DoInit();
	}
}

void CStateMachineC::Start(SP(CComponent) spThis)
{
	__super::Start(spThis);

	m_curState->DoEnter();
}

void CStateMachineC::FixedUpdate(SP(CComponent) spThis)
{
}

void CStateMachineC::Update(SP(CComponent) spThis)
{
	m_curState->DoUpdate();
}

void CStateMachineC::LateUpdate(SP(CComponent) spThis)
{
}

void CStateMachineC::OnDestroy(void)
{
	for (auto& state : m_stateList)
	{
		SAFE_DELETE(state.second);
	}
	m_stateList.clear();
}

void CStateMachineC::OnEnable(void)
{
	__super::OnEnable();
}

void CStateMachineC::OnDisable(void)
{
	__super::OnDisable();
}

CStateMachineC* CStateMachineC::AddState(CState* pState, std::wstring stateName)
{
	if (m_stateList.end() != m_stateList.find(stateName))
	{
		MSG_BOX(__FILE__, L"State name is already exist");
		ABORT;
	}

	pState->SetStateMachine(this);
	m_stateList[stateName] = pState;

	return this;
}

CState* CStateMachineC::FindState(const std::wstring& stateName)
{
	auto state = m_stateList.find(stateName);

	if (m_stateList.end() == state)
	{
		MSG_BOX(__FILE__, L"State is not exist");
		ABORT;
	}

	return state->second;
}

std::wstring CStateMachineC::GetCurStateString(void)
{
	for (auto& state : m_stateList)
	{
		if (state.second == m_curState)
		{
			return state.first;
		}
	}
	return L"";
}

void CStateMachineC::SetStartState(std::wstring _stateName)
{
	if (m_stateList.end() == m_stateList.find(_stateName))
	{
		MSG_BOX(__FILE__, L"Can't find state that name");
		ABORT;
	}

	m_curState = m_stateList[_stateName];
}

void CStateMachineC::ChangeState(const std::wstring & _stateName)
{
	if (m_stateList.end() == m_stateList.find(_stateName))
	{
		MSG_BOX(__FILE__, L"Can't find state that name");
		ABORT;
	}


	m_curState->DoExit();

	m_curState = m_stateList[_stateName];

	m_curState->DoEnter();
}

bool CStateMachineC::CompareState(std::wstring _stateName)
{
	if (m_stateList.find(_stateName) == m_stateList.end())
		return false;

	if (m_stateList[_stateName] == m_curState)
		return true;

	return false;
}
