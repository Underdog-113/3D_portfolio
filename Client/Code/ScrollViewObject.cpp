#include "Stdafx.h"
#include "ScrollViewObject.h"
#include "Scene.h"
#include "Object.h"
#include "ButtonFunction.h"

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
}

void CScrollViewObject::Render(void)
{
}

void CScrollViewObject::PostRender(void)
{
}

void CScrollViewObject::OnDestroy(void)
{
	__super::OnDestroy();
}

void CScrollViewObject::OnEnable(void)
{
	__super::OnEnable();

	_int count = 0;
	for (auto& buttonObject : m_vButtonObject)
	{
		count++;

		buttonObject->SetIsEnabled(true);

		for (auto& imageObject : m_vImageObject[count - 1])
		{
			imageObject.m_image->SetIsEnabled(true);
		}
	}
}

void CScrollViewObject::OnDisable(void)
{
	__super::OnDisable();

	_int count = 0;
	for (auto& buttonObject : m_vButtonObject)
	{
		count++;

		buttonObject->SetIsEnabled(false);

		for (auto& imageObject : m_vImageObject[count - 1])
		{
			imageObject.m_image->SetIsEnabled(false);
		}
	}
}

void CScrollViewObject::AddScrollViewData(_int column, _float2 distanceXY, _float2 offSet)
{
	m_column = column;
	m_distanceXY = distanceXY;
	m_offSet = offSet;
}

CScrollViewObject * CScrollViewObject::AddImageObjectData(_int number, std::wstring texture, _float3 size, _float2 offset)
{
	SP(Engine::CImageObject) image =
		std::dynamic_pointer_cast<Engine::CImageObject>(GetScene()->GetObjectFactory()->AddClone(L"ImageObject", true, (_int)ELayerID::UI, L"ScrollViewImageObject"));
	image->GetTransform()->SetSize(size);
	image->GetTexture()->AddTexture(texture, 0);

	ImageInfo info;
	info.m_image = image;
	info.m_offset = offset;

	m_vImageObject[number].emplace_back(info);

	return this;
}

void CScrollViewObject::SetBasicName(void)
{
	m_name = m_objectKey + std::to_wstring(m_s_uniqueID++);
}

void CScrollViewObject::ImageObjectSort()
{
	_int count = 0;
	_float3 pos = GetTransform()->GetPosition() + _float3(m_offSet.x, m_offSet.y, 0);
	pos.z += 0.01f;
	for (auto& buttonObject : m_vButtonObject)
	{
		count++;

		buttonObject->GetTransform()->SetPosition(pos);
		pos.x += m_distanceXY.x;

		for (auto& imageObject : m_vImageObject[count-1])
		{
			_float3 T = _float3(imageObject.m_offset.x, imageObject.m_offset.y, 0);
			imageObject.m_image->GetTransform()->SetPosition(pos + T);
		}

		if (count % m_column == 0)
		{
			pos.x = GetTransform()->GetPosition().x + m_offSet.x;
			pos.y -= m_distanceXY.y;
		}
	}
}

// 처음 지정위치에서 시작해서 간격만큼 이미지추가
