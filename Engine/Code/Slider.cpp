#include "EngineStdafx.h"
#include "Slider.h"
#include "ImageObject.h"
#include "Scene.h"

USING(Engine)
_uint CSlider::m_s_uniqueID = 0;
CSlider::CSlider()
{
}

CSlider::~CSlider()
{
}

SP(CSlider) CSlider::Create(_bool isStatic, CScene * pScene)
{
	SP(CSlider) spInstance(new CSlider, SmartDeleter<CSlider>);
	spInstance->SetIsStatic(isStatic);
	spInstance->SetScene(pScene);
	spInstance->Awake();

	return spInstance;
}

SP(Engine::CObject) CSlider::MakeClone(void)
{
	SP(CSlider) spClone(new CSlider, SmartDeleter<CSlider>);
	__super::InitClone(spClone);

	spClone->m_spTransform = spClone->GetComponent<CTransformC>();

	return spClone;
}

void CSlider::Awake(void)
{
	__super::Awake();
	m_layerID = (_int)ELayerID::UI;	
	m_addExtra = true;

}	

void CSlider::Start(void)
{
	__super::Start();
}

void CSlider::FixedUpdate(void)
{
	__super::FixedUpdate();
}

void CSlider::Update(void)
{
	__super::Update();
}

void CSlider::LateUpdate(void)
{
	__super::LateUpdate();
}

void CSlider::PreRender(void)
{
}

void CSlider::Render(void)
{

}

void CSlider::PostRender(void)
{
}

void CSlider::OnDestroy(void)
{
	__super::OnDestroy();
}

void CSlider::OnEnable(void)
{
	__super::OnEnable();
}

void CSlider::OnDisable(void)
{
	__super::OnDisable();
}

void CSlider::AddSliderData(_float value, _float maxValue, SP(CObject) spBackGround, SP(CObject) spFill)
{
	m_value = value;
	m_MaxValue = maxValue;
	m_spBackGround = spBackGround;
	m_spFill = spFill;
}

void CSlider::SetBasicName(void)
{
	m_name = m_objectKey + std::to_wstring(m_s_uniqueID++);
}
