#ifndef PHASECONTROL_H
#define PHASECONTROL_H

class CStageControlTower;
class CPhaseControl abstract
{
public:
	CPhaseControl();
	~CPhaseControl();

public:
	virtual			void						Update					(void) PURE;
					void						IncreasePhase			(void);

protected:
	GETTOR_SETTOR	(CStageControlTower*,		m_pCT,					nullptr,		ControlTower)
	GETTOR_SETTOR	(_int,						m_curPhase,				UNDEFINED,		CurPhase)

};

#endif