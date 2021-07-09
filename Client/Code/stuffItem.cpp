#include "stdafx.h"
#include "StuffItem.h"

#include "ButtonFunction.h"
#include "ClientScene.h"

#include "InventoryManager.h"

#include "ScrollViewObject.h"
#include "ImageObject.h"
#include "Button.h"

CStuffItem::CStuffItem()
{

}

CStuffItem::~CStuffItem()
{
}

void CStuffItem::Start()
{
	
	std::vector<CItemData*> stuffItem = CDataManager::GetInstance()->FindItemData();
	_size size = stuffItem.size();

	CScrollViewObject* spScrollView = static_cast<CScrollViewObject*>(CInventoryManager::GetInstance()->GetScene()->FindObjectByName(L"MainCanvas_ScrollView_0").get());

	for (int i = 0; i < size; i++)
	{
		spScrollView->
			AddButtonObjectData<void(CStuffItem::*)(), CStuffItem*>(&CStuffItem::InformationWindow, &CStuffItem(),
				_float2(172.0f, 205.0f), stuffItem[i]->GetName(), L"UI_4", L"UI_4");

		spScrollView->
			AddImageObjectData(i, stuffItem[i]->GetTextureKey(), _float3(163.7f, 143.6f, 0.0f), _float2(0, 20));

		_float2 offset = _float2(-18.0f * (_int)(stuffItem[i]->GetRank() * 0.5f), -51.4f);
		for (int j = 0; j < stuffItem[i]->GetRank(); j++)
		{
			spScrollView->
				AddImageObjectData(i, L"StarBig", _float3(26.3f, 26.3f, 0.0f), offset);
			offset.x += 25.0f;
		}

		spScrollView->
			AddTextObjectData(i, _float2(-27.2f, -81.9f), 30, D3DXCOLOR(0.1960784f, 0.1960784f, 0.1960784f, 1), L"¡¿" + std::to_wstring(stuffItem[i]->GetCount()));

	}
}

void CStuffItem::End()
{
	CScrollViewObject* spScrollView = static_cast<CScrollViewObject*>(CInventoryManager::GetInstance()->GetScene()->FindObjectByName(L"MainCanvas_ScrollView_0").get());
	spScrollView->AllDelete();
}

_uint CStuffItem::FixedUpdate()
{
	return _uint();
}

_uint CStuffItem::Update()
{
	return _uint();
}

_uint CStuffItem::LateUpdate()
{
	return _uint();
}

void CStuffItem::OnDestroy(void)
{
}

void CStuffItem::InformationWindow()
{
}
