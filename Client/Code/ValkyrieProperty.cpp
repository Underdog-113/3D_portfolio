#include "stdafx.h"
#include "ValkyrieProperty.h"

CValkyrieProperty::CValkyrieProperty()
{
}


CValkyrieProperty::~CValkyrieProperty()
{
}

void CValkyrieProperty::Start()
{
	m_scene = CValkyriegManager::GetInstance()->GetScene();

	// 뒤로가기 버튼 재설정
	Delegate<> delegate;
	delegate += std::bind(&CValkyrieProperty::ChangeSelect, &CValkyrieProperty());

	std::static_pointer_cast<CButton>(CValkyriegManager::GetInstance()->GetScene()->FindObjectByName(L"MainCanvas_Button_1"))->
		AddFuncData(delegate);
	// 데이터 셋팅

	PropertyCanvas();
}

void CValkyrieProperty::End()
{
}

_uint CValkyrieProperty::FixedUpdate()
{
	return _uint();
}

_uint CValkyrieProperty::Update()
{
	return _uint();
}

_uint CValkyrieProperty::LateUpdate()
{
	return _uint();
}

void CValkyrieProperty::OnDestroy(void)
{
}

void CValkyrieProperty::PropertyCanvas()
{
	m_scene->FindObjectByName(L"WeaponCanvas")->SetIsEnabled(false);
	m_scene->FindObjectByName(L"PropertyCanvas")->SetIsEnabled(true);
	CValkyrieStatusData* data = CDataManager::GetInstance()->FindInStockValkyrieData(CValkyriegManager::g_selectValkyrie);

	DataInput(L"PropertyCanvas_Text_2", std::to_wstring(data->GetHp()));
	DataInput(L"PropertyCanvas_Text_4", std::to_wstring(data->GetDamage() + data->GetWeaponData()->GetDamage()));
	DataInput(L"PropertyCanvas_Text_6", std::to_wstring(data->GetHoesim() + data->GetWeaponData()->GetHoesim()));
	DataInput(L"PropertyCanvas_Text_8", std::to_wstring(data->GetSp()));
	DataInput(L"PropertyCanvas_Text_10", std::to_wstring(data->GetDefense()));
	DataInput(L"PropertyCanvas_Text_11", std::to_wstring(data->GetExperience()) + L" / " + std::to_wstring(data->GetMaxExperience()));
	DataInput(L"PropertyCanvas_Text_17", L"LV." + std::to_wstring(data->GetLevel()));
	DataInput(L"PropertyCanvas_Text_16", data->GetSubName());
	DataInput(L"PropertyCanvas_Text_18", std::to_wstring(data->GetBattlePower()));
	m_scene->FindObjectByName(L"PropertyCanvas_Image_4")->GetComponent<Engine::CTextureC>()->ChangeTexture(data->GetProperty());

	//슬라이어 Max값 Value값 잡아주기
	std::static_pointer_cast<Engine::CSlider>(m_scene->FindObjectByName(L"PropertyCanvas_Slider_0"))->SetMaxValue((_float)data->GetMaxExperience());
	std::static_pointer_cast<Engine::CSlider>(m_scene->FindObjectByName(L"PropertyCanvas_Slider_0"))->SetValue((_float)data->GetExperience());
}

void CValkyrieProperty::ChangeSelect()
{
	CValkyriegManager::GetInstance()->GetScene()->FindObjectByName(L"PropertyCanvas")->SetIsEnabled(false);
	CValkyriegManager::GetInstance()->GetScene()->FindObjectByName(L"ValkyrieCanvas")->SetIsEnabled(true);
	CValkyriegManager::GetInstance()->ChangeFSMSelect();
}

void CValkyrieProperty::DataInput(std::wstring objectName, std::wstring  dataValue)
{
	m_scene->FindObjectByName(objectName)->GetComponent<Engine::CTextC>()->ChangeMessage(dataValue);

}

