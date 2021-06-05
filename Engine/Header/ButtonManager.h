#ifndef BUTTONMANAGER_H
#define BUTTONMANAGER_H

#include "Engine.h"

BEGIN(Engine)
//class CButton;
class ENGINE_DLL CButtonManager final : public CEngine
{
public:
	//DECLARE_SINGLETON(CButtonManager)
public:
	void Awake(void) override;
	void Update(void);
	void OnDestroy(void);

	/*void AddButtonList(CButton* buttonObject);
private:
	void UpButtonActivation();
	void DownButtonActivation();
	void PressButtonActivation();
private:
	std::list<CButton*> m_UpButtonList;
	std::list<CButton*> m_DownButtonList;
	std::list<CButton*> m_PressButtonList;*/
};

END
#endif	