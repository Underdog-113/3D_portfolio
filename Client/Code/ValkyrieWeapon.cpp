#include "stdafx.h"
#include "ValkyrieWeapon.h"

#include "ClientScene.h"
#include "KianaUIAnim.h"


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


	CValkyrieStatusData* data;

	data = CDataManager::GetInstance()->FindInStockValkyrieData(CValkyriegManager::g_selectValkyrie);

	if (m_vPlayer != nullptr)
		m_vPlayer->SetDeleteThis(true);

	std::wstring name = data->GetName();
	if (name == L"키아나·카스라나")
	{
		// 키아나 오브젝트 생성 -> IDLE로 변경
		m_vPlayer = m_scene->GetObjectFactory()->AddClone(L"KianaUIAnim", true, (_int)ELayerID::Player, L"");
		m_vPlayer->GetComponent<Engine::CTransformC>()->SetPosition(_float3(-1.61499858f, -2.75000310f, -1.07500005f));
		m_vPlayer->GetComponent<Engine::CTransformC>()->SetRotation(_float3(0, D3DXToRadian(180.0f), 0));
		m_vPlayer->GetComponent<Engine::CTransformC>()->SetSize(_float3(2.f, 2.f, 2.f));
	}
	else if (name == L"테레사·아포칼립스")
	{
		// 테레사 오브젝트 생성 -> IDLE로 변경
		m_vPlayer = m_scene->GetObjectFactory()->AddClone(L"KianaUIAnim", true, (_int)ELayerID::Player, L"");
		static_cast<CKianaUIAnim*>(m_vPlayer.get())->SetTextureName(L"Theresa_Wp");
		m_vPlayer->GetComponent<Engine::CTransformC>()->SetPosition(_float3(-0.535000920f, -0.799999893f, -3.64999032f));
		m_vPlayer->GetComponent<Engine::CTransformC>()->SetRotation(_float3(0, D3DXToRadian(180.0f), 0));
		m_vPlayer->GetComponent<Engine::CTransformC>()->SetSize(_float3(1.f, 1.f, 1.f));
	}
	else if (name == L"야에 사쿠라")
	{
		// 사쿠라 오브젝트 생성 -> IDLE로 변경
		m_vPlayer = m_scene->GetObjectFactory()->AddClone(L"KianaUIAnim", true, (_int)ELayerID::Player, L"");
		static_cast<CKianaUIAnim*>(m_vPlayer.get())->SetTextureName(L"Sakura_Wp");
		m_vPlayer->GetComponent<Engine::CTransformC>()->SetPosition(_float3(-0.305001855f, -0.534999609f, -4.28503370f));
		m_vPlayer->GetComponent<Engine::CTransformC>()->SetRotation(_float3(0, D3DXToRadian(180.0f), 0));
		m_vPlayer->GetComponent<Engine::CTransformC>()->SetSize(_float3(1.f, 1.f, 1.f));
	}
}

void CValkyrieWeapon::End()
{
	std::cout << "무기끝" << std::endl;
	if (m_vPlayer != nullptr)
		m_vPlayer->SetDeleteThis(true);
}

_uint CValkyrieWeapon::FixedUpdate()
{
	return _uint();
}

_uint CValkyrieWeapon::Update()
{
	_float x = m_vPlayer->GetComponent<Engine::CTransformC>()->GetPosition().x;
	_float y = m_vPlayer->GetComponent<Engine::CTransformC>()->GetPosition().y;
	_float z = m_vPlayer->GetComponent<Engine::CTransformC>()->GetPosition().z;

	if (Engine::CInputManager::GetInstance()->KeyPress(KEY_W))
	{
		m_vPlayer->GetComponent<Engine::CTransformC>()->AddPositionY(0.005f);
	}
	if (Engine::CInputManager::GetInstance()->KeyPress(KEY_S))
	{
		m_vPlayer->GetComponent<Engine::CTransformC>()->AddPositionY(-0.005f);
	}
	if (Engine::CInputManager::GetInstance()->KeyPress(KEY_A))
	{
		m_vPlayer->GetComponent<Engine::CTransformC>()->AddPositionX(0.005f);
	}
	if (Engine::CInputManager::GetInstance()->KeyPress(KEY_D))
	{
		m_vPlayer->GetComponent<Engine::CTransformC>()->AddPositionX(-0.005f);
	}
	if (Engine::CInputManager::GetInstance()->KeyPress(KEY_Q))
	{
		m_vPlayer->GetComponent<Engine::CTransformC>()->AddPositionZ(0.005f);
	}
	if (Engine::CInputManager::GetInstance()->KeyPress(KEY_E))
	{
		m_vPlayer->GetComponent<Engine::CTransformC>()->AddPositionZ(-0.005f);
	}

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

	m_scene->FindObjectByName(L"WeaponCanvas_Image_9")->GetComponent<Engine::CTextureC>()->ChangeTexture(data->GetWeaponData()->GetTextureKey());
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