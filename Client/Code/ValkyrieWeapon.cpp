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
	std::cout << "�������" <<  std::endl;

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
	if (name == L"Ű�Ƴ���ī����")
	{
		// Ű�Ƴ� ������Ʈ ���� -> IDLE�� ����
		m_vPlayer = m_scene->GetObjectFactory()->AddClone(L"KianaUIAnim", true, (_int)ELayerID::Player, L"");
		m_vPlayer->GetComponent<Engine::CTransformC>()->SetPosition(_float3(-1.61499858f, -2.75000310f, -1.07500005f));
		m_vPlayer->GetComponent<Engine::CTransformC>()->SetRotation(_float3(0, D3DXToRadian(180.0f), 0));
		m_vPlayer->GetComponent<Engine::CTransformC>()->SetSize(_float3(2.f, 2.f, 2.f));

		SP(Engine::CShaderC) spShader = m_vPlayer->GetComponent<Engine::CShaderC>();
		spShader->AddShader((_int)EShaderID::OutlineShader);

		spShader->ResizeShaderPerSubset(5);
		spShader->AddShaderPerSubset((_int)Engine::EShaderID::MeshShader, 0);
		spShader->AddShaderPerSubset((_int)Engine::EShaderID::MeshShader, 1);
		spShader->AddShaderPerSubset((_int)EShaderID::KianaBodyShader, 2);
		spShader->AddShaderPerSubset((_int)EShaderID::FaceShader, 3);
		spShader->AddShaderPerSubset((_int)EShaderID::KianaBodyShader, 4);
	}
	else if (name == L"�׷��硤����Į����")
	{
		// �׷��� ������Ʈ ���� -> IDLE�� ����
		m_vPlayer = m_scene->GetObjectFactory()->AddClone(L"KianaUIAnim", true, (_int)ELayerID::Player, L"");
		static_cast<CKianaUIAnim*>(m_vPlayer.get())->SetTextureName(L"Theresa_NoWp");
		m_vPlayer->GetComponent<Engine::CTransformC>()->SetPosition(_float3(-0.535000920f, -0.799999893f, -3.64999032f));
		m_vPlayer->GetComponent<Engine::CTransformC>()->SetRotation(_float3(0, D3DXToRadian(180.0f), 0));
		m_vPlayer->GetComponent<Engine::CTransformC>()->SetSize(_float3(1.f, 1.f, 1.f));

		SP(Engine::CShaderC) spShader = m_vPlayer->GetComponent<Engine::CShaderC>();
		spShader->AddShader((_int)EShaderID::OutlineShader);
		spShader->AddShader((_int)EShaderID::CharacterShader);
	}
	else if (name == L"�߿� �����")
	{
		// ����� ������Ʈ ���� -> IDLE�� ����
		m_vPlayer = m_scene->GetObjectFactory()->AddClone(L"KianaUIAnim", true, (_int)ELayerID::Player, L"");
		static_cast<CKianaUIAnim*>(m_vPlayer.get())->SetTextureName(L"Sakura_Wp");
		m_vPlayer->GetComponent<Engine::CTransformC>()->SetPosition(_float3(-0.305001855f, -0.534999609f, -4.28503370f));
		m_vPlayer->GetComponent<Engine::CTransformC>()->SetRotation(_float3(0, D3DXToRadian(180.0f), 0));
		m_vPlayer->GetComponent<Engine::CTransformC>()->SetSize(_float3(1.f, 1.f, 1.f));

		SP(Engine::CShaderC) spShader = m_vPlayer->GetComponent<Engine::CShaderC>();
		spShader->AddShader((_int)EShaderID::OutlineShader);
		spShader->AddShader((_int)EShaderID::CharacterShader);
	}
}

void CValkyrieWeapon::End()
{
	std::cout << "���ⳡ" << std::endl;
	if (m_vPlayer != nullptr)
		m_vPlayer->SetDeleteThis(true);
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