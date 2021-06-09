#include "stdafx.h"
#include "DataLoad.h"
#include "DataStore.h"

#include "ImageObject.h"
#include "Button.h"
#include "Slider.h"
#include "ButtonFunction.h"
#include "ScrollViewObject.h"
#include "Canvas.h"


CDataLoad::CDataLoad()
{
	m_loadDeleGate += std::bind(&CDataLoad::ImageLoad, &CDataLoad());
	m_loadDeleGate += std::bind(&CDataLoad::SliderLoad, &CDataLoad());
	m_loadDeleGate += std::bind(&CDataLoad::ButtonLoad, &CDataLoad());
	m_loadDeleGate += std::bind(&CDataLoad::ScrollViewLoad, &CDataLoad());
	m_loadDeleGate += std::bind(&CDataLoad::ToolLoad, &CDataLoad());
}

CDataLoad::~CDataLoad()
{

}

void CDataLoad::Load(Engine::CScene * pScene)
{
	m_loadDeleGate(pScene);
}

void CDataLoad::ImageLoad(Engine::CScene* pScene)
{
	Engine::CDataStore* dataStore = pScene->GetDataStore(); //Engine::GET_CUR_SCENE->GetDataStore();

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
			std::dynamic_pointer_cast<Engine::CImageObject>(pScene->GetObjectFactory()->AddClone(L"ImageObject", true, (_int)ELayerID::UI, name));

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
		dataStore->GetValue(false, dataID, objectKey, key + L"message", message);
		dataStore->GetValue(false, dataID, objectKey, key + L"fontPosition", fontPosition);
		dataStore->GetValue(false, dataID, objectKey, key + L"fontSize", fontSize);
		//dataStore->GetValue(false, dataID, objectKey, L"imageObejct" + std::to_wstring(i) + L"color", color);

		image->AddComponent<Engine::CTextC>()->AddFontData(name, message, fontPosition, _float2(0,0), fontSize, DT_VCENTER + DT_CENTER + DT_NOCLIP, color, true);
	}
}

void CDataLoad::SliderLoad(Engine::CScene* pScene)
{
}

void CDataLoad::ButtonLoad(Engine::CScene* pScene)
{
}

void CDataLoad::ScrollViewLoad(Engine::CScene* pScene)
{
}

void CDataLoad::ToolLoad(Engine::CScene* pScene)
{
}
