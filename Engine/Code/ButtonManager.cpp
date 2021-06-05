#include "EngineStdafx.h"
#include "ButtonManager.h"
#include "Button.h"
USING(Engine)
//IMPLEMENT_SINGLETON(CSoundManager)

void CButtonManager::Awake(void)
{

}

void CButtonManager::Update(void)
{
	/*if (Engine::IMKEY_DOWN(MOUSE_LEFT))
	{
		DownButtonActivation();
	}
	else if (Engine::IMKEY_UP(MOUSE_LEFT))
	{
		UpButtonActivation();
	}
	else if (Engine::IMKEY_PRESS(MOUSE_LEFT))
	{
		PressButtonActivation();
	}*/
}

void CButtonManager::OnDestroy(void)
{

}
/*
void CButtonManager::AddButtonList(CButton* buttonObject)
{
	switch (buttonObject->GetButtonType())
	{
	case CButton::EButton_Type::UP:
		m_UpButtonList.emplace_back(buttonObject);

		std::sort(m_UpButtonList.begin(), m_UpButtonList.end(),
			[](CButton* pObj1, CButton* pObj2)
		{
			return pObj1->GetTransform()->GetPosition().z > pObj2->GetTransform()->GetPosition().z;
		});
		break;
	case CButton::EButton_Type::Down:
		m_DownButtonList.emplace_back(buttonObject);

		std::sort(m_DownButtonList.begin(), m_DownButtonList.end(),
			[](CButton* pObj1, CButton* pObj2)
		{
			return pObj1->GetTransform()->GetPosition().z > pObj2->GetTransform()->GetPosition().z;
		});
		break;
	case CButton::EButton_Type::Press:
		m_PressButtonList.emplace_back(buttonObject);

		std::sort(m_PressButtonList.begin(), m_PressButtonList.end(),
			[](CButton* pObj1, CButton* pObj2)
		{
			return pObj1->GetTransform()->GetPosition().z > pObj2->GetTransform()->GetPosition().z;
		});
		break;
	}


}

void CButtonManager::UpButtonActivation()
{
	_float2 mousePos = Engine::CInputManager::GetInstance()->GetMousePos();

	for (auto& button : m_UpButtonList)
	{
		// 충돌체크
		button->FunceActivation();
	}
}

void CButtonManager::DownButtonActivation()
{
	_float2 mousePos = Engine::CInputManager::GetInstance()->GetMousePos();

}

void CButtonManager::PressButtonActivation()
{
	_float2 mousePos = Engine::CInputManager::GetInstance()->GetMousePos();

}
*/