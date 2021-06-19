#include "EngineStdafx.h"
#include "ImageObject.h"

USING(Engine)
_uint CImageObject::m_s_uniqueID = 0;
CImageObject::CImageObject()
{
}

CImageObject::~CImageObject()
{
	OnDestroy();
}

SP(CImageObject) CImageObject::Create(_bool isStatic, CScene * pScene)
{
	SP(CImageObject) spInstance(new CImageObject, SmartDeleter<CImageObject>);
	spInstance->SetIsStatic(isStatic);
	spInstance->SetScene(pScene);
	spInstance->Awake();

	return spInstance;
}

SP(Engine::CObject) CImageObject::MakeClone(void)
{
	SP(CImageObject) spClone(new CImageObject, SmartDeleter<CImageObject>);
	__super::InitClone(spClone);

	spClone->m_spTransform = spClone->GetComponent<CTransformC>();
	spClone->m_spGraphics = spClone->GetComponent<CGraphicsC>();
	spClone->m_spTexture = spClone->GetComponent<CTextureC>();
	spClone->m_spRectTex = spClone->GetComponent<CRectTexC>();
	spClone->m_spShader = spClone->GetComponent<CShaderC>();

	return spClone;
}

void CImageObject::Awake(void)
{
	__super::Awake();
	m_layerID = (_int)ELayerID::Decoration;	
	m_dataID = UNDEFINED;
	m_addExtra = true;
	
	(m_spRectTex = AddComponent<CRectTexC>())->SetIsOrtho(true);
	(m_spGraphics = AddComponent<CGraphicsC>())->SetRenderID((_int)ERenderID::UI);
	m_spTexture = AddComponent<CTextureC>();
	m_spShader = AddComponent<CShaderC>();
}	

void CImageObject::Start(void)
{
	__super::Start();
}

void CImageObject::FixedUpdate(void)
{
	__super::FixedUpdate();
}

void CImageObject::Update(void)
{
	__super::Update();
}

void CImageObject::LateUpdate(void)
{
	__super::LateUpdate();
}

void CImageObject::PreRender(LPD3DXEFFECT pEffect)
{
	m_spRectTex->PreRender(GetComponent<CGraphicsC>(), pEffect);
}


void CImageObject::Render(LPD3DXEFFECT pEffect)
{
	m_spRectTex->Render(GetComponent<CGraphicsC>(), pEffect);

	SP(CTextC) textC = GetComponent<CTextC>();

	if (textC)
	{
		textC->Render(m_spGraphics);
	}
}

void CImageObject::PostRender(LPD3DXEFFECT pEffect)
{
	m_spRectTex->PostRender(GetComponent<CGraphicsC>(), pEffect);
}

void CImageObject::OnDestroy(void)
{
	__super::OnDestroy();
}

void CImageObject::OnEnable(void)
{
	__super::OnEnable();
}

void CImageObject::OnDisable(void)
{
	__super::OnDisable();
}

void CImageObject::SetBasicName(void)
{
	m_name = m_objectKey + std::to_wstring(m_s_uniqueID++);
}
