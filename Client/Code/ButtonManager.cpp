#include "Stdafx.h"
#include "ButtonManager.h"
#include "Button.h"
#include "InputManager.h"
#include "WndApp.h"

IMPLEMENT_SINGLETON(CButtonManager)
void CButtonManager::Awake(void)
{
	m_clickButton = nullptr;
	m_funcActivation = nullptr;
}

void CButtonManager::Update(void)
{
	if (Engine::IMKEY_DOWN(MOUSE_LEFT))
	{
		ButtonDown();
		ButtonActivation(m_DownButtonList);
	}
	if (Engine::IMKEY_UP(MOUSE_LEFT))
	{
		ButtonUp();
		ButtonActivation(m_UpButtonList);
	}
	if (Engine::IMKEY_PRESS(MOUSE_LEFT))
	{
		ButtonActivation(m_PressButtonList);
	}

}

void CButtonManager::OnDestroy(void)
{
	m_UpButtonList.clear();
	m_DownButtonList.clear();
	m_PressButtonList.clear();
}

void CButtonManager::AddButtonList(CButton* buttonObject)
{
	switch (buttonObject->GetButtonType())
	{
	case CButton::EButton_Type::UP:
		m_UpButtonList.emplace_back(buttonObject);
		break;
	case CButton::EButton_Type::Down:
		m_DownButtonList.emplace_back(buttonObject);
		break;
	case CButton::EButton_Type::Press:
		m_PressButtonList.emplace_back(buttonObject);
		break;
	}

	m_UpButtonList.sort([](CButton* pButton1, CButton* pButton2)
	{
		return pButton1->GetTransform()->GetPosition().z < pButton2->GetTransform()->GetPosition().z;
	});
}

void CButtonManager::DeleteButtonList(CButton * buttonObject)
{
	std::list<CButton*> obj;
	switch (buttonObject->GetButtonType())
	{
	case CButton::EButton_Type::UP:
		obj = m_UpButtonList;
		break;
	case CButton::EButton_Type::Down:
		obj = m_DownButtonList;
		break;
	case CButton::EButton_Type::Press:
		obj = m_PressButtonList;
		break;
	}

	for (auto& iter = m_UpButtonList.begin(); iter != m_UpButtonList.end(); iter++)
	{
		if ((*iter) == buttonObject)
		{
			m_UpButtonList.erase(iter);
			return;
		}
	}
}

void CButtonManager::ButtonActivation(std::list<CButton*> buttonList)
{
	_float2 mousePos = Engine::CInputManager::GetInstance()->GetMousePos();

	for (auto& button : buttonList)
	{
		if (ButtonCollisionCheck(button->GetTransform()->GetPosition(), button->GetTransform()->GetSize(), mousePos))
		{
			if (button->GetIsEnabled() && m_funcActivation == nullptr)
			{
				m_funcActivation = button;
			}
			else if (button->GetIsEnabled() && m_funcActivation->GetTransform()->GetPosition().z < button->GetTransform()->GetPosition().z)
			{
				m_funcActivation = button;
			}
		}
	}

	if (m_funcActivation)
	{
		m_activationButton = m_funcActivation;
		m_name = m_activationButton->GetName();
		m_funcActivation->FuncActivation();
		m_funcActivation = nullptr;
	}
}

void CButtonManager::ButtonDown()
{
	_float2 mousePos = Engine::CInputManager::GetInstance()->GetMousePos();

	for (auto& button : m_UpButtonList)
	{
		if (ButtonCollisionCheck(button->GetTransform()->GetPosition(), button->GetTransform()->GetSize(), mousePos))
		{
			if (!button->GetIsEnabled())
			{
				continue;
			}
			if (m_clickButton == nullptr)
			{
				m_clickButton = button;
			}
			else if (m_clickButton && m_clickButton->GetTransform()->GetPosition().z < button->GetTransform()->GetPosition().z)
			{
				m_clickButton = button;
			}
		}
	}

	for (auto& button : m_DownButtonList)
	{
		if (ButtonCollisionCheck(button->GetTransform()->GetPosition(), button->GetTransform()->GetSize(), mousePos))
		{
			if (!button->GetIsEnabled())
			{
				continue;
			}
			if (m_clickButton == nullptr)
			{
				m_clickButton = button;
			}
			else if (m_clickButton && m_clickButton->GetTransform()->GetPosition().z < button->GetTransform()->GetPosition().z)
			{
				m_clickButton = button;
			}
		}
	}

	for (auto& button : m_PressButtonList)
	{
		if (ButtonCollisionCheck(button->GetTransform()->GetPosition(), button->GetTransform()->GetSize(), mousePos))
		{
			if (!button->GetIsEnabled())
			{
				continue;
			}
			else if (m_clickButton == nullptr)
			{
				m_clickButton = button;
			}
			else if (m_clickButton && m_clickButton->GetTransform()->GetPosition().z < button->GetTransform()->GetPosition().z)
			{
				m_clickButton = button;
			}
		}
	}

	if (m_clickButton)
	{
		m_clickButton->ButtonPressed();
	}
}

void CButtonManager::ButtonUp()
{
	if (m_clickButton)
	{
		m_clickButton->ButtonNormal();
		m_clickButton = nullptr;
	}
}

_bool CButtonManager::ButtonCollisionCheck(_float3 buttonPos, _float3 buttonScale, _float2 mousePos)
{
	_float2 pointDis;
	pointDis.x = abs(buttonPos.x - mousePos.x) * 2.0f;
	pointDis.y = abs(buttonPos.y - mousePos.y) * 2.0f;

	if (buttonScale.x >= pointDis.x && buttonScale.y >= pointDis.y)
	{
		return true;
	}

	return false;
}
