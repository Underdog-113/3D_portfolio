#include "stdafx.h"
#include "ImageFontObject.h"

CImageFontObject::CImageFontObject()
{
}


CImageFontObject::~CImageFontObject()
{
}

SP(CImageFontObject) CImageFontObject::Create(_bool isStatic, Engine::CScene * pScene)
{
	SP(CImageFontObject) spInstance(new CImageFontObject, Engine::SmartDeleter<CImageFontObject>);
	spInstance->SetIsStatic(isStatic);
	spInstance->SetScene(pScene);
	spInstance->Awake();

	return spInstance;
}

SP(Engine::CObject) CImageFontObject::MakeClone(void)
{
	SP(CImageFontObject) spClone(new CImageFontObject);
	__super::InitClone(spClone);

	spClone->m_spTransform = spClone->GetComponent<Engine::CTransformC>();

	return spClone;
	return SP(CObject)();
}

void CImageFontObject::Awake(void)
{
	__super::Awake();
	m_layerID = (_int)ELayerID::UI;	
	m_addExtra = true;
	
	AddComponent<Engine::CBitmapC>();
	AddComponent<Engine::CGraphicsC>()->SetRenderID((_int)Engine::ERenderID::UI);
	AddComponent<Engine::CTextureC>();
}

void CImageFontObject::Start(void)
{
	__super::Start();

	_float2 pos = _float2(GetTransform()->GetPosition().x, GetTransform()->GetPosition().y);
	m_textData = Engine::CTextManager::GetInstance()->AddText(GetName(), m_text, pos, m_boxSize, m_fontSize, m_alignment, m_color);
}

void CImageFontObject::FixedUpdate(void)
{
	__super::FixedUpdate();
}

void CImageFontObject::Update(void)
{
	__super::Update();
}

void CImageFontObject::LateUpdate(void)
{
	__super::LateUpdate();
}

void CImageFontObject::OnDestroy(void)
{
	__super::OnDestroy();
}

void CImageFontObject::OnEnable(void)
{
	__super::OnEnable();
}

void CImageFontObject::OnDisable(void)
{
	__super::OnDisable();
}

void CImageFontObject::SetBasicName(void)
{
}

void CImageFontObject::AddFontData(std::wstring text, _float2 boxSize, _int fontSize, DWORD alignment, D3DXCOLOR color)
{
	m_text = text;
	m_boxSize = boxSize;
	m_fontSize = fontSize;
	m_alignment = alignment;
	m_color = color;
}
