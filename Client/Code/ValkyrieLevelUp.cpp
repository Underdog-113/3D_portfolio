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
	/* 버튼함수 (확인)
	아이템을 없애고 겸험치를 올리는 함수
	*/

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
	g_itemCount = 1;
	CValkyriegManager::GetInstance()->ChangeFSMProperty();
}

void CValkyrieLevelUp::ItemCountUp()
{
	/* 버튼함수 (+)
	아이템의 사용갯수와 경험치 증가량을 올리는 함수
	// 아이템의 갯수를 확인하여 레벨없이 되는지 경험치가 몇획득하는지 체크하여 UI를 게속 변경
	*/
	// 선택한 아이템의 갯수 이상 못올라가게 수정
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


	// 아이템 수량 변경
	// 슬라이더 벨류값 변경
}

void CValkyrieLevelUp::ItemCountDown()
{
	/* 버튼함수 (-)
	아이템의 사용갯수를 내리고 경험치 증가량을 내리는 함수
	// 아이템의 갯수를 확인하여 레벨없이 되는지 경험치가 몇획득하는지 체크하여 UI를 게속 변경
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
	// 어떤 아이템을 쓸건인지
	g_selectItemName = CButtonManager::GetInstance()->GetActivationButton()->GetName();
}


// 아이템 셀렉후 몇개 사용할지 지정하고 레벨업