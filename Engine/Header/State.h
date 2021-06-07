#ifndef STATE_H
#define STATE_H

BEGIN(Engine)

class CStateMachineC;
class ENGINE_DLL CState
{
	typedef		std::function<void(void)>		Func;

public:
	explicit	CState		(void);
				~CState		(void);

	CState*		MakeClone();

public:
	void DoInit();
	void DoEnter();
	void DoUpdate();
	void DoExit();

public:
	void SetMachine(Func init, Func enter, Func update, Func exit);

	void SetInitailize(Func init);
	void SetEnter(Func enter);
	void SetUpdate(Func update);
	void SetExit(Func exit);

protected:
	GETTOR_SETTOR(CStateMachineC*, m_pMachine, nullptr, StateMachine)

	Func			m_init			= nullptr;
	Func			m_enter			= nullptr;
	Func			m_update		= nullptr;
	Func			m_exit			= nullptr;
};


END

#endif // !STATE_H
