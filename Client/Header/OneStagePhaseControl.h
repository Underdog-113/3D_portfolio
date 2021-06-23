#ifndef ONESTAGEPHASECONTROL_H
#define ONESTAGEPHASECONTROL_H

#include "PhaseControl.h"

class COneStagePhaseControl final : public CPhaseControl
{
public:
	COneStagePhaseControl();
	~COneStagePhaseControl();

public:
					void		Update		(void) override;
};

#endif