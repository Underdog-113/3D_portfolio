#include "stdafx.h"
#include "StaticScene.h"

#pragma region Prototype Headers
#include "EmptyObject.h"
#include "ImageObject.h"

#include "DebugCollider.h"
#include "Camera.h"

#include "SkyBox.h"

#include "Button.h"
#include "Slider.h"
#include "ScrollViewObject.h"
#include "Canvas.h"

#include "MO_Scout.h"
#include "MO_Ninza.h"
#include "MO_Axe.h"
#include "MO_Robot.h"
#include "MO_Spider.h"
#include "MO_Sickle.h"
#include "MO_Lancer.h"
#include "MB_Ganesha.h"
#include "MB_Bronya.h"
#include "Monster.h"

#pragma endregion

#pragma region Static setting
 
#pragma endregion



CStaticScene::CStaticScene()
{
}


CStaticScene::~CStaticScene()
{
}

CClientScene* CStaticScene::Create(void)
{
	CStaticScene* pInstance = new CStaticScene;
	pInstance->Awake((_int)ELayerID::NumOfLayerID);

	return pInstance;
}

void CStaticScene::Free(void)
{
	OnDestroy();
	delete this;
}

void CStaticScene::Awake(_int numOfLayers)
{
	__super::Awake(numOfLayers);
}

void CStaticScene::Start(void)
{
	InitSettings();
}

void CStaticScene::FixedUpdate(void)
{
	__super::FixedUpdate();
	
}

void CStaticScene::Update(void)
{
	__super::Update();
	
}

void CStaticScene::LateUpdate(void)
{
	__super::LateUpdate();
	
}

void CStaticScene::OnDestroy(void)
{
	__super::OnDestroy();
}

void CStaticScene::OnEnable(void)
{
	__super::OnEnable();
	
}

void CStaticScene::OnDisable(void)
{
	__super::OnDisable();
	
}

void CStaticScene::InitSettings(void)
{
	Engine::CCollisionManager::GetInstance()->InitCollisionMap();
}

void CStaticScene::InitPrototypes(void)
{
	SP(Engine::CEmptyObject) spEmptyObjectPrototype(Engine::CEmptyObject::Create(true, this));
	GetObjectFactory()->AddPrototype(spEmptyObjectPrototype);

	SP(Engine::CCamera) spCameraPrototype(Engine::CCamera::Create(true, this));
	GetObjectFactory()->AddPrototype(spCameraPrototype);

	SP(Engine::CSkyBox) spSkyBox(Engine::CSkyBox::Create(true, this));
	GetObjectFactory()->AddPrototype(spSkyBox);

	InitUiPrototypes();
	InitMonsterPrototypes();
	
}

void CStaticScene::InitUiPrototypes(void)
{
	SP(Engine::CCanvas) spCanvasViewObject(Engine::CCanvas::Create(true, this));
	GetObjectFactory()->AddPrototype(spCanvasViewObject);

	SP(Engine::CImageObject) spImageObject(Engine::CImageObject::Create(true, this));
	GetObjectFactory()->AddPrototype(spImageObject);

	SP(CButton) spButtonObject(CButton::Create(true, this));
	GetObjectFactory()->AddPrototype(spButtonObject);

	SP(Engine::CSlider) spSliderObject(Engine::CSlider::Create(true, this));
	GetObjectFactory()->AddPrototype(spSliderObject);

	SP(CScrollViewObject) spScrollViewObject(CScrollViewObject::Create(true, this));
	GetObjectFactory()->AddPrototype(spScrollViewObject);

	SP(Engine::CDebugCollider) spDebugCOllider(Engine::CDebugCollider::Create(true, this));
	GetObjectFactory()->AddPrototype(spDebugCOllider);
}

void CStaticScene::InitMonsterPrototypes(void)
{
	SP(CMonster) spMO_Spider(CMO_Spider::Create(true, this));
	GetObjectFactory()->AddPrototype(spMO_Spider);

	SP(CMonster) spMO_Ninza(CMO_Ninza::Create(true, this));
	GetObjectFactory()->AddPrototype(spMO_Ninza);

	SP(CMonster) spMO_Axe(CMO_Axe::Create(true, this));
	GetObjectFactory()->AddPrototype(spMO_Axe);

	SP(CMonster) spMO_Scout(CMO_Scout::Create(true, this));
	GetObjectFactory()->AddPrototype(spMO_Scout);

	SP(CMonster) spMO_Robot(CMO_Robot::Create(true, this));
	GetObjectFactory()->AddPrototype(spMO_Robot);

	SP(CMonster) spMO_Lancer(CMO_Lancer::Create(true, this));
	GetObjectFactory()->AddPrototype(spMO_Lancer);

	SP(CMonster) spMO_Sickle(CMO_Sickle::Create(true, this));
	GetObjectFactory()->AddPrototype(spMO_Sickle);

	SP(CMonster) spMB_Ganesha(CMB_Ganesha::Create(true, this));
	GetObjectFactory()->AddPrototype(spMB_Ganesha);

	SP(CMonster) spMB_Bronya(CMB_Bronya::Create(true, this));
	GetObjectFactory()->AddPrototype(spMB_Bronya);
}
