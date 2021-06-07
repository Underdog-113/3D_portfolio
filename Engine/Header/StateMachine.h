#ifndef STATEMACHINECOMPONENT_H
#define STATEMACHINECOMPONENT_H

/*
public:
void StateName_Init(void);
void StateName_Start(void);
void StateName_Update(float deltaTime);
void StateName_End(void);
*/

#define CreateState(className, pState, stateName)									\
pState = new Engine::CState;														\
pState->SetInitailize(std::bind(&##className##::##stateName##_Init, this));			\
pState->SetEnter(std::bind(&##className##::##stateName##_Enter, this));				\
pState->SetUpdate(std::bind(&##className##::##stateName##_Update, this, GET_DT));	\
pState->SetExit(std::bind(&##className##::##stateName##_End, this));				


BEGIN(Engine)

class CState;
class ENGINE_DLL CStateMachineC abstract : public CComponent
{
public:
	explicit	CStateMachineC	(void);
	virtual		~CStateMachineC	(void);

//Override functions									   
public:
	virtual SP(CComponent)		MakeClone		(CObject* pObject) PURE;

	virtual void		Awake			(void);
	virtual void		Start			(SP(CComponent) spThis);

			void		FixedUpdate		(SP(CComponent) spThis);
			void		Update			(SP(CComponent) spThis);
			void		LateUpdate		(SP(CComponent) spThis);

			 void		OnDestroy		(void);

			 void		OnEnable		(void);
			 void		OnDisable		(void);

public:
	template<typename T>
	SP(CStateMachineC)		MakeStateMachineClone(CObject* pObject)
	{
		SP(CStateMachineC) spClone(new T);

		__super::InitClone(spClone, pObject);

		for (auto pState : m_stateList)
		{
			spClone->m_stateList.emplace(pState.first, pState.second->MakeClone());
		}

		return spClone;
	}


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
	GETTOR_SETTOR	(_STATELIST,			m_stateList,	{},			StateList)
	GETTOR_SETTOR	(Engine::CState*,		m_curState,		nullptr,	CurrentState)

};


END
#endif // !STATEMACHINECOMPONENT_H