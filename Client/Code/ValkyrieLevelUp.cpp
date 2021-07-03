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
	if (CDataManager::GetInstance()->FindItemData().size() == 0)
	{
		CValkyriegManager::GetInstance()->ChangeFSMProperty();
		return;
	}

	g_itemCount = 0;

	CValkyriegManager::GetInstance()->GetScene()->FindObjectByName(L"LevelUpCanvas")->SetIsEnabled(true);
	CValkyriegManager::GetInstance()->GetScene()->FindObjectByName(L"LevelUpCanvas_Text_4")->GetComponent<Engine::CTextC>()->ChangeMessage(std::to_wstring(CDataManager::GetInstance()->FindInStockValkyrieData(CValkyriegManager::g_selectValkyrie)->GetLevel()));
	ItemButtonSetting();
	ItemCountUp();

	std::static_pointer_cast<Engine::CSlider>(CValkyriegManager::GetInstance()->GetScene()->FindObjectByName(L"LevelUpCanvas_Slider_0"))->SetMaxValue((_float)CDataManager::GetInstance()->FindItemData(g_selectItemName)->GetCount());
}

void CValkyrieLevelUp::End()
{
	CValkyriegManager::GetInstance()->GetScene()->FindObjectByName(L"LevelUpCanvas")->SetIsEnabled(false);


	for (auto& obj : m_spItemButtonObject)
	{
		obj->SetDeleteThis(true);
	}
	m_spItemButtonObject.clear();
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
	
	_int expSum = data->GetExperience() + (CDataManager::GetInstance()->FindItemData(g_selectItemName)->GetExperience() * g_itemCount);
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
	data->LevelUp();
	CDataManager::GetInstance()->FindItemData(g_selectItemName)->CountDown(g_itemCount);
	g_itemCount = 0;
	CValkyriegManager::GetInstance()->ChangeFSMProperty();
}

void CValkyrieLevelUp::ItemCountUp()
{
	g_itemCount++;

	if (g_itemCount >= CDataManager::GetInstance()->FindItemData(g_selectItemName)->GetCount())
		g_itemCount = CDataManager::GetInstance()->FindItemData(g_selectItemName)->GetCount();

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

	_int expSum = data->GetExperience() + (CDataManager::GetInstance()->FindItemData(g_selectItemName)->GetExperience() * g_itemCount);
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

void CValkyrieLevelUp::ItemButtonSetting()
{
	std::vector<CItemData*> data = CDataManager::GetInstance()->FindItemData();
	size_t size = data.size();
	_float offsetX = 174.2f;
	_float3 statPos = _float3(-offsetX * (int)(size * 0.5f), 0, 0.7f);

	CValkyrieLevelUp::g_selectItemName = data[0]->GetName();

	for (int i = 0; i < size; i++)
	{
		SP(CItemButton) object;
		object = std::dynamic_pointer_cast<CItemButton>(CValkyriegManager::GetInstance()->GetScene()->GetObjectFactory()->AddClone(L"ItemButton", true, (_int)Engine::ELayerID::UI, L""));
		object->GetTransform()->SetPosition(statPos);
		object->SetItemName(data[i]->GetName());
		// 버튼
		object->ButtonCreate(data[i]->GetName(), _float3(0.0f, 0.0f, 0.0f), _float3(122.3f, 149.4f, 0), L"UI_4", CButton::UP);
		// 이미지
		object->ImageCreate(L"", _float3(0.0f, 16.3f, statPos.z), _float3(122.1f, 106.4f, 0), data[i]->GetTextureKey());
		// 텍스트
		object->textCreate(L"", _float2(0.0f, 62.1f), statPos.z, 28, D3DXCOLOR(0, 0, 0, 1), L"", L"×" + std::to_wstring(data[i]->GetCount()));

		object->GetButton()->AddFuncData<void(CItemButton::*)(), CItemButton*>(&CItemButton::ItemSelect, object.get());

		statPos.x += offsetX;
		m_spItemButtonObject.emplace_back(object);
	}

}
// 사이의 거리
// 시작위치
