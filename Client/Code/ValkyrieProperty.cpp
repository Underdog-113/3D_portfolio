#include "stdafx.h"
#include "ValkyrieProperty.h"

#include "ClientScene.h"
#include "KianaUIAnim.h"

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

	std::static_pointer_cast<CButton>(CValkyriegManager::GetInstance()->GetScene()->FindObjectByName(L"MainCanvas_Button_1"))->AddFuncData(delegate);
	// 데이터 셋팅

	PropertyCanvas();

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

		SP(Engine::CShaderC) spShader = m_vPlayer->GetComponent<Engine::CShaderC>();
		spShader->AddShader((_int)EShaderID::OutlineShader);

		spShader->ResizeShaderPerSubset(5);
		spShader->AddShaderPerSubset((_int)Engine::EShaderID::MeshShader, 0);
		spShader->AddShaderPerSubset((_int)Engine::EShaderID::MeshShader, 1);
		spShader->AddShaderPerSubset((_int)EShaderID::KianaBodyShader, 2);
		spShader->AddShaderPerSubset((_int)EShaderID::FaceShader, 3);
		spShader->AddShaderPerSubset((_int)EShaderID::KianaBodyShader, 4);
	}
	else if (name == L"테레사·아포칼립스")
	{
		// 테레사 오브젝트 생성 -> IDLE로 변경
		m_vPlayer = m_scene->GetObjectFactory()->AddClone(L"KianaUIAnim", true, (_int)ELayerID::Player, L"");
		static_cast<CKianaUIAnim*>(m_vPlayer.get())->SetTextureName(L"Theresa_Wp");
		m_vPlayer->GetComponent<Engine::CTransformC>()->SetPosition(_float3(-0.535000920f, -0.799999893f, -3.64999032f));
		m_vPlayer->GetComponent<Engine::CTransformC>()->SetRotation(_float3(0, D3DXToRadian(180.0f), 0));
		m_vPlayer->GetComponent<Engine::CTransformC>()->SetSize(_float3(1.f, 1.f, 1.f));

		SP(Engine::CShaderC) spShader = m_vPlayer->GetComponent<Engine::CShaderC>();
		spShader->AddShader((_int)EShaderID::OutlineShader);
		spShader->AddShader((_int)EShaderID::CharacterShader);
	}
	else if (name == L"야에 사쿠라")
	{
		// 사쿠라 오브젝트 생성 -> IDLE로 변경
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

void CValkyrieProperty::End()
{
	if (m_vPlayer != nullptr)
		m_vPlayer->SetDeleteThis(true);
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

