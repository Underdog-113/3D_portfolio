#include "EngineStdafx.h"
#include "SkyBox.h"


USING(Engine)
_uint CSkyBox::m_s_uniqueID = 0;
CSkyBox::CSkyBox()
{
}


CSkyBox::~CSkyBox()
{
	OnDestroy();
}

SP(CSkyBox) CSkyBox::Create(_bool isStatic, CScene * pScene)
{
	SP(CSkyBox) spInstance(new CSkyBox, SmartDeleter<CSkyBox>);
	spInstance->SetIsStatic(isStatic);
	spInstance->SetScene(pScene);
	spInstance->Awake();

	return spInstance;
}

SP(CObject) CSkyBox::MakeClone(void)
{
	SP(CSkyBox) spClone(new CSkyBox, SmartDeleter<CSkyBox>);
	__super::InitClone(spClone);

	spClone->m_spTransform	= spClone->GetComponent<CTransformC>();
	spClone->m_spCubeTex	= spClone->GetComponent<CCubeTexC>();
	spClone->m_spGraphics	= spClone->GetComponent<CGraphicsC>();
	spClone->m_spShader		= spClone->GetComponent<CShaderC>();

	return spClone;
}

void CSkyBox::Awake(void)
{
	__super::Awake();

	m_layerID	= (_int)ELayerID::Decoration;
	m_dataID	= (_int)EDataID::Object;

	m_spCubeTex		= AddComponent<CCubeTexC>();
	m_spTexture		= AddComponent<CTextureC>();
	m_spGraphics	= AddComponent<CGraphicsC>();
	m_spShader		= AddComponent<CShaderC>();
}

void CSkyBox::Start(void)
{
	__super::Start();
	
	m_spTransform->SetSize(40, 40, 40);
}

void CSkyBox::FixedUpdate(void)
{
	__super::FixedUpdate();
	
}

void CSkyBox::Update(void)
{
	__super::Update();

	m_spTransform->SetPosition(GET_MAIN_CAM->GetTransform()->GetPosition());
}

void CSkyBox::LateUpdate(void)
{
	__super::LateUpdate();
	
}

void CSkyBox::PreRender(LPD3DXEFFECT pEffect)
{
	pEffect->BeginPass(0);
	m_spCubeTex->PreRender(m_spGraphics, pEffect);
}

void CSkyBox::Render(LPD3DXEFFECT pEffect)
{
	m_spCubeTex->Render(m_spGraphics, pEffect);
}

void CSkyBox::PostRender(LPD3DXEFFECT pEffect)
{
	pEffect->EndPass();
	m_spCubeTex->PostRender(m_spGraphics, pEffect);
}

void CSkyBox::OnDestroy(void)
{
	__super::OnDestroy();
	
}

void CSkyBox::OnEnable(void)
{
	__super::OnEnable();
	
}

void CSkyBox::OnDisable(void)
{
	__super::OnDisable();
	
}

void CSkyBox::SetBasicName(void)
{
	m_name = m_objectKey + std::to_wstring(m_s_uniqueID++);
}
