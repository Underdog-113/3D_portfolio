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
	OnDestroy();
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
	m_layerID = (_int)ELayerID::Decoration;	
	m_addExtra = true;
	m_spHandle = nullptr;
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

	if (m_spHandle)
	{
		/*
		자신의 벨류에 맞는곳의 이미지를띄운다.
		해당 벨류로 인하여 이미지의 위치가변경될수도있고 
		이미지의위치에 의하여 벨류가 변경될수도있다.
		슬라이더 min위치와 max위치 사이에 이미지가 어디에있는가
		1. 이미지 위치를 어떻게 수정할까?
		2. 이미지가 이동하면 bool값을 바꾼다.
		*/
	}
}

void CSlider::LateUpdate(void)
{
	__super::LateUpdate();
}

void CSlider::PreRender(LPD3DXEFFECT pEffect)
{
}

void CSlider::Render(LPD3DXEFFECT pEffect)
{

}

void CSlider::PostRender(LPD3DXEFFECT pEffect)
{
}

void CSlider::OnDestroy(void)
{
	__super::OnDestroy();
}

void CSlider::OnEnable(void)
{
	__super::OnEnable();
	m_spBackGround->SetIsEnabled(true);
	m_spFill->SetIsEnabled(true);
}

void CSlider::OnDisable(void)
{
	__super::OnDisable();
	m_spBackGround->SetIsEnabled(false);
	m_spFill->SetIsEnabled(false);
}

void CSlider::AddSliderData(_float value, _float maxValue, _float minValue, SP(CObject) spBackGround, SP(CObject) spFill)
{
	m_value = value;
	m_MaxValue = maxValue;
	m_MinValue = minValue;
	m_spBackGround = spBackGround;
	m_spFill = spFill;
}

void CSlider::SetBasicName(void)
{
	m_name = m_objectKey + std::to_wstring(m_s_uniqueID++);
}
