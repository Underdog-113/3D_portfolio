#include "stdafx.h"
#include "WaponItem.h"

#include "ButtonFunction.h"
#include "ClientScene.h"

#include "InventoryManager.h"

#include "ScrollViewObject.h"
#include "ImageObject.h"
#include "Button.h"

CWaponItem::CWaponItem()
{

}


CWaponItem::~CWaponItem()
{
}

void CWaponItem::Start()
{

	std::vector<CWeaponData*> weaponData = CDataManager::GetInstance()->FindWeaponData();
	_size size = weaponData.size();

	CScrollViewObject* spScrollView = static_cast<CScrollViewObject*>(CInventoryManager::GetInstance()->GetScene()->FindObjectByName(L"MainCanvas_ScrollView_0").get());
	
	for (int i = 0; i < size; i++)
	{
		spScrollView->
			AddButtonObjectData<void(CWaponItem::*)(), CWaponItem*>(&CWaponItem::InformationWindow, &CWaponItem(),
				_float2(172.0f, 205.0f), weaponData[i]->GetName(), L"UI_4", L"UI_4");
		
		spScrollView->
			AddImageObjectData(i, weaponData[i]->GetTextureKey(), _float3(163.7f, 143.6f, 0.0f), _float2(0, 26));

		// 별달고 레벨달고
		spScrollView->
			AddTextObjectData(i, _float2(0, 0), 30, D3DXCOLOR(1, 1, 1, 1), std::to_wstring(weaponData[i]->GetLevel()));
	}
}

void CWaponItem::End()
{
	_int end = 10;
}

_uint CWaponItem::FixedUpdate()
{
	return _uint();
}

_uint CWaponItem::Update()
{
	return _uint();
}

_uint CWaponItem::LateUpdate()
{
	return _uint();
}

void CWaponItem::OnDestroy(void)
{
}

void CWaponItem::InformationWindow()
{
}
