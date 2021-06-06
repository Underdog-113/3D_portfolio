#include "Stdafx.h"
#include "ButtonManager.h"
#include "Button.h"

IMPLEMENT_SINGLETON(CButtonManager)
void CButtonManager::Awake(void)
{

}

void CButtonManager::Update(void)
{
	// ��ư ������ ������
	// ��ư ���� ������

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
		// Ŭ���� ��ư ���� ����
		PressButtonActivation();
	}
}

void CButtonManager::OnDestroy(void)
{

}

bool sort(const CButton* button1, const CButton* button2)
{
	return button1->GetTransform()->GetPosition().z < button2->GetTransform()->GetPosition().z;
}

void CButtonManager::AddButtonList(CButton* buttonObject)
{
	switch (buttonObject->GetButtonType())
	{
	case CButton::EButton_Type::UP:
		m_UpButtonList.emplace_back(buttonObject);
		m_UpButtonList.sort(sort);
		break;
	case CButton::EButton_Type::Down:
		m_DownButtonList.emplace_back(buttonObject);
		m_DownButtonList.sort(sort);
		break;
	case CButton::EButton_Type::Press:
		m_PressButtonList.emplace_back(buttonObject);
		m_PressButtonList.sort((sort));
		break;
	}


}

bool CrushCheck(_float3 pos, _float3 scale, _float2 point)
{
	_float2 boxDis;
	boxDis.x = pos.x - scale.x;
	boxDis.y = pos.y - scale.y;

	_float2 pointDis;
	pointDis.x = pos.x - point.x;
	pointDis.y = pos.y - point.y;

	if (boxDis.x >= pointDis.x && boxDis.y >= pointDis.y)
	{
		return true;
	}

	return false;
}

void CButtonManager::UpButtonActivation()
{
	_float2 mousePos = Engine::CInputManager::GetInstance()->GetMousePos();

	for (auto& button : m_UpButtonList)
	{
		// ��ġ ������ ��ǥ���־��ָ� true false����ȯ �ϴ� �Լ�
		if (CrushCheck(button->GetTransform()->GetPosition(), button->GetTransform()->GetSize(), mousePos))
		{
			button->FunceActivation();
		}
	}
}

void CButtonManager::DownButtonActivation()
{
	//_float2 mousePos = Engine::CInputManager::GetInstance()->GetMousePos();

}

void CButtonManager::PressButtonActivation()
{
	//_float2 mousePos = Engine::CInputManager::GetInstance()->GetMousePos();

}
