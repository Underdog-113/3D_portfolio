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
	spClone->m_spGraphics = spClone->GetComponent<Engine::CGraphicsC>();
	spClone->m_spTexture = spClone->GetComponent<Engine::CTextureC>();
	spClone->m_spRectTex = spClone->GetComponent<Engine::CRectTexC>();

	return spClone;
}

void CScrollViewObject::Awake(void)
{
	__super::Awake();
	m_layerID = (_int)Engine::ELayerID::UI;
	m_addExtra = true;
	
	(m_spRectTex = AddComponent<Engine::CRectTexC>())->SetIsOrtho(true);
	(m_spGraphics = AddComponent<Engine::CGraphicsC>())->SetRenderID((_int)Engine::ERenderID::UI);
	(m_spTexture = AddComponent<Engine::CTextureC>())->AddTexture(L"Defalut",0);
	m_spShader = AddComponent<Engine::CShaderC>();
	m_spShader->AddShader((_int)Engine::EShaderID::RectTexShader);
}

void CScrollViewObject::Start(void)
{
	__super::Start();
	offset = 0;

	dir = _float3(0, 1, 0);
}

void CScrollViewObject::FixedUpdate(void)
{
	__super::FixedUpdate();
}

void CScrollViewObject::Update(void)
{
	__super::Update();
	ImageObjectSort();
	Scroll();
}

void CScrollViewObject::LateUpdate(void)
{
	__super::LateUpdate();
}

void CScrollViewObject::PreRender(LPD3DXEFFECT pEffect)
{
	if(m_spTexture != nullptr)
		m_spRectTex->PreRender(m_spGraphics, pEffect);
}

void CScrollViewObject::Render(LPD3DXEFFECT pEffect)
{
	if (m_spTexture != nullptr)
		m_spRectTex->Render(m_spGraphics, pEffect);

	for (auto& obj : m_vButtonObject)
	{
		obj->Render(pEffect);
	}
}

void CScrollViewObject::PostRender(LPD3DXEFFECT pEffect)
{
	m_spRectTex->PostRender(m_spGraphics, pEffect);
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

		for (auto& textObject : m_vTextObject)
		{
			textObject.m_text->SetIsEnabled(true);
		}

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

		for (auto& textObject : m_vTextObject)
		{
			textObject.m_text->SetIsEnabled(false);
		}

		for (auto& imageObject : m_vImageObject[count - 1])
		{
			imageObject.m_image->SetIsEnabled(false);
		}
	}
}

void CScrollViewObject::AllDelete()
{
	_int count = 0;

	for (auto& buttonObject : m_vButtonObject)
	{
		count++;

		buttonObject->SetDeleteThis(true);

		for (auto& textObject : m_vTextObject)
		{
			textObject.m_text->SetDeleteThis(true);
		}

		for (auto& imageObject : m_vImageObject[count - 1])
		{
			imageObject.m_image->SetDeleteThis(true);
		}
	}

	m_vButtonObject.clear();
	m_vTextObject.clear();
	m_vImageObject.clear();
}

void CScrollViewObject::AddScrollViewData(_int column, _float2 distanceXY, _float2 offSet)
{
	m_column = column;
	m_distanceXY = distanceXY;
	m_offSet = offSet;
}

CScrollViewObject * CScrollViewObject::AddImageObjectData(_int number, std::wstring texture, _float3 size, _float2 offset, _float sort)
{
	SP(Engine::CImageObject) image =
		std::static_pointer_cast<Engine::CImageObject>(GetScene()->GetObjectFactory()->AddClone(L"ImageObject", true, (_int)Engine::ELayerID::UI, L"ScrollViewImageObject"));
	image->GetTransform()->SetSize(size);
	image->GetTexture()->AddTexture(texture, 0);
	image->GetShader()->AddShader((_int)Engine::EShaderID::RectTexShader);

	ImageInfo info;
	info.m_image = image;
	info.m_offset = _float3(offset.x, offset.y, sort);

	m_vImageObject[number].emplace_back(info);

	return this;
}

CScrollViewObject * CScrollViewObject::AddTextObjectData(_int number, _float2 offset, _int fontSize, D3DXCOLOR color, std::wstring message)
{
	SP(Engine::CTextObject) textObject =
		std::static_pointer_cast<Engine::CTextObject>(GetScene()->GetObjectFactory()->AddClone(L"TextObject", true, (_int)Engine::ELayerID::UI, L""));
	_float2 pos = _float2(m_spTransform->GetPosition().x, m_spTransform->GetPosition().y);
	textObject->AddComponent<Engine::CTextC>()->AddFontData(message, _float2(0,0), _float2(0, 0), fontSize, DT_VCENTER + DT_LEFT + DT_NOCLIP, color, true);

	TextInfo info;
	info.m_text = textObject;
	info.m_offset = offset;

	m_vTextObject.emplace_back(info);

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


		buttonObject->GetTransform()->SetPosition(pos);


		/*_float3 T = _float3(m_vTextObject[count].m_offset.x, m_vTextObject[count].m_offset.y, 0.09f);
		m_vTextObject[count].m_text->GetTransform()->SetPosition(pos + T);*/

		for (auto& imageObject : m_vImageObject[count])
		{
			_float3 T = _float3(imageObject.m_offset.x, imageObject.m_offset.y, imageObject.m_offset.z + 0.01f);
			imageObject.m_image->GetTransform()->SetPosition(pos + T);
		}

		pos.x += m_distanceXY.x;

		count++;
		if (count % m_column == 0)
		{
			pos.x = GetTransform()->GetPosition().x + m_offSet.x;
			pos.y -= m_distanceXY.y;
		}
	}
}

void CScrollViewObject::Scroll()
{

	// 마우스가 스크롤뷰 안을 클릭하면 현재 위치를 저장
	// 마우스가 이동하는면 이동 대신 빠르게이동하면 빠르게 이동되고
	// 빠르게 이동하다가 마우스를 놔버리면 해당 속도로 느리게 이동된다

	// 그려야할 모든 오브젝트의 위치값을 알고있다 해당 위치값을 더해주고 빼서 이동시킬수있다.

	if (Engine::CInputManager::GetInstance()->KeyPress(MOUSE_LEFT))
	{
	/*	_int count = 0;
		for (auto& buttonObject : m_vButtonObject)
		{
			count++;

			buttonObject->GetTransform()->SetPosition(dir * offset);

			for (auto& textObject : m_vTextObject)
			{
				textObject.m_text->GetTransform()->SetPosition(dir * offset);
			}

			for (auto& imageObject : m_vImageObject[count - 1])
			{
				imageObject.m_image->GetTransform()->SetPosition(dir * offset);
			}
		}*/
	}
	else
	{
		offset = 0;
		
	}

}

