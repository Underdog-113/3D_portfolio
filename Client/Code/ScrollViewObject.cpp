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
	spClone->m_spShader = spClone->GetComponent<Engine::CShaderC>();

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
	m_oldMousePos = _float3(0, 0, 0);
	m_dir = _float3(0, 1.0f, 0);
	m_chack = false;
	m_speed = 0;
	m_init = false;
}

void CScrollViewObject::FixedUpdate(void)
{
	__super::FixedUpdate();
}

void CScrollViewObject::Update(void)
{
	__super::Update();
	
	Scroll();

	if (m_chack)
	{
		if (ScrollChack(m_speed))
		{
			m_speed = 0;
			return;
		}

		_int count = 0;
		for (auto& buttonObject : m_vButtonObject)
		{
			count++;

			buttonObject->GetTransform()->AddPosition(m_dir * m_speed);

			for (auto& imageObject : m_vImageObject[count - 1])
			{
				imageObject.m_image->GetTransform()->AddPosition(m_dir * m_speed);
			}
		}

		for (auto& textObject : m_vTextObject)
		{
			textObject.m_text->GetTransform()->AddPosition(m_dir * m_speed);
		}

		if (m_speed > 0)
		{
			m_speed = max(m_speed - GET_DT * 10, 0);
		}
		else if (m_speed < 0)
		{
			m_speed = min(m_speed + GET_DT * 10, 0);
		}

		std::cout << "m_speed : " << m_speed << std::endl; 
	}
}

void CScrollViewObject::LateUpdate(void)
{
	__super::LateUpdate();

	if (!m_init)
	{
		ImageObjectSort();
		m_init = true;
	}
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
	m_init = false;

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
	m_init = false;
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

		_float3 T = _float3(m_vTextObject[count].m_offset.x, m_vTextObject[count].m_offset.y, 0.09f);
		m_vTextObject[count].m_text->GetTransform()->SetPosition(pos + T);

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
	if (Engine::CInputManager::GetInstance()->KeyDown(MOUSE_LEFT))
	{	
		m_oldMousePos = Engine::CInputManager::GetInstance()->GetMousePos();
	}

	if (Engine::CInputManager::GetInstance()->KeyUp(MOUSE_LEFT))
	{
		if (m_speed != 0)
		{
			m_chack = true;
			m_speed *= 0.5f;
		}

		m_oldMousePos = _float3(0,0,0);
	}

	if (Engine::CInputManager::GetInstance()->KeyPress(MOUSE_LEFT))
	{
		m_speed = 0;
		m_chack = false;
		_float3 mousePos = Engine::CInputManager::GetInstance()->GetMousePos();
		_int count = 0;

		Directionadjustment(m_oldMousePos, mousePos, m_speed);

		/*system("cls");
		std::cout << "m_oldMousePos : " << m_oldMousePos.y <<std::endl;
		std::cout << "mousePos : " << mousePos.y <<  std::endl;
		std::cout << "m_speed : " << m_speed << std::endl;*/

		if (ScrollChack(m_speed))
		{
			m_oldMousePos = Engine::CInputManager::GetInstance()->GetMousePos();
			return;
		}

		for (auto& buttonObject : m_vButtonObject)
		{
			count++;

			buttonObject->GetTransform()->AddPosition(m_dir * m_speed);

			for (auto& imageObject : m_vImageObject[count - 1])
			{
				imageObject.m_image->GetTransform()->AddPosition(m_dir * m_speed);
			}
		}

		for (auto& textObject : m_vTextObject)
		{
			textObject.m_text->GetTransform()->AddPosition(m_dir * m_speed);
		}

		m_oldMousePos = Engine::CInputManager::GetInstance()->GetMousePos();
	}
}

bool CScrollViewObject::ScrollChack(_float dir)
{
	switch (m_dirType)
	{
	case EDir_Type::UpandDown:
	{
		_float s = m_vButtonObject[m_vButtonObject.size() - 1]->GetTransform()->GetPosition().y + (m_dir.y * dir);

		if (m_vButtonObject[0]->GetTransform()->GetPosition().y + (m_dir.y * dir) + (m_offSet.y * 0.5) < GetTransform()->GetPosition().y + (GetTransform()->GetSize().y * 0.5f))
		{
			return true;
		}

		if (m_vButtonObject[m_vButtonObject.size() - 1]->GetTransform()->GetPosition().y + (m_dir.y * dir) - (m_offSet.y * 0.5)> GetTransform()->GetPosition().y - (GetTransform()->GetSize().y * 0.5f))
		{
			return true;
		}
		break;
	}
	case EDir_Type::RightandLeft:
		if (m_vButtonObject[m_vButtonObject.size() - 1]->GetTransform()->GetPosition().x + (m_dir.x * dir) > m_offSet.x)
		{
			return true;
		}
		break;
	}

	return false;
}

void CScrollViewObject::Directionadjustment(_float3 pos1, _float3 pos2, _float & dir)
{
	switch (m_dirType)
	{
	case EDir_Type::UpandDown:
		pos1.x = 0; pos1.z = 0;
		pos2.x = 0; pos2.z = 0;
		dir = Engine::Direction(pos1, pos2);
		if (pos1.y > pos2.y) 
		{
			dir *= -1;
		}
		break;
	case EDir_Type::RightandLeft:
		pos1.y = 0; pos1.z = 0;
		pos2.y = 0; pos2.z = 0;
		if (pos1.x > pos2.x)
		{
			dir *= -1;
		}
		break;
	}
}

/*
이동하는 코드를 update문에 박아두고
현재 마우스체크부분에는 속도값을 주는코드로바꾸면 이동하는 값만큼의 이속을줄수있지않을까

문제는 이속을주고 손가락을때야 스피드가 적용되고 그외에는 그냥 손가락움직이는거에 맞춰서 지금 방식으로 이동한다.
빠르게 손가락두는것과 그냥 손가락두는것의 차이를 알아야한다.
*/