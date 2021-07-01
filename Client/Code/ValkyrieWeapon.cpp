#include "stdafx.h"
#include "ValkyrieWeapon.h"


CValkyrieWeapon::CValkyrieWeapon()
{
}

CValkyrieWeapon::~CValkyrieWeapon()
{
}

void CValkyrieWeapon::Start()
{
	std::cout << "무기시작" <<  std::endl;

	m_scene = CValkyriegManager::GetInstance()->GetScene();

	Delegate<> delegate;
	delegate += std::bind(&CValkyrieWeapon::ChangeSelect, &CValkyrieWeapon());

	std::static_pointer_cast<CButton>(CValkyriegManager::GetInstance()->GetScene()->FindObjectByName(L"MainCanvas_Button_1"))->
		AddFuncData(delegate);

	WeaponCanvas();
}

void CValkyrieWeapon::End()
{
	std::cout << "무기끝" << std::endl;
}

_uint CValkyrieWeapon::FixedUpdate()
{
	return _uint();
}

_uint CValkyrieWeapon::Update()
{
	return _uint();
}

_uint CValkyrieWeapon::LateUpdate()
{
	return _uint();
}

void CValkyrieWeapon::OnDestroy(void)
{
}

void CValkyrieWeapon::WeaponCanvas()
{
	m_scene->FindObjectByName(L"WeaponCanvas")->SetIsEnabled(true);
	m_scene->FindObjectByName(L"PropertyCanvas")->SetIsEnabled(false);
	m_scene->FindObjectByName(L"ValkyrieCanvas")->SetIsEnabled(false);
	CValkyrieStatusData* data = CDataManager::GetInstance()->FindInStockValkyrieData(CValkyriegManager::g_selectValkyrie);

	DataInput(L"WeaponCanvas_Text_0", data->GetWeaponData()->GetName());
	DataInput(L"WeaponCanvas_Text_3", L"LV." + std::to_wstring(data->GetWeaponData()->GetLevel()));

	DataInput(L"WeaponCanvas_Text_17", L"LV." + std::to_wstring(data->GetLevel()));
	DataInput(L"WeaponCanvas_Text_16", data->GetSubName());
	DataInput(L"WeaponCanvas_Text_18", std::to_wstring(data->GetBattlePower()));

	m_scene->FindObjectByName(L"WeaponCanvas_Image_4")->GetComponent<Engine::CTextureC>()->ChangeTexture(data->GetProperty());

	for (int i = 0; i < 4; i++)
	{
		std::wstring textureKey = L"";
		if (i < data->GetWeaponData()->GetRank())
			textureKey = L"StarBig";
		else
			textureKey = L"StarBigGray";

		m_scene->FindObjectByName(L"WeaponCanvas_Image_" + std::to_wstring(5 + i))->GetComponent<Engine::CTextureC>()->ChangeTexture(textureKey);

	}

	
}

void CValkyrieWeapon::ChangeSelect()
{
	CValkyriegManager::GetInstance()->GetScene()->FindObjectByName(L"PropertyCanvas")->SetIsEnabled(false);
	CValkyriegManager::GetInstance()->GetScene()->FindObjectByName(L"ValkyrieCanvas")->SetIsEnabled(true);
	CValkyriegManager::GetInstance()->ChangeFSMSelect();

}

void CValkyrieWeapon::DataInput(std::wstring objectName, std::wstring  dataValue)
{
	m_scene->FindObjectByName(objectName)->GetComponent<Engine::CTextC>()->ChangeMessage(dataValue);

}