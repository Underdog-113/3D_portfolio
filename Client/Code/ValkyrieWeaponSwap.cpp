#include "stdafx.h"
#include "ValkyrieWeaponSwap.h"

std::wstring CValkyrieWeaponSwap::g_selectWeaponName = L"";
CValkyrieWeaponSwap::CValkyrieWeaponSwap()
{
}

CValkyrieWeaponSwap::~CValkyrieWeaponSwap()
{
}

void CValkyrieWeaponSwap::Start()
{
	std::cout << "무기시작" << std::endl;
	
	CValkyriegManager::GetInstance()->GetScene()->FindObjectByName(L"WeaponSwapCanvas")->SetIsEnabled(true);
	m_scene = CValkyriegManager::GetInstance()->GetScene();

	// 내가 가지고있는 무기 목록 스크롤뷰에 쫘악 그리기
	// 무기를 클릭하면 해당 무기의 이름을 selectWeaponName에다가 넣어준다.
	SP(CScrollViewObject) spScrollView = std::dynamic_pointer_cast<CScrollViewObject>(CValkyriegManager::GetInstance()->GetScene()->FindObjectByName(L"WeaponSwapCanvas_ScrollView_0"));
	

	CValkyrieStatusData* valkyrieData = CDataManager::GetInstance()->FindInStockValkyrieData(CValkyriegManager::g_selectValkyrie);
	std::vector<CWeaponData*> weaponData = CDataManager::GetInstance()->FindWeaponData();
	_size weaponDataSize = weaponData.size();

	_int count = 0;
	for (_int i = 0; i < weaponDataSize; i++)
	{
		if (valkyrieData->GetWeaponType() == weaponData[i]->GetWeaponType())
		{
			if(valkyrieData->GetWeaponData()->GetName() == weaponData[i]->GetName())
				spScrollView->AddButtonObjectData<void(CValkyrieWeaponSwap::*)(), CValkyrieWeaponSwap*>(&CValkyrieWeaponSwap::SelectWeapon, this,
					_float2(135.5f, 173.4f), weaponData[i]->GetName(), L"UI_5", L"UI_5");
			else
				spScrollView->AddButtonObjectData<void(CValkyrieWeaponSwap::*)(), CValkyrieWeaponSwap*>(&CValkyrieWeaponSwap::SelectWeapon, this,
					_float2(135.5f, 173.4f), weaponData[i]->GetName(), L"UI_4", L"UI_4");


			spScrollView->AddImageObjectData(count, weaponData[i]->GetTextureKey(), _float3(129.0f, 122.1f, 0), _float2(0.0f, 17.2f));

			spScrollView->AddTextObjectData(count, _float2(-23.9f, -69.3f), 35, D3DXCOLOR(0, 0, 0, 1), L"LV." + std::to_wstring(weaponData[i]->GetLevel()));

			count++;
		}
	}


}

void CValkyrieWeaponSwap::End()
{
	CValkyriegManager::GetInstance()->GetScene()->FindObjectByName(L"WeaponSwapCanvas")->SetIsEnabled(false);
	std::dynamic_pointer_cast<CScrollViewObject>(CValkyriegManager::GetInstance()->GetScene()->FindObjectByName(L"WeaponSwapCanvas_ScrollView_0"))->AllDelete();
}

_uint CValkyrieWeaponSwap::FixedUpdate()
{
	return _uint();
}

_uint CValkyrieWeaponSwap::Update()
{
	return _uint();
}

_uint CValkyrieWeaponSwap::LateUpdate()
{
	return _uint();
}

void CValkyrieWeaponSwap::OnDestroy(void)
{
}

void CValkyrieWeaponSwap::SelectWeapon()
{
	g_selectWeaponName = CButtonManager::GetInstance()->GetActivationButton()->GetName();
}

void CValkyrieWeaponSwap::WeaponChange()
{
	CValkyrieStatusData* valkyrieData = CDataManager::GetInstance()->FindInStockValkyrieData(CValkyriegManager::g_selectValkyrie);
	valkyrieData->SetWeaponData(CDataManager::GetInstance()->FindWeaponData(g_selectWeaponName));
	valkyrieData->SetDamage(valkyrieData->GetDamage() + valkyrieData->GetWeaponData()->GetDamage());
	valkyrieData->SetHoesim(valkyrieData->GetHoesim() + valkyrieData->GetWeaponData()->GetHoesim());
	valkyrieData->SetBattlePower(valkyrieData->GetDamage() + valkyrieData->GetHoesim() + valkyrieData->GetWeaponData()->GetDamage() + valkyrieData->GetWeaponData()->GetHoesim());

	CValkyriegManager::GetInstance()->ChangeFSMWeapon();
}
