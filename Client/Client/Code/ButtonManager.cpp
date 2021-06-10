#include "Stdafx.h"
#include "ButtonManager.h"
#include "Button.h"
#include "InputManager.h"
#include "WndApp.h"

IMPLEMENT_SINGLETON(CButtonManager)
void CButtonManager::Awake(void)
{

}

void CButtonManager::Update(void)
{
	// 버튼 누르면 색변경
	// 버튼 때면 색변경

	if (Engine::IMKEY_DOWN(MOUSE_LEFT))
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


void CButtonManager::UpButtonActivation()
{
	_float2 mousePos = Engine::CInputManager::GetInstance()->GetMousePos();

	for (auto& button : m_UpButtonList)
	{
		if (ButtonCollisionCheck(button->GetTransform()->GetPosition(), button->GetTransform()->GetSize(), mousePos))
		{
			button->FuncActivation();
		}
	}
}

void CButtonManager::DownButtonActivation()
{
	_float2 mousePos = Engine::CInputManager::GetInstance()->GetMousePos();

	for (auto& button : m_DownButtonList)
	{
		if (ButtonCollisionCheck(button->GetTransform()->GetPosition(), button->GetTransform()->GetSize(), mousePos))
		{
			button->FuncActivation();
		}
	}
}

void CButtonManager::PressButtonActivation()
{
	_float2 mousePos = Engine::CInputManager::GetInstance()->GetMousePos();

	for (auto& button : m_PressButtonList)
	{
		if (ButtonCollisionCheck(button->GetTransform()->GetPosition(), button->GetTransform()->GetSize(), mousePos))
		{
			button->FuncActivation();
		}
	}
}

_bool CButtonManager::ButtonCollisionCheck(_float3 buttonPos, _float3 buttonScale, _float2 mousePos)
{
	_float2 pointDis;
	pointDis.x = abs(buttonPos.x - mousePos.x);
	pointDis.y = abs(buttonPos.y - mousePos.y);

	if (buttonScale.x >= pointDis.x && buttonScale.y >= pointDis.y)
	{
		return true;
	}

	return false;
}
