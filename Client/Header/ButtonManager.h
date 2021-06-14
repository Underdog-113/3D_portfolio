#ifndef BUTTONMANAGER_H
#define BUTTONMANAGER_H

#include "Button.h"
class CButtonManager final
{
public:
	DECLARE_SINGLETON(CButtonManager)
public:
	void Awake(void);
	void Update(void);
	void OnDestroy(void);

	void AddButtonList(CButton* buttonObject);
private:
	void ButtonActivation(std::list<CButton*> buttonList);

	void ButtonDown();
	void ButtonUp();

	_bool ButtonCollisionCheck(_float3 buttonPos, _float3 buttonScale, _float2 mousePos);
private:
	std::list<CButton*> m_UpButtonList;
	std::list<CButton*> m_DownButtonList;
	std::list<CButton*> m_PressButtonList;

	CButton* m_clickButton;
	CButton* m_funcActivation;
};


#endif