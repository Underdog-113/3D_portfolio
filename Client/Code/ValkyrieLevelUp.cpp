#include "stdafx.h"
#include "ValkyrieLevelUp.h"

std::wstring CValkyrieLevelUp::g_selectItemName = L"";
_int CValkyrieLevelUp::g_itemCount = 0;
CValkyrieLevelUp::CValkyrieLevelUp()
{
}

CValkyrieLevelUp::~CValkyrieLevelUp()
{
}

void CValkyrieLevelUp::Start()
{
	CValkyriegManager::GetInstance()->GetScene()->FindObjectByName(L"LevelUpCanvas")->SetIsEnabled(true);
	CValkyriegManager::GetInstance()->GetScene()->FindObjectByName(L"LevelUpCanvas_Text_7")->GetComponent<Engine::CTextC>()->ChangeMessage(L"1");
}

void CValkyrieLevelUp::End()
{
	CValkyriegManager::GetInstance()->GetScene()->FindObjectByName(L"LevelUpCanvas")->SetIsEnabled(false);
}

_uint CValkyrieLevelUp::FixedUpdate()
{
	return _uint();
}

_uint CValkyrieLevelUp::Update()
{
	return _uint();
	
}

_uint CValkyrieLevelUp::LateUpdate()
{
	return _uint();
}

void CValkyrieLevelUp::OnDestroy(void)
{
}

void CValkyrieLevelUp::LevelUp()
{
	/* ��ư�Լ� (Ȯ��)
	�������� ���ְ� ����ġ�� �ø��� �Լ�
	*/

	CValkyrieStatusData* data = CDataManager::GetInstance()->FindInStockValkyrieData(CValkyriegManager::g_selectValkyrie);

	//100�� ���� ������ �������� ����ġ��ŭ ������ ����
	_int expSum = data->GetExperience() + (100 * g_itemCount);
	_int levalUpSum = 0;

	while (true)
	{
		if (expSum >= data->GetMaxExperience())
		{
			levalUpSum++;
			expSum -= data->GetMaxExperience();
			data->SetMaxExperience((_int)(data->GetMaxExperience() * 1.5));
			continue;
		}

		break;
	}

	data->SetExperience(expSum);
	data->SetLevel(data->GetLevel() + levalUpSum);
	g_itemCount = 1;
	CValkyriegManager::GetInstance()->ChangeFSMProperty();
}

void CValkyrieLevelUp::ItemCountUp()
{
	/* ��ư�Լ� (+)
	�������� ��밹���� ����ġ �������� �ø��� �Լ�
	// �������� ������ Ȯ���Ͽ� �������� �Ǵ��� ����ġ�� ��ȹ���ϴ��� üũ�Ͽ� UI�� �Լ� ����
	*/
	// ������ �������� ���� �̻� ���ö󰡰� ����
	g_itemCount++;

	CValkyriegManager::GetInstance()->GetScene()->FindObjectByName(L"LevelUpCanvas_Text_7")->GetComponent<Engine::CTextC>()->ChangeMessage(std::to_wstring(g_itemCount));
	std::static_pointer_cast<Engine::CSlider>(CValkyriegManager::GetInstance()->GetScene()->FindObjectByName(L"LevelUpCanvas_Slider_0"))->SetValue((_float)g_itemCount);

	CValkyrieStatusData* data = CDataManager::GetInstance()->FindInStockValkyrieData(CValkyriegManager::g_selectValkyrie);

	_int expSum = data->GetExperience() + (100 * g_itemCount);
	_int levalUpSum = data->GetLevel();
	_int nextExp = data->GetMaxExperience();
	while (true)
	{
		if (expSum >= nextExp)
		{
			levalUpSum++;
			expSum -= nextExp;
			nextExp = (int)(nextExp  * 1.5);
			continue;
		}

		break;
	}
	CValkyriegManager::GetInstance()->GetScene()->FindObjectByName(L"LevelUpCanvas_Text_5")->GetComponent<Engine::CTextC>()->ChangeMessage(std::to_wstring(levalUpSum));


	// ������ ���� ����
	// �����̴� ������ ����
}

void CValkyrieLevelUp::ItemCountDown()
{
	/* ��ư�Լ� (-)
	�������� ��밹���� ������ ����ġ �������� ������ �Լ�
	// �������� ������ Ȯ���Ͽ� �������� �Ǵ��� ����ġ�� ��ȹ���ϴ��� üũ�Ͽ� UI�� �Լ� ����
	*/
	g_itemCount--;

	if (g_itemCount <= 0)
		g_itemCount = 1;

	CValkyriegManager::GetInstance()->GetScene()->FindObjectByName(L"LevelUpCanvas_Text_7")->GetComponent<Engine::CTextC>()->ChangeMessage(std::to_wstring(g_itemCount));
	std::static_pointer_cast<Engine::CSlider>(CValkyriegManager::GetInstance()->GetScene()->FindObjectByName(L"LevelUpCanvas_Slider_0"))->SetValue((_float)g_itemCount);


	CValkyrieStatusData* data = CDataManager::GetInstance()->FindInStockValkyrieData(CValkyriegManager::g_selectValkyrie);

	_int expSum = data->GetExperience() + (100 * g_itemCount);
	_int levalUpSum = data->GetLevel();
	_int nextExp = data->GetMaxExperience();
	while (true)
	{
		if (expSum >= nextExp)
		{
			levalUpSum++;
			expSum -= nextExp;
			nextExp = (int)(nextExp  * 1.5);
			continue;
		}

		break;
	}
	CValkyriegManager::GetInstance()->GetScene()->FindObjectByName(L"LevelUpCanvas_Text_5")->GetComponent<Engine::CTextC>()->ChangeMessage(std::to_wstring(levalUpSum));

}

void CValkyrieLevelUp::ItemSelect()
{
	// � �������� ��������
	g_selectItemName = CButtonManager::GetInstance()->GetActivationButton()->GetName();
}


// ������ ������ � ������� �����ϰ� ������