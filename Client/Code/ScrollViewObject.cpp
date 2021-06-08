#include "Stdafx.h"
#include "ScrollViewObject.h"
#include "Scene.h"
#include "Object.h"
_uint CScrollViewObject::m_s_uniqueID = 0;
CScrollViewObject::CScrollViewObject()
{
}


CScrollViewObject::~CScrollViewObject()
{
}

SP(CScrollViewObject) CScrollViewObject::Create(_bool isStatic, Engine::CScene * pScene)
{
	SP(CScrollViewObject) spInstance(new CScrollViewObject, Engine::SmartDeleter<CScrollViewObject>);
	spInstance->SetIsStatic(isStatic);
	spInstance->SetScene(pScene);
	spInstance->Awake();

	return spInstance;
}

SP(Engine::CObject) CScrollViewObject::MakeClone(void)
{
	SP(CScrollViewObject) spClone(new CScrollViewObject, Engine::SmartDeleter<CScrollViewObject>);
	__super::InitClone(spClone);

	spClone->m_spTransform = spClone->GetComponent<Engine::CTransformC>();

	return spClone;
}

void CScrollViewObject::Awake(void)
{
	__super::Awake();
	m_layerID = (_int)ELayerID::UI;
	m_addExtra = true;

}

void CScrollViewObject::Start(void)
{
	__super::Start();
}

void CScrollViewObject::FixedUpdate(void)
{
	__super::FixedUpdate();
}

void CScrollViewObject::Update(void)
{
	__super::Update();
	ImageObjectSort();
}

void CScrollViewObject::LateUpdate(void)
{
	__super::LateUpdate();
}

void CScrollViewObject::PreRender(void)
{
	m_spRectTex->PreRender(m_spGraphics);
}

void CScrollViewObject::Render(void)
{
	m_spRectTex->Render(m_spGraphics);
}

void CScrollViewObject::PostRender(void)
{
	m_spRectTex->PostRender(m_spGraphics);
}

void CScrollViewObject::OnDestroy(void)
{
	__super::OnDestroy();
}

void CScrollViewObject::OnEnable(void)
{
	__super::OnEnable();
}

void CScrollViewObject::OnDisable(void)
{
	__super::OnDisable();
}

void CScrollViewObject::AddScrollViewData(_int column, _float2 distanceXY, std::wstring texture)
{
	m_column = column;
	m_distanceXY = distanceXY;
	m_spTexture->AddTexture(texture);
}

CScrollViewObject * CScrollViewObject::AddImageObjectData(std::wstring texture)
{
	/*SP(Engine::CImageObject) image =
		std::dynamic_pointer_cast<Engine::CImageObject>(ADD_CLONE(L"ImageObject", true, (_int)ELayerID::UI, L"ScrollViewImageObject"));
	image->GetTransform()->SetPositionZ(0.0f);
	image->GetTransform()->SetSize(_float3(800, 600, 0));
	image->GetTexture()->AddTexture(texture, 0);*/

	return this;
}

void CScrollViewObject::SetBasicName(void)
{
	m_name = m_objectKey + std::to_wstring(m_s_uniqueID++);
}

void CScrollViewObject::ImageObjectSort()
{
/*	_int count = 0;
	_float3 pos = GetTransform()->GetPosition();
	for (auto& object : m_vImageObject)
	{
		m_vImageObject[count]->GetTransform()->SetPosition(pos);
		pos.x += m_distanceXY.x;
		if (count % m_column == 0)
		{
			pos.x += GetTransform()->GetPosition().x;
			pos.y += m_distanceXY.y;
		}

		count++;
	}*/
}

// 처음 지정위치에서 시작해서 간격만큼 이미지추가
