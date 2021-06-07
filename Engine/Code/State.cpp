#include "EngineStdafx.h"
#include "State.h"


USING(Engine)

CState::CState()
{
}


CState::~CState()
{
}

CState* CState::MakeClone()
{
	CState* spClone = new CState;

	spClone->m_pMachine = m_pMachine;
	spClone->m_init = m_init;
	spClone->m_enter = m_enter;
	spClone->m_update = m_update;
	spClone->m_exit = m_exit;

	return spClone;
}

void CState::DoInit()
{
	m_init();
}

void CState::DoEnter()
{
	m_enter();
}

void CState::DoUpdate()
{
	m_update();
}

void CState::DoExit()
{
	m_exit();
}

void CState::SetMachine(Func init, Func enter, Func update, Func exit)
{
	SetInitailize(init);
	SetEnter(enter);
	SetUpdate(update);
	SetExit(exit);
}

void CState::SetInitailize(Func init)
{
	m_init = init;
}

void CState::SetEnter(Func enter)
{
	m_enter = enter;
}

void CState::SetUpdate(Func update)
{
	m_update = update;
}

void CState::SetExit(Func exit)
{
	m_exit = exit;
}
