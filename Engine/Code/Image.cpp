#include "EngineStdafx.h"
#include "Image.h"
#include "TextC.h"
USING(Engine)
_uint CImage::m_s_uniqueID = 0;
CImage::CImage()
{
}

CImage::~CImage()
{
}

SP(CImage) CImage::Create(_bool isStatic, Engine::CScene * pScene)
{
	SP(CImage) spInstance(new CImage, Engine::SmartDeleter<CImage>);
	spInstance->SetIsStatic(isStatic);
	spInstance->SetScene(pScene);
	spInstance->Awake();

	return spInstance;
}

SP(Engine::CObject) CImage::MakeClone(void)
{
	SP(CImage) spClone(new CImage);
	__super::InitClone(spClone);

	spClone->m_spTransform = spClone->GetComponent<Engine::CTransformC>();
	spClone->m_spGraphics = spClone->GetComponent<Engine::CGraphicsC>();
	spClone->m_spTexture = spClone->GetComponent<Engine::CTextureC>();
	spClone->m_spRectTex = spClone->GetComponent<Engine::CRectTexC>();

	return spClone;
	return SP(CObject)();
}

void CImage::Awake(void)
{
	__super::Awake();
	m_layerID = (_int)ELayerID::UI;	
	m_addExtra = true;
	
	AddComponent<Engine::CRectTexC>()->SetIsOrtho(true);
	AddComponent<Engine::CGraphicsC>()->SetRenderID((_int)Engine::ERenderID::UI);
	AddComponent<Engine::CTextureC>();
}

void CImage::Start(void)
{
	__super::Start();
}

void CImage::FixedUpdate(void)
{
	__super::FixedUpdate();
}

void CImage::Update(void)
{
	__super::Update();
}

void CImage::LateUpdate(void)
{
	__super::LateUpdate();
}

void CImage::PreRender(void)
{
	m_spRectTex->PreRender(m_spGraphics);
}

void CImage::Render(void)
{
	m_spRectTex->Render(m_spGraphics);

	SP(CTextC) text = GetComponent<CTextC>();
	if (text)
	{
		text->RenderText();
	}

}

void CImage::PostRender(void)
{
	m_spRectTex->PostRender(m_spGraphics);
}

void CImage::OnDestroy(void)
{
	__super::OnDestroy();
}

void CImage::OnEnable(void)
{
	__super::OnEnable();
}

void CImage::OnDisable(void)
{
	__super::OnDisable();
}

void CImage::SetBasicName(void)
{
}
