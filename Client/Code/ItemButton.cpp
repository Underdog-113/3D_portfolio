#include "stdafx.h"
#include "ItemButton.h"
#include "ValkyrieLevelUp.h"

#include "ClientScene.h"

_uint CItemButton::m_s_uniqueID = 0;
CItemButton::CItemButton()
{
}


CItemButton::~CItemButton()
{
	OnDestroy();
}

SP(CItemButton) CItemButton::Create(_bool isStatic, Engine::CScene * pScene)
{
	SP(CItemButton) spInstance(new CItemButton, Engine::SmartDeleter<CItemButton>);
	spInstance->SetIsStatic(isStatic);
	spInstance->SetScene(pScene);
	spInstance->Awake();

	return spInstance;
}

SP(Engine::CObject) CItemButton::MakeClone(void)
{
	SP(CItemButton) spClone(new CItemButton, Engine::SmartDeleter<CItemButton>);
	__super::InitClone(spClone);

	spClone->m_spTransform = spClone->GetComponent<Engine::CTransformC>();

	return spClone;
}

void CItemButton::Awake(void)
{
	__super::Awake();

	m_layerID = (_int)Engine::ELayerID::UI;
	m_dataID = UNDEFINED;
}

void CItemButton::Start(void)
{
	__super::Start();
}

void CItemButton::FixedUpdate(void)
{
	__super::FixedUpdate();

}

void CItemButton::Update(void)
{
	__super::Update();

}

void CItemButton::LateUpdate(void)
{
	__super::LateUpdate();

}

void CItemButton::PreRender(LPD3DXEFFECT pEffect)
{
}

void CItemButton::Render(LPD3DXEFFECT pEffect)
{
}

void CItemButton::PostRender(LPD3DXEFFECT pEffect)
{
}

void CItemButton::OnDestroy(void)
{
	__super::OnDestroy();

	if(m_button != nullptr)
		m_button->SetDeleteThis(true);

	if(m_image != nullptr)
		m_image->SetDeleteThis(true);

	if(m_textObj != nullptr)
		m_textObj->SetDeleteThis(true);
}

void CItemButton::OnEnable(void)
{
	__super::OnEnable();

}

void CItemButton::OnDisable(void)
{
	__super::OnDisable();
}

void CItemButton::ButtonCreate(std::wstring name, _float3 pos, _float3 size, std::wstring textureKey, CButton::EButton_Type buttonType)
{
	m_button = std::dynamic_pointer_cast<CButton>(m_pScene->GetObjectFactory()->AddClone(L"Button", true, (_int)Engine::ELayerID::UI, name));
	m_button->GetTransform()->SetPosition(m_spTransform->GetPosition() + pos);
	m_button->GetTransform()->SetSize(size);
	m_button->GetTexture()->AddTexture(textureKey, 0);
	m_button->GetTexture()->AddTexture(textureKey, 0);
	m_button->SetButtonType(buttonType);
	m_button->GetShader()->AddShader((_int)Engine::EShaderID::RectTexShader);
}

void CItemButton::ImageCreate(std::wstring name, _float3 pos, _float3 size, std::wstring textureKey)
{
	m_image = std::dynamic_pointer_cast<Engine::CImageObject>(m_pScene->GetObjectFactory()->AddClone(L"ImageObject", true, (_int)Engine::ELayerID::UI, name));
	m_image->GetTransform()->SetPosition(m_spTransform->GetPosition() + pos);
	m_image->GetTransform()->SetPositionZ(pos.z + 0.01f);

	m_image->GetTransform()->SetSize(size);
	m_image->GetTexture()->AddTexture(textureKey, 0);
	m_image->GetShader()->AddShader((_int)Engine::EShaderID::RectTexShader);
}

void CItemButton::textCreate(std::wstring name, _float2 pos, _float sort, _int fontSize, D3DXCOLOR color, std::wstring alignment, std::wstring message)
{
	m_textObj = std::dynamic_pointer_cast<Engine::CTextObject>(m_pScene->GetObjectFactory()->AddClone(L"TextObject", true, (_int)Engine::ELayerID::UI, name));
	m_textObj->GetTransform()->SetPositionZ(sort + 0.02f);
	m_textObj->AddComponent<Engine::CTextC>()->AddFontData(message, pos, _float2(0, 0), fontSize, DT_VCENTER + DT_CENTER + DT_NOCLIP, color, true);
}

void CItemButton::ItemSelect()
{
	CValkyrieLevelUp::g_selectItemName = m_itemName;
	CValkyrieLevelUp::g_itemCount = 0;
	static_cast<CValkyrieLevelUp*>(CValkyriegManager::GetInstance()->GetValkyrieFSM())->ItemCountUp();
	std::static_pointer_cast<Engine::CSlider>(GET_CUR_CLIENT_SCENE->FindObjectByName(L"LevelUpCanvas_Slider_0"))->SetMaxValue((_float)CDataManager::GetInstance()->FindItemData(m_itemName)->GetCount());
}

void CItemButton::SetBasicName(void)
{
	m_name = m_objectKey + std::to_wstring(m_s_uniqueID++);
}
