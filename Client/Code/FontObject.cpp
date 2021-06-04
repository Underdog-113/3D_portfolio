#include "stdafx.h"
#include "FontObject.h"

CFontObject::CFontObject()
{
}


CFontObject::~CFontObject()
{
}

SP(CFontObject) CFontObject::Create(_bool isStatic, Engine::CScene * pScene)
{
	SP(CFontObject) spInstance(new CFontObject, Engine::SmartDeleter<CFontObject>);
	spInstance->SetIsStatic(isStatic);
	spInstance->SetScene(pScene);
	spInstance->Awake();

	return spInstance;
}

SP(Engine::CObject) CFontObject::MakeClone(void)
{
	SP(CFontObject) spClone(new CFontObject);
	__super::InitClone(spClone);

	spClone->m_spTransform = spClone->GetComponent<Engine::CTransformC>();

	return spClone;
	return SP(CObject)();
}

void CFontObject::Awake(void)
{
	__super::Awake();
	m_layerID = (_int)ELayerID::UI;	
	m_addExtra = true;
	
	AddComponent<Engine::CBitmapC>();
	AddComponent<Engine::CGraphicsC>()->SetRenderID((_int)Engine::ERenderID::UI);
	AddComponent<Engine::CTextureC>();
}

void CFontObject::Start(void)
{
	__super::Start();

	_float2 pos = _float2(GetTransform()->GetPosition().x, GetTransform()->GetPosition().y);
	m_textData = Engine::CTextManager::GetInstance()->AddText(GetName(), m_text, pos, m_boxSize, m_fontSize, m_alignment, m_color);
}

void CFontObject::FixedUpdate(void)
{
	__super::FixedUpdate();
}

void CFontObject::Update(void)
{
	__super::Update();
}

void CFontObject::LateUpdate(void)
{
	__super::LateUpdate();
}

void CFontObject::OnDestroy(void)
{
	__super::OnDestroy();
}

void CFontObject::OnEnable(void)
{
	__super::OnEnable();
}

void CFontObject::OnDisable(void)
{
	__super::OnDisable();
}

void CFontObject::SetBasicName(void)
{
}

void CFontObject::AddFontData(std::wstring text, _float2 boxSize, _int fontSize, DWORD alignment, D3DXCOLOR color)
{
	m_text = text;
	m_boxSize = boxSize;
	m_fontSize = fontSize;
	m_alignment = alignment;
	m_color = color;
}
