#include "stdafx.h"
#include "SupplyOut.h"
#include "StuffItem.h"

CSupplyOut::CSupplyOut()
{

}

CSupplyOut::~CSupplyOut()
{
}

void CSupplyOut::Start()
{
	_int a = CSupplyManager::GetInstance()->GetOutCount();
	_int b = CSupplyManager::GetInstance()->GetSupplyOldState();

	Engine::GET_CUR_SCENE->FindObjectByName(L"OutCanvas")->SetIsEnabled(true);
	Engine::GET_CUR_SCENE->FindObjectByName(L"MainCanvas_Button_2")->SetIsEnabled(false);
	Engine::GET_CUR_SCENE->FindObjectByName(L"MainCanvas_Button_3")->SetIsEnabled(false);

	m_scrollView = static_cast<CScrollViewObject*>(Engine::GET_CUR_SCENE->FindObjectByName(L"OutCanvas_ScrollView_0").get());
	m_scrollView->AllDelete();

	m_timer = 1.0f;
	RandoBoxList();
}

void CSupplyOut::End()
{
	Engine::GET_CUR_SCENE->FindObjectByName(L"OutCanvas")->SetIsEnabled(false);
	Engine::GET_CUR_SCENE->FindObjectByName(L"MainCanvas_Button_2")->SetIsEnabled(true);
	Engine::GET_CUR_SCENE->FindObjectByName(L"MainCanvas_Button_3")->SetIsEnabled(true);
}

_uint CSupplyOut::FixedUpdate()
{
	return _uint();
}

_uint CSupplyOut::Update()
{
	//ItemRandomBox();
	//WeaponRandomBox();
	return _uint();
}

_uint CSupplyOut::LateUpdate()
{
	return _uint();
}

void CSupplyOut::OnDestroy(void)
{
}
void CSupplyOut::ItemRandomBox()
{
	m_timer -= GET_DT;
	
	if (m_timer <= 0 && m_itemList.size() != 0)
	{
		m_timer = 1.0f;
		ItemInfo item = m_itemList.back();
		m_itemList.pop_back();

		CDataManager::GetInstance()->ItemInit(item.m_name, item.m_count);

		m_scrollView->AddButtonObjectData<void(CStuffItem::*)(), CStuffItem*>(&CStuffItem::InformationWindow, &CStuffItem(),
			_float2(161.5f, 183.5f), item.m_name, L"UI_4", L"UI_4");

		_int size = (int)m_scrollView->GetButtonObject().size() - 1;
	
		m_scrollView->AddImageObjectData(size, CDataManager::GetInstance()->FindItemData(item.m_name)->GetTextureKey(), _float3(151.9f, 128.8f, 0), _float2(0.0f, 18.6f));

		_int rank = CDataManager::GetInstance()->FindItemData(item.m_name)->GetRank();
		_float2 offset = _float2(-15.7f * (_int)(rank * 0.5f), -46.1f);

		for (int i = 0; i < rank; i++)
		{
			m_scrollView->
				AddImageObjectData(size, L"StarBig", _float3(25.0f, 25.0f, 0.0f), offset, 0.01f);
			offset.x += 22.4f;
		}

		m_scrollView->AddTextObjectData(size, _float2(-25.1f, -74.1f), 25, D3DXCOLOR(0.1960784f, 0.1960784f, 0.1960784f, 1), L"°ø" + std::to_wstring(item.m_count));


		{
			Engine::CObject* a = m_scrollView->GetButtonObject().at(size).get();
			a->AddComponent<CSizeDownC>();
			a->GetComponent<CSizeDownC>()->SetSize(1.5f);
			a->GetComponent<CSizeDownC>()->SetSpeed(5);
		}

		{
			Engine::CObject* a = m_scrollView->GetImageObject().at(size).at(0).m_image.get();
			a->AddComponent<CSizeDownC>();
			a->GetComponent<CSizeDownC>()->SetSize(1.5f);
			a->GetComponent<CSizeDownC>()->SetSpeed(5);
		}
	}
}
void CSupplyOut::WeaponRandomBox()
{
	m_timer -= GET_DT;

	if (m_timer <= 0 && m_itemList.size() != 0)
	{
		m_timer = 1.0f;
		ItemInfo item = m_itemList.back();
		m_itemList.pop_back();

		CDataManager::GetInstance()->WeaponInit(item.m_name);

		m_scrollView->AddButtonObjectData<void(CStuffItem::*)(), CStuffItem*>(&CStuffItem::InformationWindow, &CStuffItem(),
			_float2(161.5f, 183.5f), item.m_name, L"UI_4", L"UI_4");

		_int size = (int)m_scrollView->GetButtonObject().size() - 1;

		m_scrollView->AddImageObjectData(size, CDataManager::GetInstance()->FindWeaponData(item.m_name)->GetTextureKey(), _float3(151.9f, 128.8f, 0), _float2(0.0f, 18.6f));

		_int rank = CDataManager::GetInstance()->FindItemData(item.m_name)->GetRank();
		_float2 offset = _float2(-15.7f * (_int)(rank * 0.5f), -46.1f);

		for (int i = 0; i < rank; i++)
		{
			m_scrollView->
				AddImageObjectData(size, L"StarBig", _float3(25.0f, 25.0f, 0.0f), offset, 0.01f);
			offset.x += 22.4f;
		}

		m_scrollView->AddTextObjectData(size, _float2(-25.1f, -74.1f), 25, D3DXCOLOR(0.1960784f, 0.1960784f, 0.1960784f, 1), L"LV." + std::to_wstring(item.m_count));

		{
			Engine::CObject* a = m_scrollView->GetButtonObject().at(size).get();
			a->AddComponent<CSizeDownC>();
			a->GetComponent<CSizeDownC>()->SetSize(1.5f);
			a->GetComponent<CSizeDownC>()->SetSpeed(5);
		}

		{
			Engine::CObject* a = m_scrollView->GetImageObject().at(size).at(0).m_image.get();
			a->AddComponent<CSizeDownC>();
			a->GetComponent<CSizeDownC>()->SetSize(1.5f);
			a->GetComponent<CSizeDownC>()->SetSpeed(5);
		}
	}
}

void CSupplyOut::RandoBoxList()
{
	m_itemList.emplace_back(ItemInfo(L"∫¢≤…¿« º≠æ‡", 50));
	m_itemList.emplace_back(ItemInfo(L"∫¢≤…¿« º≠æ‡", 50));
	m_itemList.emplace_back(ItemInfo(L"∫¢≤…¿« º≠æ‡", 50));
	m_itemList.emplace_back(ItemInfo(L"∫¢≤…¿« º≠æ‡", 50));
	m_itemList.emplace_back(ItemInfo(L"∫¢≤…¿« º≠æ‡", 50));
	m_itemList.emplace_back(ItemInfo(L"∫¢≤…¿« º≠æ‡", 50));
	m_itemList.emplace_back(ItemInfo(L"∫¢≤…¿« º≠æ‡", 50));
	m_itemList.emplace_back(ItemInfo(L"∫¢≤…¿« º≠æ‡", 50));
	m_itemList.emplace_back(ItemInfo(L"∫¢≤…¿« º≠æ‡", 50));
	m_itemList.emplace_back(ItemInfo(L"∫¢≤…¿« º≠æ‡", 50));
}
/*
0¿∫ π´±‚
1¿∫ ¿Á∑·

count∏∏≈≠ º“»Ø
*/
