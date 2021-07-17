#pragma once
#ifndef UILINKER_H
#define UILINKER_H

class CStageControlTower;
class CUILinker
{
public:
	enum WaitSlot { Up, Down };

	enum JoyStick_Dir { NoDir, LD, D, RD, L, Center, R, LU, U, RU };

public:
	CUILinker();
	~CUILinker();

public:
	void	UpdateLinker			(void);

public:
	void	SwitchValkyrie			(WaitSlot slot, V_Stat::Valkyrie_Type switchIn, V_Stat::Valkyrie_Type switchOut);
			
	void	SwitchValkyrie_UpSlot	(V_Stat::Valkyrie_Type switchOut);
	void	SwitchValkyrie_DownSlot	(V_Stat::Valkyrie_Type switchOut);

	void	SwitchValkyrie_Actor	(V_Stat::Valkyrie_Type switchIn);

	void	PlayerHpSet				(void);									 
	void	PlayerSpSet				(void);

public:
	void	MoveJoyStick			();

	void	Skill					(void);
	void	Ultra					(void);
	void	Evade					();
	void	Attack					();

	void	SkillUI_SwitchSetting	();
	void	UltraUI_SwitchSetting	();

	void	SwapToOne				(void);
	void	SwapToTwo				(void);

	void	QTEButtonEffectOn(void);
	void	QTEButtonEffectOff(void);

	void	MonsterHpDown			(_float damage);
	void	Hit_Up					(void);
		
public:
	void	OnTargetMarker			(void);
	void	OffTargetMarker			(void);

		
	void	MonsterInfoSet			(void);
	void	OffMonsterInfo			(void);


private:
	CBattleUiManager* m_pUIManager = nullptr;
	
	GETTOR_SETTOR		(CStageControlTower*,		m_pCT,			nullptr,		ControlTower)
};

#endif