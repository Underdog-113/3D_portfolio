#include "stdafx.h"
#include "DataLoad.h"
#include "DataStore.h"

#include "UiAnimCtrC.h"

#include "ImageObject.h"
#include "Button.h"
#include "Slider.h"
#include "ButtonFunction.h"
#include "ScrollViewObject.h"
#include "Canvas.h"

#include "ObjectFactory.h"
#include "MeshData.h"

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
	//m_loadDeleGate += std::bind(&CDataLoad::ToolLoad, &CDataLoad(), std::placeholders::_1);
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

		std::wstring message;
		_float2 fontPosition;
		_int fontSize;
		D3DXCOLOR color = D3DXCOLOR(1,1,1,1);

		dataStore->GetValue(false, dataID, objectKey, key + L"fontName", name);

		if (name != L"Not")
		{
			dataStore->GetValue(false, dataID, objectKey, key + L"message", message);
			dataStore->GetValue(false, dataID, objectKey, key + L"fontPosition", fontPosition);
			dataStore->GetValue(false, dataID, objectKey, key + L"fontSize", fontSize);
			//dataStore->GetValue(false, dataID, objectKey, L"imageObejct" + std::to_wstring(i) + L"color", (_float4)color);
			fontPosition.y *= -1;
			image->AddComponent<Engine::CTextC>()->AddFontData(message, fontPosition, _float2(0, 0), fontSize, DT_VCENTER + DT_CENTER + DT_NOCLIP, color, true);
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

				image->GetTexture()->AddTexture(textureKey, 0);
			}
		}

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

		_int imageType;
		dataStore->GetValue(false, dataID, objectKey, key + L"imageType", imageType);
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

		imageObj[1]->SetParent(slider.get());
		if (imageType == 0)
		{
			imageObj[1]->AddComponent<Engine::CShaderC>()->
				AddShader(Engine::CShaderManager::GetInstance()->GetShaderID((L"SliderShader")));
		}
		else if(imageType == 1)
		{
			imageObj[1]->AddComponent<Engine::CShaderC>()->
				AddShader(Engine::CShaderManager::GetInstance()->GetShaderID((L"CircularGaugeShader")));
		}

		_float value, maxValue, minValue;
		dataStore->GetValue(false, dataID, objectKey, key + L"value", value);
		dataStore->GetValue(false, dataID, objectKey, key + L"maxValue", maxValue);
		dataStore->GetValue(false, dataID, objectKey, key + L"minValue", minValue);

		slider->AddSliderData(maxValue, maxValue, minValue, imageObj[0], imageObj[1]);
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
		D3DXCOLOR color = D3DXCOLOR(1, 1, 1, 1);

		dataStore->GetValue(false, dataID, objectKey, key + L"fontName", name);

		if (name == L"Not")
		{
			continue;
		}

		dataStore->GetValue(false, dataID, objectKey, key + L"message", message);
		dataStore->GetValue(false, dataID, objectKey, key + L"fontPosition", fontPosition);
		dataStore->GetValue(false, dataID, objectKey, key + L"fontSize", fontSize);
		//dataStore->GetValue(false, dataID, objectKey, L"imageObejct" + std::to_wstring(i) + L"color", (_float4)color);

		fontPosition.y *= -1;
		button->AddComponent<Engine::CTextC>()->AddFontData(message, fontPosition, _float2(0, 0), fontSize, DT_VCENTER + DT_CENTER + DT_NOCLIP, color, true);
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
		spScrollView->GetTexture()->AddTexture(textureKey, 0);
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

void CDataLoad::ToolLoad(Engine::CScene* pScene)
{
	auto& objectFactory = pScene->GetObjectFactory();

	// 데이터 파일 불러오기
	std::string strLine = "";
	std::string filePath = "../../Data/EditorScene/save.ini";
	std::ifstream ifsLoad(filePath.data());

	_float vPos = 0.f;
	_float vRot = 0.f;

	std::wstring protoObjectKey;
	_bool isStatic;
	_int layerID;
	std::wstring meshKey;
	_bool initTex;
	_int renderID;
	_float3 position;
	_float3 scale;
	_float3 rotation;
	_int colID; // collider
	_float3 offset; // collider
	_float3 size; // collider
	_float3 rotOffset; // collider
	_int shaderID;

	SP(Engine::CObject) spObject = nullptr;

	while (!ifsLoad.eof())
	{
		Engine::_tchar* dataTag = nullptr;
		Engine::_tchar* dataValue = nullptr;

		std::getline(ifsLoad, strLine);

		if ("" == strLine)
			continue;

		std::vector<std::string> vStr = split(strLine, '=');

		if (!dataValue && !dataTag)
		{
			std::wstring wstr = Engine::StrToWStr(vStr[1]);
			dataValue = _wcsdup(wstr.c_str());
		}

		if (!wcscmp(L"numOfEmptyObject", _wcsdup(Engine::StrToWStr(vStr[0]).c_str())))
			continue;

		std::vector<std::string> vStrTag = split(vStr[0], '_');

		std::wstring wstr = Engine::StrToWStr(vStrTag[1]);
		dataTag = _wcsdup(wstr.c_str());

		if (!wcscmp(L"static", dataTag))
		{
			isStatic = WstrToBool(dataValue);
			continue;
		}
		else if (!wcscmp(L"layerID", dataTag))
		{
			layerID = WstrToInt(dataValue);
			spObject = objectFactory->AddClone(L"EmptyObject", isStatic, layerID, Engine::StrToWStr(vStrTag[0]));

			spObject->SetLayerID(layerID);
			continue;
		}
		else if (!wcscmp(L"shaderKey", dataTag))
		{
			shaderID = WstrToInt(dataValue);
			spObject->AddComponent<Engine::CShaderC>()->AddShader(shaderID);
			continue;
		}
		else if (!wcscmp(L"meshKey", dataTag))
		{
			meshKey = dataValue;

			spObject->AddComponent<Engine::CMeshC>()->AddMeshData(meshKey);
			
			continue;
		}
		else if (!wcscmp(L"initTex", dataTag))
		{
			initTex = WstrToBool(dataValue);
			spObject->GetComponent<Engine::CMeshC>()->SetInitTex(initTex);

			if (initTex == true)
			{
				if (L"Cube" != spObject->GetComponent<Engine::CMeshC>()->GetMeshDatas()[0]->GetMeshKey())
					spObject->AddComponent<Engine::CTextureC>();
				else
					spObject->AddComponent<Engine::CTextureC>()->AddTexture(L"Castle_wall", 0);

				//고쳐야됨 쉐이더키 따로 세팅하기
				if (spObject->GetComponent<Engine::CShaderC>() == nullptr)
					spObject->AddComponent<Engine::CShaderC>()->AddShader((_int)Engine::EShaderID::MeshShader);
			}
			else
			{
				spObject->AddComponent<Engine::CTextureC>();
				spObject->GetComponent<Engine::CTextureC>()->AddTexture(L"water");
				spObject->GetComponent<Engine::CTextureC>()->AddTexture(L"WaterNormalMap");
			}
			continue;
		}
		else if (!wcscmp(L"renderID", dataTag))
		{
			renderID = WstrToInt(dataValue);
			spObject->AddComponent<Engine::CGraphicsC>()->SetRenderID(renderID);
			spObject->GetComponent<Engine::CGraphicsC>()->SetColorReverse(false);
			continue;
		}
		else if (!wcscmp(L"scale", dataTag))
		{
			vStr = split(vStr[1], ',');
			scale = { StrToFloat(vStr[0]), StrToFloat(vStr[1]), StrToFloat(vStr[2]) };
			spObject->GetTransform()->SetSize(scale);
			continue;
		}
		else if (!wcscmp(L"rotation", dataTag))
		{
			vStr = split(vStr[1], ',');
			rotation = { StrToFloat(vStr[0]), StrToFloat(vStr[1]), StrToFloat(vStr[2]) };
			spObject->GetTransform()->SetRotation(rotation);
			continue;
		}
		else if (!wcscmp(L"position", dataTag))
		{
			vStr = split(vStr[1], ',');
			position = { StrToFloat(vStr[0]), StrToFloat(vStr[1]), StrToFloat(vStr[2]) };
			spObject->GetTransform()->SetPosition(position);
			continue;
		}
		else if (!wcscmp(L"collider", dataTag))
		{
			if (nullptr == spObject->GetComponent<Engine::CCollisionC>())
			{
				spObject->AddComponent<Engine::CCollisionC>();
				spObject->AddComponent<Engine::CDebugC>();
			}

			std::wstring wstr = Engine::StrToWStr(vStrTag[3]);
			if (L"collisionID" == wstr)
				colID = WstrToInt(dataValue);

			std::getline(ifsLoad, strLine);
			vStr = split(strLine, '=');
			vStrTag = split(vStr[0], '_');
			std::wstring type = Engine::StrToWStr(vStrTag[3]);

			_int index = StrToInt(vStr[1]);

			if (L"type" == type)
			{
				switch (index)
				{
				case 1: // ray
					break;
				case 3: // aabb
				{
					/* offset */
					std::getline(ifsLoad, strLine);
					vStr = split(strLine, '=');
					vStr = split(vStr[1], ',');
					offset = { StrToFloat(vStr[0]), StrToFloat(vStr[1]), StrToFloat(vStr[2]) };

					/* size */
					std::getline(ifsLoad, strLine);
					vStr = split(strLine, '=');
					vStr = split(vStr[1], ',');
					size = { StrToFloat(vStr[0]), StrToFloat(vStr[1]), StrToFloat(vStr[2]) };

					spObject->GetComponent<Engine::CCollisionC>()->AddCollider(Engine::CAabbCollider::Create(colID, size, offset));
					size_t colIdx = spObject->GetComponent<Engine::CCollisionC>()->GetColliders().size() - 1;
				}
				break;
				case 4: // obb
				{
					/* offset */
					std::getline(ifsLoad, strLine);
					vStr = split(strLine, '=');
					vStr = split(vStr[1], ',');
					offset = { StrToFloat(vStr[0]), StrToFloat(vStr[1]), StrToFloat(vStr[2]) };

					/* size */
					std::getline(ifsLoad, strLine);
					vStr = split(strLine, '=');
					vStr = split(vStr[1], ',');
					size = { StrToFloat(vStr[0]), StrToFloat(vStr[1]), StrToFloat(vStr[2]) };

					/* rotOffset */
					std::getline(ifsLoad, strLine);
					vStr = split(strLine, '=');
					vStr = split(vStr[1], ',');
					rotOffset = { StrToFloat(vStr[0]), StrToFloat(vStr[1]), StrToFloat(vStr[2]) };

					spObject->GetComponent<Engine::CCollisionC>()->AddCollider(Engine::CObbCollider::Create(colID, size, offset, rotOffset));
					size_t colIdx = spObject->GetComponent<Engine::CCollisionC>()->GetColliders().size() - 1;
					break;
				}
				}
			}
		}
	}
}

void CDataLoad::EffectLoad(Engine::CScene * pScene)
{
}

void CDataLoad::ButtonFunction(SP(CButton) button, std::wstring function)
{
	if (0 == function.compare(L"MainRoomScene")) // 메인씬
	{
		button->AddFuncData<void(CButtonFunction::*)(), CButtonFunction*>(&CButtonFunction::MainRoomScene, &CButtonFunction());
	}
	else if (0 == function.compare(L"StageSelectionScene")) // 스테이지 고르는씬
	{
		button->AddFuncData<void(CButtonFunction::*)(), CButtonFunction*>(&CButtonFunction::StageSelectionScene, &CButtonFunction());
	}
	else if (0 == function.compare(L"ReadyToSortieScene")) // 케릭터 프리셋
	{
		button->AddFuncData<void(CButtonFunction::*)(), CButtonFunction*>(&CButtonFunction::ReadyToSortieScene, &CButtonFunction());
	}
	else if (0 == function.compare(L"PartySettingScene")) //  케릭터 파티
	{
		button->AddFuncData<void(CButtonFunction::*)(), CButtonFunction*>(&CButtonFunction::PartySettingScene, &CButtonFunction());
	}
	else if (0 == function.compare(L"Sally")) // 1스테이지
	{
		button->AddFuncData<void(CButtonFunction::*)(), CButtonFunction*>(&CButtonFunction::Sally, &CButtonFunction());
	}
}
