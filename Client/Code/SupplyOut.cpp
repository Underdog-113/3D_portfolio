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
	m_production = true;

	Engine::CSoundManager::GetInstance()->StopSound((_uint)Engine::EChannelID::UI_ButtonUI);
	Engine::CSoundManager::GetInstance()->StartSound(L"GachaBoxStart.wav", (_uint)Engine::EChannelID::UI_ButtonUI);

	m_outCount = CSupplyManager::GetInstance()->GetOutCount();
	m_itemType = CSupplyManager::GetInstance()->GetSupplyOldState();

	Engine::GET_CUR_SCENE->FindObjectByName(L"BackGroundCanvas")->SetIsEnabled(false);
	Engine::GET_CUR_SCENE->FindObjectByName(L"SelectCanvas")->SetIsEnabled(false);
	Engine::GET_CUR_SCENE->FindObjectByName(L"MainCanvas")->SetIsEnabled(false);
	Engine::GET_CUR_SCENE->FindObjectByName(L"SupplyCanvas")->SetIsEnabled(false);
	Engine::GET_CUR_SCENE->FindObjectByName(L"OutCanvas")->SetIsEnabled(false);

	m_scrollView = static_cast<CScrollViewObject*>(Engine::GET_CUR_SCENE->FindObjectByName(L"OutCanvas_ScrollView_0").get());
	m_scrollView->AllDelete();

	m_timer = 0.3f;


	SP(Engine::CObject) box = Engine::GET_CUR_SCENE->GetObjectFactory()->AddClone(L"DecoObject", true, (_uint)ELayerID::Player, L"box");
	box->GetComponent<Engine::CTransformC>()->AddPositionY(-1.1f);
	box->GetComponent<Engine::CMeshC>()->SetMeshData(L"GachaBox");
	box->GetComponent<Engine::CMeshC>()->SetInitTex(true);
	box->GetComponent<Engine::CShaderC>()->AddShader((_int)Engine::EShaderID::MeshShader);
	box->GetComponent<Engine::CGraphicsC>()->SetRenderID((_int)Engine::ERenderID::NonAlpha);
	box->AddComponent<CGachBoxC>()->SetProduction(&m_production);

	SP(Engine::CObject) gachaMap = Engine::GET_CUR_SCENE->GetObjectFactory()->AddClone(L"DecoObject", true, (_uint)ELayerID::Player, L"map");
	gachaMap->GetComponent<Engine::CMeshC>()->SetMeshData(L"GachaMap");
	gachaMap->GetComponent<Engine::CMeshC>()->SetInitTex(true);
	gachaMap->GetComponent<Engine::CShaderC>()->AddShader((_int)Engine::EShaderID::MeshShader);
	gachaMap->GetComponent<Engine::CGraphicsC>()->SetRenderID((_int)Engine::ERenderID::NonAlpha);


	if (m_itemType == 0)
		WeaponRandoBoxList();
	else if (m_itemType == 1)
		ItemRandoBoxList();
}

void CSupplyOut::End()
{
	Engine::GET_CUR_SCENE->FindObjectByName(L"box")->SetDeleteThis(true);
	Engine::GET_CUR_SCENE->FindObjectByName(L"map")->SetDeleteThis(true);

	Engine::GET_CUR_SCENE->FindObjectByName(L"BackGroundCanvas")->SetIsEnabled(true);
	Engine::GET_CUR_SCENE->FindObjectByName(L"MainCanvas")->SetIsEnabled(true);
	Engine::GET_CUR_SCENE->FindObjectByName(L"SupplyCanvas")->SetIsEnabled(true);
	Engine::GET_CUR_SCENE->FindObjectByName(L"OutCanvas")->SetIsEnabled(false);
}

_uint CSupplyOut::FixedUpdate()
{
	return _uint();
}

_uint CSupplyOut::Update()
{
	if (m_production)
	{

	}
	else if (!m_production)
	{
		if (m_itemType == 0)
			WeaponRandomBox();
		else if (m_itemType == 1)
			ItemRandomBox();
	}

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
		m_timer = 0.3f;
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

		m_scrollView->AddTextObjectData(size, _float2(-25.1f, -74.1f), 25, D3DXCOLOR(0.1960784f, 0.1960784f, 0.1960784f, 1), L"×" + std::to_wstring(item.m_count));


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

		Engine::CSoundManager::GetInstance()->StopSound((_uint)Engine::EChannelID::UI_ButtonUI);
		Engine::CSoundManager::GetInstance()->StartSound(L"GachaBoxEnd.wav", (_uint)Engine::EChannelID::UI_ButtonUI);
	}
}

void CSupplyOut::WeaponRandomBox()
{
	m_timer -= GET_DT;

	if (m_timer <= 0 && m_itemList.size() != 0)
	{
		m_timer = 0.3f;
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

		Engine::CSoundManager::GetInstance()->StopSound((_uint)Engine::EChannelID::UI_ButtonUI);
		Engine::CSoundManager::GetInstance()->StartSound(L"GachaBoxEnd.wav", (_uint)Engine::EChannelID::UI_ButtonUI);

	}
}

void CSupplyOut::ItemRandoBoxList()
{
	for (int i = 0; i < m_outCount; i++)
	{
		ItemList();
	}
}

void CSupplyOut::WeaponRandoBoxList()
{
	for (int i = 0; i < m_outCount; i++)
	{
		WeaponList();
	}
}

void CSupplyOut::ItemList()
{
	_int value = rand() % 4;
	switch (value)
	{
	case 0:
		m_itemList.emplace_back(ItemInfo(L"하급 학습 칩", 1));
		break;
	case 1:
		m_itemList.emplace_back(ItemInfo(L"특급 학습 칩", 1));
		break;
	case 2:
		m_itemList.emplace_back(ItemInfo(L"고급 학습 칩", 1));
		break;
	case 3:
		m_itemList.emplace_back(ItemInfo(L"무기 강화제", 1));
		break;
	}

}

void CSupplyOut::WeaponList()
{
	_int value = rand() % 30;

	switch (value)
	{
	case 0:
		m_itemList.emplace_back(ItemInfo(L"11th 성유물", 1));
		break;
	case 1:
		m_itemList.emplace_back(ItemInfo(L"USP45", 1));
		break;
	case 2:
		m_itemList.emplace_back(ItemInfo(L"개량형 USP", 1));
		break;
	case 3:
		m_itemList.emplace_back(ItemInfo(L"고주파 절단도", 1));
		break;
	case 4:
		m_itemList.emplace_back(ItemInfo(L"흑쇄 분쇄자", 1));
		break;
	case 5:
		m_itemList.emplace_back(ItemInfo(L"화염의 천사", 1));
		break;
	case 6:
		m_itemList.emplace_back(ItemInfo(L"호리카와 쿠니히로", 1));
		break;
	case 7:
		m_itemList.emplace_back(ItemInfo(L"프로토 펄스 권총", 1));
		break;
	case 8:
		m_itemList.emplace_back(ItemInfo(L"파프닐의 폭염", 1));
		break;
	case 9:
		m_itemList.emplace_back(ItemInfo(L"토르의 망치", 1));
		break;
	case 10:
		m_itemList.emplace_back(ItemInfo(L"콜트·피스 메이커", 1));
		break;
	case 11:
		m_itemList.emplace_back(ItemInfo(L"초전자 핸드건", 1));
		break;
	case 12:
		m_itemList.emplace_back(ItemInfo(L"십자가·빙결탄", 1));
		break;
	case 13:
		m_itemList.emplace_back(ItemInfo(L"저주파 절단도", 1));
		break;
	case 14:
		m_itemList.emplace_back(ItemInfo(L"잭 오 랜턴", 1));
		break;
	case 15:
		m_itemList.emplace_back(ItemInfo(L"유다의 서약", 1));
		break;
	case 16:
		m_itemList.emplace_back(ItemInfo(L"아이쨩 캔디", 1));
		break;
	case 17:
		m_itemList.emplace_back(ItemInfo(L"영도·사쿠라 후부키", 1));
		break;
	case 18:
		m_itemList.emplace_back(ItemInfo(L"요도 무라마사", 1));
		break;
	case 19:
		m_itemList.emplace_back(ItemInfo(L"요도 아메무라", 1));
		break;
	case 20:
		m_itemList.emplace_back(ItemInfo(L"뇌절", 1));
		break;
	case 21:
		m_itemList.emplace_back(ItemInfo(L"새벽달의 진혼가", 1));
		break;
	case 22:
		m_itemList.emplace_back(ItemInfo(L"불의 요정 l 형", 1));
		break;
	case 23:
		m_itemList.emplace_back(ItemInfo(L"벚꽃의 서약", 1));
		break;
	case 24:
		m_itemList.emplace_back(ItemInfo(L"물의 요정 ll 형", 1));
		break;
	case 25:
		m_itemList.emplace_back(ItemInfo(L"물의 요정 l 형", 1));
		break;
	case 26:
		m_itemList.emplace_back(ItemInfo(L"묘도·뇌혼", 1));
		break;
	case 27:
		m_itemList.emplace_back(ItemInfo(L"묘도·뇌요", 1));
		break;
	case 28:
		m_itemList.emplace_back(ItemInfo(L"모조된 유다·피의 포옹", 1));
		break;
	case 29:
		m_itemList.emplace_back(ItemInfo(L"마그네틱 스톰·참", 1));
		break;
	}
}

/*
void CSupplyOut::RandoBoxList()
{
	for (int i = 0; i < m_outCount; i++)
	{
		m_itemList.emplace_back(ItemInfo(L"벚꽃의 서약", 1));
	}
}*/

/*
0은 무기
1은 재료

count만큼 소환

1. 박스오픈연출씨
2. 2개씩나오는 연출
3. 나온 아이템을 전부다 보여준다.
*/
