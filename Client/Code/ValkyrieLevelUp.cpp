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
	g_itemCount = 0;
	CValkyriegManager::GetInstance()->GetScene()->FindObjectByName(L"LevelUpCanvas")->SetIsEnabled(true);
	CValkyriegManager::GetInstance()->GetScene()->FindObjectByName(L"LevelUpCanvas_Text_4")->GetComponent<Engine::CTextC>()->ChangeMessage(std::to_wstring(CDataManager::GetInstance()->FindInStockValkyrieData(CValkyriegManager::g_selectValkyrie)->GetLevel()));

	ItemCountUp();

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
	CValkyrieStatusData* data = CDataManager::GetInstance()->FindInStockValkyrieData(CValkyriegManager::g_selectValkyrie);

	//100은 내가 선택한 아이템의 경험치만큼 오르게 변경
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
	g_itemCount = 0;
	CValkyriegManager::GetInstance()->ChangeFSMProperty();
}

void CValkyrieLevelUp::ItemCountUp()
{
	g_itemCount++;

	CValkyriegManager::GetInstance()->GetScene()->FindObjectByName(L"LevelUpCanvas_Text_7")->GetComponent<Engine::CTextC>()->ChangeMessage(std::to_wstring(g_itemCount));
	std::static_pointer_cast<Engine::CSlider>(CValkyriegManager::GetInstance()->GetScene()->FindObjectByName(L"LevelUpCanvas_Slider_0"))->SetValue((_float)g_itemCount);

	ItemCountUiHelp();
}

void CValkyrieLevelUp::ItemCountDown()
{
	g_itemCount--;

	if (g_itemCount <= 0)
		g_itemCount = 1;

	CValkyriegManager::GetInstance()->GetScene()->FindObjectByName(L"LevelUpCanvas_Text_7")->GetComponent<Engine::CTextC>()->ChangeMessage(std::to_wstring(g_itemCount));
	std::static_pointer_cast<Engine::CSlider>(CValkyriegManager::GetInstance()->GetScene()->FindObjectByName(L"LevelUpCanvas_Slider_0"))->SetValue((_float)g_itemCount);

	ItemCountUiHelp();
}

void CValkyrieLevelUp::ItemSelect()
{
	// 어떤 아이템을 쓸건인지
	g_selectItemName = CButtonManager::GetInstance()->GetActivationButton()->GetName();
}

void CValkyrieLevelUp::ItemCountUiHelp()
{
	CValkyrieStatusData* data = CDataManager::GetInstance()->FindInStockValkyrieData(CValkyriegManager::g_selectValkyrie);

	_int expSum = data->GetExperience() + (100 * g_itemCount);
	_int levalUpSum = data->GetLevel();
	_int nextExp = data->GetMaxExperience();

	CValkyriegManager::GetInstance()->GetScene()->FindObjectByName(L"LevelUpCanvas_Text_2")->GetComponent<Engine::CTextC>()->ChangeMessage(std::to_wstring(expSum - data->GetExperience()));
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


// 아이템 셀렉후 몇개 사용할지 지정하고 레벨업