#include "stdafx.h"
#include "DataLoad.h"

#include "UiAnimCtrC.h"

#include "ImageObject.h"
#include "Button.h"
#include "Slider.h"
#include "ButtonFunction.h"
#include "ScrollViewObject.h"
#include "Canvas.h"

#include "MeshData.h"

#include "MapObject.h"
#include "DecoObject.h"
#include "PhaseChanger.h"
#include "MapObject2D.h"
#include "Monster.h"
#include "Portal.h"

#include "ValkyrieLevelUp.h"
#include "ValkyrieWeaponSwap.h"

CDataLoad::CDataLoad()
{
	
}

CDataLoad::~CDataLoad()
{

}

void CDataLoad::Setting()
{
	m_loadDeleGate += std::bind(&CDataLoad::ButtonLoad, &CDataLoad(), std::placeholders::_1);
	m_loadDeleGate += std::bind(&CDataLoad::ImageLoad, &CDataLoad(), std::placeholders::_1);
	m_loadDeleGate += std::bind(&CDataLoad::SliderLoad, &CDataLoad(), std::placeholders::_1);
	m_loadDeleGate += std::bind(&CDataLoad::ScrollViewLoad, &CDataLoad(), std::placeholders::_1);
	m_loadDeleGate += std::bind(&CDataLoad::CanvasLoad, &CDataLoad(), std::placeholders::_1);
	//m_loadDeleGate += std::bind(&CDataLoad::MapLoad, &CDataLoad(), std::placeholders::_1);
	m_loadDeleGate += std::bind(&CDataLoad::EffectLoad, &CDataLoad(), std::placeholders::_1);
}

void CDataLoad::DelegatePush(void(CDataLoad::* function)(Engine::CScene *), CDataLoad* dataload)
{
	m_loadDeleGate += std::bind(function, dataload, std::placeholders::_1);
}

void CDataLoad::DeleGatePop(void(CDataLoad::* function)(Engine::CScene *), CDataLoad* dataload)
{
	m_loadDeleGate -= std::bind(function, dataload, std::placeholders::_1);
}

void CDataLoad::Load(Engine::CScene * pScene)
{
	m_loadDeleGate(pScene);
}

void CDataLoad::ImageLoad(Engine::CScene* pScene)
{
	Engine::CDataStore* dataStore = pScene->GetDataStore();

	_int numOfImageObject;
	_int dataID = (_int)EDataID::UI;
	std::wstring objectKey = L"ImageDataFile";
	dataStore->GetValue(false, dataID, objectKey, L"numOfImageObject", numOfImageObject);

	for (_int i = 0; i < numOfImageObject; ++i)
	{
		std::wstring key = L"imageObject" + std::to_wstring(i) + L"_";

		std::wstring name;
		dataStore->GetValue(false, dataID, objectKey, key + L"name", name);

		SP(Engine::CImageObject) image =
			std::dynamic_pointer_cast<Engine::CImageObject>(pScene->GetObjectFactory()->AddClone(L"ImageObject", true, (_int)Engine::ELayerID::UI, name));

		_float3 position;
		dataStore->GetValue(false, dataID, objectKey, key + L"position", position);
		image->GetTransform()->SetPosition(position);

		_float3 size;
		dataStore->GetValue(false, dataID, objectKey, key + L"size", size);
		size.z = 0;
		image->GetTransform()->SetSize(size);

		_float sort;
		dataStore->GetValue(false, dataID, objectKey, key + L"sortLayer", sort);
		image->GetTransform()->SetPositionZ(sort);

		std::wstring textureKey;
		dataStore->GetValue(false, dataID, objectKey, key + L"textureKey", textureKey);
		image->GetTexture()->AddTexture(textureKey, 0);


		_float4 textureColor;
		dataStore->GetValue(false, dataID, objectKey, key + L"textureColor", textureColor);
		image->GetTexture()->SetColor(textureColor);

		std::wstring message;
		_float2 fontPosition;
		_int fontSize;
		_float4 color;// = D3DXCOLOR(1, 1, 1, 1);
		std::wstring alignment;

		dataStore->GetValue(false, dataID, objectKey, key + L"fontName", name);

		if (name != L"Not")
		{
			dataStore->GetValue(false, dataID, objectKey, key + L"message", message);
			dataStore->GetValue(false, dataID, objectKey, key + L"fontPosition", fontPosition);
			dataStore->GetValue(false, dataID, objectKey, key + L"fontSize", fontSize);
			dataStore->GetValue(false, dataID, objectKey, key + L"color", color);
			dataStore->GetValue(false, dataID, objectKey, key + L"alignment", alignment);
			fontPosition.y *= -1;

			if (alignment == L"UpperLeft")
			{
				image->AddComponent<Engine::CTextC>()->AddFontData(message, fontPosition, _float2(0, 0), fontSize, DT_VCENTER + DT_LEFT + DT_NOCLIP, (D3DXCOLOR)color, true);

			}
			else if (alignment == L"UpperRight")
			{
				image->AddComponent<Engine::CTextC>()->AddFontData(message, fontPosition, _float2(0, 0), fontSize, DT_VCENTER + DT_RIGHT + DT_NOCLIP, (D3DXCOLOR)color, true);

			}
			else if (alignment == L"UpperCenter")
			{
				image->AddComponent<Engine::CTextC>()->AddFontData(message, fontPosition, _float2(0, 0), fontSize, DT_VCENTER + DT_CENTER + DT_NOCLIP, (D3DXCOLOR)color, true);
			}
		}

		_int animCount;
		dataStore->GetValue(false, dataID, objectKey, key + L"AnimCount", animCount);
		if (animCount > 0)
		{
			image->AddComponent<CUiAnimCtrC>()->SetAnimCount(animCount);

			_float animSpeed;
			dataStore->GetValue(false, dataID, objectKey, key + L"AnimSpeed", animSpeed);
			image->GetComponent<CUiAnimCtrC>()->SetAnimSpeed(animSpeed);

			for (int j = 0; j < animCount; j++)
			{
				dataStore->GetValue(false, dataID, objectKey, key + L"AnimName" + std::to_wstring(j), textureKey);

				image->GetTexture()->AddTexture(textureKey, j);
			}
		}

		image->GetShader()->AddShader((_int)Engine::EShaderID::RectTexShader);

	}
}

void CDataLoad::SliderLoad(Engine::CScene* pScene)
{
	Engine::CDataStore* dataStore = pScene->GetDataStore();

	_int numOfSliderObject;
	_int dataID = (_int)EDataID::UI;
	std::wstring objectKey = L"SliderDataFile";
	dataStore->GetValue(false, dataID, objectKey, L"numOfSliderObject", numOfSliderObject);

	for (_int i = 0; i < numOfSliderObject; ++i)
	{
		std::wstring key = L"SliderObject" + std::to_wstring(i) + L"_";

		std::wstring name;
		dataStore->GetValue(false, dataID, objectKey, key + L"name", name);

		SP(Engine::CSlider) slider =
			std::dynamic_pointer_cast<Engine::CSlider>(pScene->GetObjectFactory()->AddClone(L"Slider", true, (_int)Engine::ELayerID::UI, name));

		_float3 pos;
		dataStore->GetValue(false, dataID, objectKey, key + L"position", pos);
		slider->GetTransform()->SetPosition(pos);

		_int dir;
		dataStore->GetValue(false, dataID, objectKey, key + L"direction", dir);
		slider->SetDirection((Engine::CSlider::ESliderDirection)dir);

		_float sort;
		dataStore->GetValue(false, dataID, objectKey, key + L"sortLayer", sort);

		SP(Engine::CImageObject) imageObj[2];
		for (int j = 0; j < 2; j++)
		{
			imageObj[j] =
				std::dynamic_pointer_cast<Engine::CImageObject>(pScene->GetObjectFactory()->AddClone(L"ImageObject", true, (_int)Engine::ELayerID::UI, L"Image" + name));

			_float3 pos;
			dataStore->GetValue(false, dataID, objectKey, key + L"imagePosition" + std::to_wstring(j), pos);
			pos.x *= -1;

			imageObj[j]->GetTransform()->SetPosition(slider->GetTransform()->GetPosition() + pos);

			_float3 size;
			dataStore->GetValue(false, dataID, objectKey, key + L"imageSize" + std::to_wstring(j), size);
			size.z = 0;
			imageObj[j]->GetTransform()->SetSize(size);

			_float rotationZ;
			dataStore->GetValue(false, dataID, objectKey, key + L"imageRotationZ" + std::to_wstring(j), rotationZ);
			imageObj[j]->GetTransform()->SetRotationZ(D3DXToRadian(rotationZ));

			imageObj[j]->GetTransform()->SetPositionZ(sort);
			sort += 0.1f;

			std::wstring textureKey;
			dataStore->GetValue(false, dataID, objectKey, key + L"imageTextureKey" + std::to_wstring(j), textureKey);
			imageObj[j]->GetTexture()->AddTexture(textureKey, 0);
		}
		imageObj[0]->GetShader()->AddShader((_int)Engine::EShaderID::RectTexShader);
		imageObj[1]->SetParent(slider.get());

		_int imageType;
		dataStore->GetValue(false, dataID, objectKey, key + L"imageType", imageType);

		if (imageType == 0)
		{
			imageObj[1]->GetComponent<Engine::CShaderC>()->
				AddShader((_int)Engine::EShaderID::SliderShader);
		}
		else if(imageType == 1)
		{
			imageObj[1]->GetComponent<Engine::CShaderC>()->
				AddShader((_int)EShaderID::CircularGaugeShader);
		}

		_float value, maxValue, minValue;
		dataStore->GetValue(false, dataID, objectKey, key + L"value", value);
		dataStore->GetValue(false, dataID, objectKey, key + L"maxValue", maxValue);
		dataStore->GetValue(false, dataID, objectKey, key + L"minValue", minValue);

		slider->AddSliderData(value, maxValue, minValue, imageObj[0], imageObj[1]);
	}
}

void CDataLoad::ButtonLoad(Engine::CScene* pScene)
{
	Engine::CDataStore* dataStore = pScene->GetDataStore();

	_int numOfButtonObject;
	_int dataID = (_int)EDataID::UI;
	std::wstring objectKey = L"ButtonDataFile";
	dataStore->GetValue(false, dataID, objectKey, L"numOfbuttonObject", numOfButtonObject);

	for (_int i = 0; i < numOfButtonObject; ++i)
	{
		std::wstring key = L"buttonObject" + std::to_wstring(i) + L"_";

		std::wstring name;
		dataStore->GetValue(false, dataID, objectKey, key + L"name", name);

		SP(CButton) button =
			std::dynamic_pointer_cast<CButton>(pScene->GetObjectFactory()->AddClone(L"Button", true, (_int)Engine::ELayerID::UI, name));
		_float3 position;
		dataStore->GetValue(false, dataID, objectKey, key + L"position", position);
		button->GetTransform()->SetPosition(position);

		_float3 size;
		dataStore->GetValue(false, dataID, objectKey, key + L"size", size);
		size.z = 0;
		button->GetTransform()->SetSize(size);

		_float sort;
		dataStore->GetValue(false, dataID, objectKey, key + L"sortLayer", sort);
		button->GetTransform()->SetPositionZ(sort);

		std::wstring textureKey;
		dataStore->GetValue(false, dataID, objectKey, key + L"textureKey", textureKey);
		button->GetTexture()->AddTexture(textureKey, 0);

		std::wstring pressedTextureKey;
		dataStore->GetValue(false, dataID, objectKey, key + L"pressedTextureKey", pressedTextureKey);
		button->GetTexture()->AddTexture(pressedTextureKey, 0);

		std::wstring buttonfunction;
		dataStore->GetValue(false, dataID, objectKey, key + L"buttonFunction", buttonfunction);
		ButtonFunction(button, buttonfunction);

		_int buttonType;
		dataStore->GetValue(false, dataID, objectKey, key + L"buttonType", buttonType);
		button->SetButtonType((CButton::EButton_Type)buttonType);

		std::wstring message;
		_float2 fontPosition;
		_int fontSize;
		_float4 color;// = D3DXCOLOR(1, 1, 1, 1);
		std::wstring alignment;

		dataStore->GetValue(false, dataID, objectKey, key + L"fontName", name);
		button->GetShader()->AddShader((_int)Engine::EShaderID::RectTexShader);

		if (name == L"Not")
		{
			continue;
		}

		dataStore->GetValue(false, dataID, objectKey, key + L"message", message);
		dataStore->GetValue(false, dataID, objectKey, key + L"fontPosition", fontPosition);
		dataStore->GetValue(false, dataID, objectKey, key + L"fontSize", fontSize);
		dataStore->GetValue(false, dataID, objectKey, key + L"color", color);
		dataStore->GetValue(false, dataID, objectKey, key + L"alignment", alignment);
		fontPosition.y *= -1;

		if (alignment == L"UpperLeft")
		{
			button->AddComponent<Engine::CTextC>()->AddFontData(message, fontPosition, _float2(0, 0), fontSize, DT_VCENTER + DT_LEFT + DT_NOCLIP, (D3DXCOLOR)color, true);

		}
		else if (alignment == L"UpperRight")
		{
			button->AddComponent<Engine::CTextC>()->AddFontData(message, fontPosition, _float2(0, 0), fontSize, DT_VCENTER + DT_RIGHT + DT_NOCLIP, (D3DXCOLOR)color, true);

		}
		else if (alignment == L"UpperCenter")
		{
			button->AddComponent<Engine::CTextC>()->AddFontData(message, fontPosition, _float2(0, 0), fontSize, DT_VCENTER + DT_CENTER + DT_NOCLIP, (D3DXCOLOR)color, true);
		}
	}
}

void CDataLoad::ScrollViewLoad(Engine::CScene* pScene)
{
	Engine::CDataStore* dataStore = pScene->GetDataStore();

	_int numOfScrollViewObject;
	_int dataID = (_int)EDataID::UI;
	std::wstring objectKey = L"ScrollViewDataFile";
	dataStore->GetValue(false, dataID, objectKey, L"numOfScrollViewObject", numOfScrollViewObject);

	for (_int i = 0; i < numOfScrollViewObject; ++i)
	{
		std::wstring key = L"ScrollObject" + std::to_wstring(i) + L"_";

		std::wstring name;
		dataStore->GetValue(false, dataID, objectKey, key + L"name", name);


		SP(CScrollViewObject) spScrollView =
			std::dynamic_pointer_cast<CScrollViewObject>(pScene->GetObjectFactory()->AddClone(L"ScrollViewObject", true, (_int)Engine::ELayerID::UI, name));

		_float3 pos;
		dataStore->GetValue(false, dataID, objectKey, key + L"position", pos);

		_float3 size;
		dataStore->GetValue(false, dataID, objectKey, key + L"size", size);

		_float sortLayer;
		dataStore->GetValue(false, dataID, objectKey, key + L"sortLayer", sortLayer);

		std::wstring textureKey;
		dataStore->GetValue(false, dataID, objectKey, key + L"textureKey", textureKey);

		_int column;
		dataStore->GetValue(false, dataID, objectKey, key + L"column", column);

		_float2 distanceXY;
		dataStore->GetValue(false, dataID, objectKey, key + L"distanceXY", distanceXY);

		_float2 offSet;
		dataStore->GetValue(false, dataID, objectKey, key + L"offSet", offSet);

		spScrollView->GetTransform()->SetPosition(pos);
		spScrollView->GetTransform()->SetPositionZ(sortLayer);
		spScrollView->GetTransform()->SetSize(size);
		//spScrollView->GetTexture()->ChangeTexture(textureKey);
		spScrollView->AddScrollViewData(column, distanceXY, offSet);
	}
}

void CDataLoad::CanvasLoad(Engine::CScene * pScene)
{
	Engine::CDataStore* dataStore = pScene->GetDataStore();

	_int numOfCanvasObject;
	_int dataID = (_int)EDataID::UI;
	std::wstring objectKey = L"CanvasDataFile";
	dataStore->GetValue(false, dataID, objectKey, L"numOfCanvasObject", numOfCanvasObject);

	for (_int i = 0; i < numOfCanvasObject; ++i)
	{
		std::wstring key = L"CanvasObject" + std::to_wstring(i) + L"_";

		std::wstring name;
		dataStore->GetValue(false, dataID, objectKey, key + L"name", name);

		SP(Engine::CCanvas) canvas =
			std::dynamic_pointer_cast<Engine::CCanvas>(pScene->GetObjectFactory()->AddClone(L"Canvas", true, (_int)Engine::ELayerID::UI, name));
	}
}

void CDataLoad::TextLoad(Engine::CScene * pScene)
{
	Engine::CDataStore* dataStore = pScene->GetDataStore();

	_int numOfImageObject;
	_int dataID = (_int)EDataID::UI;
	std::wstring objectKey = L"TextDataFile";
	dataStore->GetValue(false, dataID, objectKey, L"numOfTextObject", numOfImageObject);

	for (_int i = 0; i < numOfImageObject; ++i)
	{
		std::wstring key = L"TextObject" + std::to_wstring(i) + L"_";

		std::wstring name;
		dataStore->GetValue(false, dataID, objectKey, key + L"textName", name);

		SP(Engine::CObject) text = pScene->GetObjectFactory()->AddClone(L"TextObject", true, (_int)Engine::ELayerID::UI, name);

		_float sort;
		dataStore->GetValue(false, dataID, objectKey, key + L"Sort", sort);
		text->GetTransform()->SetPositionZ(sort);

		std::wstring message;
		_float2 fontPosition;
		_int fontSize;
		_float4 color;// = D3DXCOLOR(1, 1, 1, 1);
		std::wstring alignment;

		dataStore->GetValue(false, dataID, objectKey, key + L"message", message);
		dataStore->GetValue(false, dataID, objectKey, key + L"textPosition", fontPosition);
		dataStore->GetValue(false, dataID, objectKey, key + L"textSize", fontSize);
		dataStore->GetValue(false, dataID, objectKey, key + L"color", color);
		dataStore->GetValue(false, dataID, objectKey, key + L"alignment", alignment);
		fontPosition.y *= -1;

		if (alignment == L"UpperLeft")
		{
			text->AddComponent<Engine::CTextC>()->AddFontData(message, fontPosition, _float2(0, 0), fontSize, DT_VCENTER + DT_LEFT+ DT_NOCLIP, (D3DXCOLOR)color, true);

		}
		else if (alignment == L"UpperRight")
		{
			text->AddComponent<Engine::CTextC>()->AddFontData(message, fontPosition, _float2(0, 0), fontSize, DT_VCENTER + DT_RIGHT + DT_NOCLIP, (D3DXCOLOR)color, true);

		}
		else if (alignment == L"UpperCenter")
		{
			text->AddComponent<Engine::CTextC>()->AddFontData(message, fontPosition, _float2(0, 0), fontSize, DT_VCENTER + DT_CENTER + DT_NOCLIP, (D3DXCOLOR)color, true);
		}

	}

}

void CDataLoad::MapLoad(Engine::CScene* pScene)
{
	auto& pDataStore = pScene->GetDataStore();
	auto& pObjectFactory = pScene->GetObjectFactory();

	/* deco */
	_int numOfDecoObject;
	pDataStore->GetValue(false, (_int)EDataID::Scene, L"mapDecoration", L"numOfDecoObject", numOfDecoObject);
	for (_int i = 0; i < numOfDecoObject; ++i)
	{
		SP(CDecoObject) spDecoObject =
			std::dynamic_pointer_cast<CDecoObject>(pObjectFactory->AddClone(L"DecoObject", true));


		_float3 position, rotation, size;

		//GETVALUE
		pDataStore->GetValue(false, (_int)EDataID::Scene, L"mapDecoration",
			std::to_wstring(i) + L"_position", position);

		pDataStore->GetValue(false, (_int)EDataID::Scene, L"mapDecoration",
			std::to_wstring(i) + L"_rotation", rotation);

		pDataStore->GetValue(false, (_int)EDataID::Scene, L"mapDecoration",
			std::to_wstring(i) + L"_size", size);

		spDecoObject->GetTransform()->SetPosition(position);
		spDecoObject->GetTransform()->SetRotation(rotation);
		spDecoObject->GetTransform()->SetSize(size);


		std::wstring meshKey;
		pDataStore->GetValue(false, (_int)EDataID::Scene, L"mapDecoration",
							 std::to_wstring(i) + L"_meshKey", meshKey);

		spDecoObject->GetMesh()->SetMeshData(meshKey);



		_int numOfTexSet;
		pDataStore->GetValue(false, (_int)EDataID::Scene, L"mapDecoration",
							std::to_wstring(i) + L"_numOfTexSet", numOfTexSet);

		for (_int k = 0; k < numOfTexSet; ++k)
		{
			_int numOfTex;

			pDataStore->GetValue(false, (_int)EDataID::Scene, L"mapDecoration",
								std::to_wstring(i) + L"_numOfTex" + std::to_wstring(k), numOfTex);

			for (_int l = 0; l < numOfTex; ++l)
			{
				std::wstring textureKey;
				pDataStore->GetValue(false, (_int)EDataID::Scene, L"mapDecoration",
									 std::to_wstring(i) + L"_textureKey" + std::to_wstring(k) + L'_' + std::to_wstring(l), textureKey);

				spDecoObject->GetTexture()->AddTexture(textureKey, k);
			}
		}

		_int renderID;
		pDataStore->GetValue(false, (_int)EDataID::Scene, L"mapDecoration",
							 std::to_wstring(i) + L"_renderID", renderID);
		spDecoObject->GetGraphics()->SetRenderID(renderID);

		if (L"Stage02_Alpha_WaterPlane" == meshKey)
		{			
			spDecoObject->GetComponent<Engine::CTextureC>()->AddTexture(L"waterNor");
			spDecoObject->GetComponent<Engine::CTextureC>()->AddTexture(L"water");
			spDecoObject->GetComponent<Engine::CShaderC>()->AddShader((_int)EShaderID::WaterShader);
		}
		else if(renderID == 1)
			spDecoObject->GetComponent<Engine::CShaderC>()->AddShader((_int)Engine::EShaderID::MeshShader);
		else
			spDecoObject->GetComponent<Engine::CShaderC>()->AddShader((_int)Engine::EShaderID::MeshAlphaTestShader);

	}

	_int numOfMapObject;
	pDataStore->GetValue(false, (_int)EDataID::Scene, L"mapMapObject", L"numOfMapObject", numOfMapObject);
	for (_int i = 0; i < numOfMapObject; ++i)
	{
		SP(CMapObject) spMapObject =
			std::dynamic_pointer_cast<CMapObject>(pObjectFactory->AddClone(L"MapObject", true));


		spMapObject->AddComponent<Engine::CDebugC>();

		_float3 position, rotation, size;

		//GETVALUE
		pDataStore->GetValue(false, (_int)EDataID::Scene, L"mapMapObject",
			std::to_wstring(i) + L"_position", position);

		pDataStore->GetValue(false, (_int)EDataID::Scene, L"mapMapObject",
			std::to_wstring(i) + L"_rotation", rotation);

		pDataStore->GetValue(false, (_int)EDataID::Scene, L"mapMapObject",
			std::to_wstring(i) + L"_size", size);

		spMapObject->GetTransform()->SetPosition(position);
		spMapObject->GetTransform()->SetRotation(rotation);
		spMapObject->GetTransform()->SetSize(size);

		std::wstring meshKey;
		pDataStore->GetValue(false, (_int)EDataID::Scene, L"mapMapObject",
							 std::to_wstring(i) + L"_meshKey", meshKey);

		spMapObject->GetMesh()->SetMeshData(meshKey);


		_int numOfTexSet;
		pDataStore->GetValue(false, (_int)EDataID::Scene, L"mapMapObject",
							 std::to_wstring(i) + L"_numOfTexSet", numOfTexSet);

		for (_int k = 0; k < numOfTexSet; ++k)
		{
			_int numOfTex;
			pDataStore->GetValue(false, (_int)EDataID::Scene, L"mapMapObject",
								 std::to_wstring(i) + L"_numOfTex" + std::to_wstring(k), numOfTex);

			for (_int l = 0; l < numOfTex; ++l)
			{
				std::wstring textureKey;
				pDataStore->GetValue(false, (_int)EDataID::Scene, L"mapMapObject",
									 std::to_wstring(i) + L"_textureKey" + std::to_wstring(k) + L'_' + std::to_wstring(l), textureKey);

				spMapObject->GetTexture()->AddTexture(textureKey, k);
			}
		}

		_int renderID;
		pDataStore->GetValue(false, (_int)EDataID::Scene, L"mapMapObject",
			std::to_wstring(i) + L"_renderID", renderID);
		spMapObject->GetGraphics()->SetRenderID(renderID);
		spMapObject->AddComponent<Engine::CShaderC>()->AddShader((_int)Engine::EShaderID::MeshShader);


		/* map */
		_int numOfCollider;
		pDataStore->GetValue(false, (_int)EDataID::Scene, L"mapMapObject", std::to_wstring(i) + L"_numOfCollider", numOfCollider);
		for (_int j = 0; j < numOfCollider; ++j)
		{
			_int colliderType;
			pDataStore->GetValue(false, (_int)EDataID::Scene, L"mapMapObject",
				std::to_wstring(i) + L"_colliderType" + std::to_wstring(j), colliderType);

			_int collisionID;
			pDataStore->GetValue(false, (_int)EDataID::Scene, L"mapMapObject",
				std::to_wstring(i) + L"_colliderCollisionID" + std::to_wstring(j), collisionID);

			_float3 offset;
			pDataStore->GetValue(false, (_int)EDataID::Scene, L"mapMapObject",
				std::to_wstring(i) + L"_colliderOffset" + std::to_wstring(j), offset);

			_float radius; // sphere
			_float3 size; // aabb or obb
			_float3 rotOffset; // obb

			switch (colliderType)
			{
			case (_int)Engine::EColliderType::Point:
				break;
			case (_int)Engine::EColliderType::Ray:
				break;
			case (_int)Engine::EColliderType::Sphere:
				pDataStore->GetValue(false, (_int)EDataID::Scene, L"mapMapObject",
					std::to_wstring(i) + L"_colliderRadius" + std::to_wstring(j), radius);

				spMapObject->GetComponent<Engine::CCollisionC>()->AddCollider(Engine::CSphereCollider::Create(collisionID, radius, offset));
				break;
			case (_int)Engine::EColliderType::AABB:
				pDataStore->GetValue(false, (_int)EDataID::Scene, L"mapMapObject",
					std::to_wstring(i) + L"_colliderSize" + std::to_wstring(j), size);

				spMapObject->GetComponent<Engine::CCollisionC>()->AddCollider(Engine::CAabbCollider::Create(collisionID, size, offset));
				break;
			case (_int)Engine::EColliderType::OBB:
				pDataStore->GetValue(false, (_int)EDataID::Scene, L"mapMapObject",
					std::to_wstring(i) + L"_colliderSize" + std::to_wstring(j), size);
				pDataStore->GetValue(false, (_int)EDataID::Scene, L"mapMapObject",
					std::to_wstring(i) + L"_colliderRotOffset" + std::to_wstring(j), rotOffset);

				spMapObject->GetComponent<Engine::CCollisionC>()->AddCollider(Engine::CObbCollider::Create(collisionID, size, offset, rotOffset));
				break;
			}
		}
	}
}

void CDataLoad::PhaseChangerLoad(Engine::CScene * pScene)
{
	auto& pDataStore = pScene->GetDataStore();
	auto& pObjectFactory = pScene->GetObjectFactory();

	std::vector<CPhaseChanger*> vPhaseChanger;
	_int numOfPhaseChanger;
	pDataStore->GetValue(false, (_int)EDataID::Scene, L"mapPhaseChanger", L"numOfPhaseChanger", numOfPhaseChanger);
	for (_int i = 0; i < numOfPhaseChanger; ++i)
	{
		SP(CPhaseChanger) spPhaseChanger =
			std::dynamic_pointer_cast<CPhaseChanger>(pObjectFactory->AddClone(L"PhaseChanger", true));

		_float3 position;
		pDataStore->GetValue(false, (_int)EDataID::Scene, L"mapPhaseChanger", std::to_wstring(i) + L"_position", position);
		spPhaseChanger->GetTransform()->SetPosition(position);

		_float3 rotation;
		pDataStore->GetValue(false, (_int)EDataID::Scene, L"mapPhaseChanger", std::to_wstring(i) + L"_rotation", rotation);
		spPhaseChanger->GetTransform()->SetRotation(rotation);

		_float3 size;
		pDataStore->GetValue(false, (_int)EDataID::Scene, L"mapPhaseChanger", std::to_wstring(i) + L"_size", size);
		spPhaseChanger->GetCollision()->AddCollider(Engine::CObbCollider::Create((_int)ECollisionID::PhaseChanger, size), true);

		_int phaseToDie;
		pDataStore->GetValue(false, (_int)EDataID::Scene, L"mapPhaseChanger", std::to_wstring(i) + L"_phaseToDie", phaseToDie);
		spPhaseChanger->SetPhaseToDie(phaseToDie);

		_int numOfRestrictLine;
		pDataStore->GetValue(false, (_int)EDataID::Scene, L"mapPhaseChanger", std::to_wstring(i) + L"_numOfRestrictLine", numOfRestrictLine);

		vPhaseChanger.emplace_back(spPhaseChanger.get());
		for (_int j = 0; j < numOfRestrictLine; ++j)
		{
			SP(CMapObject2D) spRestrictLine =
				std::dynamic_pointer_cast<CMapObject2D>(pObjectFactory->AddClone(L"MapObject2D", true));

			spRestrictLine->GetRectTex()->SetIsOrtho(false);
			spRestrictLine->GetGraphics()->SetRenderID((_int)Engine::ERenderID::AlphaTest);
			spRestrictLine->GetShader()->AddShader((_int)Engine::EShaderID::RectTexShader);

			std::wstring texKey;
			pDataStore->GetValue(false, (_int)EDataID::Scene, L"mapPhaseChanger", std::to_wstring(i) +
				L"_wall" +
				std::to_wstring(j) +
				L"_textureKey", texKey);
			spRestrictLine->GetComponent<Engine::CTextureC>()->AddTexture(texKey);

			pDataStore->GetValue(false, (_int)EDataID::Scene, L"mapPhaseChanger", std::to_wstring(i) +
				L"_wall" +
				std::to_wstring(j) +
				L"_position", position);
			spRestrictLine->GetTransform()->SetPosition(position);

			pDataStore->GetValue(false, (_int)EDataID::Scene, L"mapPhaseChanger", std::to_wstring(i) +
				L"_wall" +
				std::to_wstring(j) +
				L"_rotation", rotation);
			spRestrictLine->GetTransform()->SetRotation(rotation);

			pDataStore->GetValue(false, (_int)EDataID::Scene, L"mapPhaseChanger", std::to_wstring(i) +
				L"_wall" +
				std::to_wstring(j) +
				L"_size", size);
			spRestrictLine->GetTransform()->SetSize(size);

			pDataStore->GetValue(false, (_int)EDataID::Scene, L"mapPhaseChanger", std::to_wstring(i) +
				L"_wall" +
				std::to_wstring(j) +
				L"_colSize", size);
			spRestrictLine->GetCollision()->AddCollider(Engine::CObbCollider::Create((_int)ECollisionID::Wall, size));

			spPhaseChanger->AddRestrictLine(spRestrictLine);
		}
	}

	_int numOfMonster;
	pDataStore->GetValue(false, (_int)EDataID::Scene, L"mapMonsterSpawn", L"numOfMonster", numOfMonster);
	for (_int i = 0; i < numOfMonster; ++i)
	{
		std::wstring monsterType;
		pDataStore->GetValue(false, (_int)EDataID::Scene, L"mapMonsterSpawn", std::to_wstring(i) +
			L"_type", monsterType);

		SP(CMonster) spMonster =
			std::dynamic_pointer_cast<CMonster>(pObjectFactory->AddClone(monsterType, true));

		_bool isBoss;
		pDataStore->GetValue(false, (_int)EDataID::Scene, L"mapMonsterSpawn", std::to_wstring(i) +
			L"_boss", isBoss);

		_int phaseChangerNum;
		pDataStore->GetValue(false, (_int)EDataID::Scene, L"mapMonsterSpawn", std::to_wstring(i) +
			L"_phaseChanger", phaseChangerNum);
		vPhaseChanger[phaseChangerNum]->AddMonster(spMonster);

		_float3 position;
		pDataStore->GetValue(false, (_int)EDataID::Scene, L"mapMonsterSpawn", std::to_wstring(i) +
			L"_position", position);
		spMonster->GetTransform()->SetPosition(position);

		_float3 rotation;
		pDataStore->GetValue(false, (_int)EDataID::Scene, L"mapMonsterSpawn", std::to_wstring(i) +
			L"_rotation", rotation);
		spMonster->GetTransform()->SetRotation(rotation);

		_float timer;
		pDataStore->GetValue(false, (_int)EDataID::Scene, L"mapMonsterSpawn", std::to_wstring(i) +
			L"_timer", timer);
		spMonster->SetSpawnTimer(timer);
	}
}

void CDataLoad::PortalLoad(Engine::CScene * pScene)
{
	auto& pDataStore = pScene->GetDataStore();
	auto& pObjectFactory = pScene->GetObjectFactory();

	
	_int numOfPortal;
	pDataStore->GetValue(false, (_int)EDataID::Scene, L"mapPortal", L"numOfPortal", numOfPortal);
	for (_int i = 0; i < numOfPortal; ++i)
	{
		SP(CPortal) spPortal =
			std::dynamic_pointer_cast<CPortal>(pObjectFactory->AddClone(L"Portal", true));

		_float3 position;
		pDataStore->GetValue(false, (_int)EDataID::Scene, L"mapPortal", std::to_wstring(i) + L"_position", position);
		spPortal->GetTransform()->SetPosition(position);

		_float3 rotation;
		pDataStore->GetValue(false, (_int)EDataID::Scene, L"mapPortal", std::to_wstring(i) + L"_rotation", rotation);
		spPortal->GetTransform()->SetRotation(rotation);

		_float3 size;
		pDataStore->GetValue(false, (_int)EDataID::Scene, L"mapPortal", std::to_wstring(i) + L"_size", size);
		spPortal->GetTransform()->SetSize(size);

		_float3 dest;
		pDataStore->GetValue(false, (_int)EDataID::Scene, L"mapPortal", std::to_wstring(i) + L"_dest", dest);
		spPortal->SetDestPos(dest);
	}
}

void CDataLoad::EffectLoad(Engine::CScene * pScene)
{
}

void CDataLoad::ButtonFunction(SP(CButton) button, std::wstring function)
{
	if (0 == function.compare(L"MainRoomScene"))
	{
		button->AddFuncData<void(CButtonFunction::*)(), CButtonFunction*>(&CButtonFunction::MainRoomScene, &CButtonFunction());
	}
	else if (0 == function.compare(L"StageSelectionScene"))
	{
		button->AddFuncData<void(CButtonFunction::*)(), CButtonFunction*>(&CButtonFunction::StageSelectionScene, &CButtonFunction());
	}
	else if (0 == function.compare(L"ReadyToSortieScene"))
	{
		button->AddFuncData<void(CButtonFunction::*)(), CButtonFunction*>(&CButtonFunction::ReadyToSortieScene, &CButtonFunction());
	}
	else if (0 == function.compare(L"PartySettingScene")) 
	{
		button->AddFuncData<void(CButtonFunction::*)(), CButtonFunction*>(&CButtonFunction::PartySettingScene, &CButtonFunction());
	}
	else if (0 == function.compare(L"BattleEndScene"))
	{
		button->AddFuncData<void(CButtonFunction::*)(), CButtonFunction*>(&CButtonFunction::BattleEndScene, &CButtonFunction());
	}
	else if (0 == function.compare(L"Sally"))
	{
		button->AddFuncData<void(CButtonFunction::*)(), CButtonFunction*>(&CButtonFunction::Sally, &CButtonFunction());
	}
	else if (0 == function.compare(L"ObjectOn"))
	{
		button->AddFuncData<void(CButtonFunction::*)(), CButtonFunction*>(&CButtonFunction::ObjectOn, &CButtonFunction());
	}
	else if (0 == function.compare(L"ObjectOff"))
	{
		button->AddFuncData<void(CButtonFunction::*)(), CButtonFunction*>(&CButtonFunction::ObjectOff, &CButtonFunction());
	}
	else if (0 == function.compare(L"BattleRenunciation"))
	{
		button->AddFuncData<void(CButtonFunction::*)(), CButtonFunction*>(&CButtonFunction::BattleRenunciation, &CButtonFunction());
	}
	else if (0 == function.compare(L"ChangeFSMProperty"))
	{
		button->AddFuncData<void(CValkyriegManager::*)(), CValkyriegManager*>(&CValkyriegManager::ChangeFSMProperty, CValkyriegManager::GetInstance());
	}
	else if (0 == function.compare(L"ChangeFSMLevelUp"))
	{
		button->AddFuncData<void(CValkyriegManager::*)(), CValkyriegManager*>(&CValkyriegManager::ChangeFSMLevelUp, CValkyriegManager::GetInstance());
	}
	else if (0 == function.compare(L"LevelUp"))
	{
		button->AddFuncData<void(CValkyrieLevelUp::*)(), CValkyrieLevelUp*>(&CValkyrieLevelUp::LevelUp, &CValkyrieLevelUp());
	}
	else if (0 == function.compare(L"ItemCountUp"))
	{
		button->AddFuncData<void(CValkyrieLevelUp::*)(), CValkyrieLevelUp*>(&CValkyrieLevelUp::ItemCountUp, &CValkyrieLevelUp());
	}
	else if (0 == function.compare(L"ItemCountDown"))
	{
		button->AddFuncData<void(CValkyrieLevelUp::*)(), CValkyrieLevelUp*>(&CValkyrieLevelUp::ItemCountDown, &CValkyrieLevelUp());
	}
	else if (0 == function.compare(L"ItemSelect"))
	{
		button->AddFuncData<void(CValkyrieLevelUp::*)(), CValkyrieLevelUp*>(&CValkyrieLevelUp::ItemSelect, &CValkyrieLevelUp());
	}
	else if (0 == function.compare(L"ChangeFSMSelect"))
	{
		button->AddFuncData<void(CValkyriegManager::*)(), CValkyriegManager*>(&CValkyriegManager::ChangeFSMSelect, CValkyriegManager::GetInstance());
	}
	else if (0 == function.compare(L"InventoryScene"))
	{
		button->AddFuncData<void(CButtonFunction::*)(), CButtonFunction*>(&CButtonFunction::InventoryScene, &CButtonFunction());
	}
	else if (0 == function.compare(L"WeaponFSM"))
	{
		button->AddFuncData<void(CInventoryManager::*)(), CInventoryManager*>(&CInventoryManager::WeaponFSM, CInventoryManager::GetInstance());
	}
	else if (0 == function.compare(L"ItemFSM"))
	{
		button->AddFuncData<void(CInventoryManager::*)(), CInventoryManager*>(&CInventoryManager::ItemFSM, CInventoryManager::GetInstance());
	}
	else if (0 == function.compare(L"ChangeFSMWeapon"))
	{
		button->AddFuncData<void(CValkyriegManager::*)(), CValkyriegManager*>(&CValkyriegManager::ChangeFSMWeapon, CValkyriegManager::GetInstance());
	}
	else if (0 == function.compare(L"changeFSMWeaponSwap"))
	{
		button->AddFuncData<void(CValkyriegManager::*)(), CValkyriegManager*>(&CValkyriegManager::changeFSMWeaponSwap, CValkyriegManager::GetInstance());
	}
	else if (0 == function.compare(L"WeaponChange"))
	{
		button->AddFuncData<void(CValkyrieWeaponSwap::*)(), CValkyrieWeaponSwap*>(&CValkyrieWeaponSwap::WeaponChange, &CValkyrieWeaponSwap());
	}
	
}
