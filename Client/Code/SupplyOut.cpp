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

		m_scrollView->AddTextObjectData(size, _float2(-25.1f, -74.1f), 25, D3DXCOLOR(0.1960784f, 0.1960784f, 0.1960784f, 1), L"��" + std::to_wstring(item.m_count));


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
		m_itemList.emplace_back(ItemInfo(L"�ϱ� �н� Ĩ", 1));
		break;
	case 1:
		m_itemList.emplace_back(ItemInfo(L"Ư�� �н� Ĩ", 1));
		break;
	case 2:
		m_itemList.emplace_back(ItemInfo(L"��� �н� Ĩ", 1));
		break;
	case 3:
		m_itemList.emplace_back(ItemInfo(L"���� ��ȭ��", 1));
		break;
	}

}

void CSupplyOut::WeaponList()
{
	_int value = rand() % 30;

	switch (value)
	{
	case 0:
		m_itemList.emplace_back(ItemInfo(L"11th ������", 1));
		break;
	case 1:
		m_itemList.emplace_back(ItemInfo(L"USP45", 1));
		break;
	case 2:
		m_itemList.emplace_back(ItemInfo(L"������ USP", 1));
		break;
	case 3:
		m_itemList.emplace_back(ItemInfo(L"������ ���ܵ�", 1));
		break;
	case 4:
		m_itemList.emplace_back(ItemInfo(L"��� �м���", 1));
		break;
	case 5:
		m_itemList.emplace_back(ItemInfo(L"ȭ���� õ��", 1));
		break;
	case 6:
		m_itemList.emplace_back(ItemInfo(L"ȣ��ī�� �������", 1));
		break;
	case 7:
		m_itemList.emplace_back(ItemInfo(L"������ �޽� ����", 1));
		break;
	case 8:
		m_itemList.emplace_back(ItemInfo(L"�������� ����", 1));
		break;
	case 9:
		m_itemList.emplace_back(ItemInfo(L"�丣�� ��ġ", 1));
		break;
	case 10:
		m_itemList.emplace_back(ItemInfo(L"��Ʈ���ǽ� ����Ŀ", 1));
		break;
	case 11:
		m_itemList.emplace_back(ItemInfo(L"������ �ڵ��", 1));
		break;
	case 12:
		m_itemList.emplace_back(ItemInfo(L"���ڰ�������ź", 1));
		break;
	case 13:
		m_itemList.emplace_back(ItemInfo(L"������ ���ܵ�", 1));
		break;
	case 14:
		m_itemList.emplace_back(ItemInfo(L"�� �� ����", 1));
		break;
	case 15:
		m_itemList.emplace_back(ItemInfo(L"������ ����", 1));
		break;
	case 16:
		m_itemList.emplace_back(ItemInfo(L"����» ĵ��", 1));
		break;
	case 17:
		m_itemList.emplace_back(ItemInfo(L"����������� �ĺ�Ű", 1));
		break;
	case 18:
		m_itemList.emplace_back(ItemInfo(L"�䵵 ���󸶻�", 1));
		break;
	case 19:
		m_itemList.emplace_back(ItemInfo(L"�䵵 �Ƹ޹���", 1));
		break;
	case 20:
		m_itemList.emplace_back(ItemInfo(L"����", 1));
		break;
	case 21:
		m_itemList.emplace_back(ItemInfo(L"�������� ��ȥ��", 1));
		break;
	case 22:
		m_itemList.emplace_back(ItemInfo(L"���� ���� l ��", 1));
		break;
	case 23:
		m_itemList.emplace_back(ItemInfo(L"������ ����", 1));
		break;
	case 24:
		m_itemList.emplace_back(ItemInfo(L"���� ���� ll ��", 1));
		break;
	case 25:
		m_itemList.emplace_back(ItemInfo(L"���� ���� l ��", 1));
		break;
	case 26:
		m_itemList.emplace_back(ItemInfo(L"��������ȥ", 1));
		break;
	case 27:
		m_itemList.emplace_back(ItemInfo(L"����������", 1));
		break;
	case 28:
		m_itemList.emplace_back(ItemInfo(L"������ ���١����� ����", 1));
		break;
	case 29:
		m_itemList.emplace_back(ItemInfo(L"���׳�ƽ ���衤��", 1));
		break;
	}
}

/*
void CSupplyOut::RandoBoxList()
{
	for (int i = 0; i < m_outCount; i++)
	{
		m_itemList.emplace_back(ItemInfo(L"������ ����", 1));
	}
}*/

/*
0�� ����
1�� ���

count��ŭ ��ȯ

1. �ڽ����¿��⾾
2. 2���������� ����
3. ���� �������� ���δ� �����ش�.
*/
