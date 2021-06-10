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
	spClone->m_spMesh		= spClone->GetComponent<CMeshC>();
	spClone->m_spGraphics	= spClone->GetComponent<CGraphicsC>();

	return spClone;
}

void CSkyBox::Awake(void)
{
	__super::Awake();
}

void CSkyBox::Start(void)
{
	__super::Start();
	
	m_spGraphics->SetRenderID((_int)ERenderID::Base);
}

void CSkyBox::FixedUpdate(void)
{
	__super::FixedUpdate();
	
}

void CSkyBox::Update(void)
{
	__super::Update();
	
}

void CSkyBox::LateUpdate(void)
{
	__super::LateUpdate();
	
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
