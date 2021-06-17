#pragma once
#ifndef UILINKER_H
#define UILINKER_H

class CStageControlTower;
class CUILinker
{
	enum JoyStick_Dir { Down = 2, Left = 4, Center = 5, Right = 6, Up = 8 };

public:
	CUILinker();
	~CUILinker();

public:
	void	PlayerHpSet			(void);
								 
	void	PlayerSpSet			(void);

public:
	void	MoveJoyStick		(JoyStick_Dir dir);

	void	Skill				(void);
	void	Ultra				(void);
	//void	Evade				(_float cooltime);
	//void	Attack				(_float cooltime);

	void	SwapToOne			(void);
	void	SwapToTwo			(void);

	void	Hit_Up				(void);
		
public:
	void	TargetMarker		(void);
		
	void	MonsterInfoSet		(void);
	void	MonsterHpSet		(void);


private:
	CBattleUiManager* m_pUIManager = nullptr;
	
	GETTOR_SETTOR		(CStageControlTower*,		m_pCT,			nullptr,		ControlTower)
};

#endif