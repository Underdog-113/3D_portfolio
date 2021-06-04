#ifndef STATEMACHINECOMPONENT_H
#define STATEMACHINECOMPONENT_H

/*
public:
void StateName_Init(void);
void StateName_Start(void);
void StateName_Update(float deltaTime);
void StateName_End(void);
*/

#define CreateState(pState, className, stateName)								\
pState = new Engine::CState;													\
pState->SetInitailize(std::bind(&##className::##stateName_Init, this));			\
pState->SetEnter(std::bind(&##className::##stateName_Enter, this));				\
pState->SetUpdate(std::bind(&##className::##stateName_Update, this, GET_DT));	\
pState->SetExit(std::bind(&##className::##stateName_End, this));				


BEGIN(Engine)

class CState;
class ENGINE_DLL CStateMachineC : public CComponent
{
public:
	explicit	CStateMachineC	(void);
	virtual		~CStateMachineC	(void);

//Override functions									   
public:
	SP(CComponent)		MakeClone		(CObject* pObject) override;

	virtual void		Awake			(void);
	void				Start			(SP(CComponent) spThis) override;

	void				FixedUpdate		(SP(CComponent) spThis) override;
	void				Update			(SP(CComponent) spThis) override;
	void				LateUpdate		(SP(CComponent) spThis) override;

	void				OnDestroy		(void) override;

	void				OnEnable		(void) override;
	void				OnDisable		(void) override;

public:

	CStateMachineC* AddState(CState* pState, std::wstring stateName);

	CState* FindState(const std::wstring& _stateName);

//Settors

//Interface
public:
	std::wstring	GetCurStateString	(void);
	void			SetStartState		(std::wstring _stateName);
	void			ChangeState			(const std::wstring& _stateName);
	bool			CompareState		(std::wstring _stateName);
	
public:
	static const	EComponentID		m_s_componentID = EComponentID::StateMachine;

// Get Set
protected:
	typedef std::map<std::wstring, Engine::CState*> _STATELIST;
	GETTOR			(_STATELIST,			m_stateList,	{},			StateList)
	GETTOR_SETTOR	(Engine::CState*,		m_curState,		nullptr,	CurrentState)

};


END
#endif // !STATEMACHINECOMPONENT_H