#include "stdafx.h"
#include "StaticScene.h"

#pragma region MapPrototypes
#include "SkyBox.h"
#include "DecoObject.h"
#include "MapObject.h"
#include "MapObject2D.h"
#include "PhaseChanger.h"
#pragma endregion

#pragma region Prototype Headers
#include "EmptyObject.h"
#include "ImageObject.h"
#include "TextObject.h"

#include "DebugCollider.h"
#include "Camera.h"


#include "Button.h"
#include "Slider.h"
#include "ScrollViewObject.h"
#include "Canvas.h"
#include "ItemButton.h"

#include "AttackBall.h"
#include "AttackBox.h"

#include "MO_Dummy.h"
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

#include "MeshEffect_Client.h"
#include "AttackRange_Circle.h"

#include "SoftEffect.h"
#include "MonsterHitEffect.h"
#include "MonsterSpawnBeam.h"
#include "MonsterSpawnEff.h"

// Kiana
#include "Kiana_Trail.h"
#include "Kiana_Ult_Trail.h"
#include "Kiana_Ult_Eff.h"
#include "Kiana_Ult_Plane.h"
#include "Kiana_Ult_Shield.h"
#include "Kiana_Ult_Ring.h"

// Theresa
#include "Theresa_Trail.h"
#include "Theresa_Ult_Trail.h"
#include "Theresa_Ult_Eff.h"
#include "Theresa_Ult_Charge.h"
#include "Theresa_Ult_Smoke.h"
#include "Theresa_Ult_Fire.h"
#include "Theresa_Ult_Boom.h"
#include "Theresa_Ult_Crack.h"
#include "TheresaCharge_Att.h"
#include "MoveUpSmoke.h"

// Sakura
#include "Sakura_Charge_Att.h"

#pragma endregion

#pragma region Static setting
 
#pragma endregion

#include "Include_Valkyrie.h"

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

	SP(Engine::CDebugCollider) spDebugCOllider(Engine::CDebugCollider::Create(true, this));
	GetObjectFactory()->AddPrototype(spDebugCOllider);
	
	SP(CAttackBall) spAttackBall(CAttackBall::Create(true, this));
	GetObjectFactory()->AddPrototype(spAttackBall);

	SP(CAttackBox) spAttackBox(CAttackBox::Create(true, this));
	GetObjectFactory()->AddPrototype(spAttackBox);
	
	InitMapPrototypes();
	InitUiPrototypes();
	InitMonsterPrototypes();
	InitValkyriePrototypes();
	InitEffectPrototypes();
}

void CStaticScene::InitMapPrototypes(void)
{
	SP(Engine::CSkyBox) spSkyBox(Engine::CSkyBox::Create(true, this));
	GetObjectFactory()->AddPrototype(spSkyBox);

	SP(CDecoObject) spDecoObject(CDecoObject::Create(true, this));
	GetObjectFactory()->AddPrototype(spDecoObject);

	SP(CMapObject) spMapObject(CMapObject::Create(true, this));
	GetObjectFactory()->AddPrototype(spMapObject);

	SP(CMapObject2D) spMapObject2D(CMapObject2D::Create(true, this));
	GetObjectFactory()->AddPrototype(spMapObject2D);

	SP(CPhaseChanger) spPhaseChanger(CPhaseChanger::Create(true, this));
	GetObjectFactory()->AddPrototype(spPhaseChanger);
}

void CStaticScene::InitUiPrototypes(void)
{
	SP(Engine::CTextObject) spTextObject(Engine::CTextObject::Create(true, this));
	GetObjectFactory()->AddPrototype(spTextObject);

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

	SP(CItemButton) spItemButtonObject(CItemButton::Create(true, this));
	GetObjectFactory()->AddPrototype(spItemButtonObject);
}

void CStaticScene::InitMonsterPrototypes(void)
{
	SP(CMonster) spMO_Dummy(CMO_Dummy::Create(true, this));
	GetObjectFactory()->AddPrototype(spMO_Dummy);

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

void CStaticScene::InitValkyriePrototypes(void)
{
	SP(CKiana) spKianaPrototype(CKiana::Create(true, this));
	ADD_PROTOTYPE(spKianaPrototype);

	SP(CKiana_CatPaw_Atk01) spPaw01(CKiana_CatPaw_Atk01::Create(true, this));
	ADD_PROTOTYPE(spPaw01);

	SP(CKiana_CatPaw_Atk02) spPaw02(CKiana_CatPaw_Atk02::Create(true, this));
	ADD_PROTOTYPE(spPaw02);

	SP(CKiana_CatPaw_Atk03) spPaw03(CKiana_CatPaw_Atk03::Create(true, this));
	ADD_PROTOTYPE(spPaw03);

	SP(CKiana_CatPaw_Atk04) spPaw04(CKiana_CatPaw_Atk04::Create(true, this));
	ADD_PROTOTYPE(spPaw04);

	SP(CKiana_CatPaw_Atk05) spPaw05(CKiana_CatPaw_Atk05::Create(true, this));
	ADD_PROTOTYPE(spPaw05);

	SP(CKiana_CatPaw_Ring_Atk01) spPawRing01(CKiana_CatPaw_Ring_Atk01::Create(true, this));
	ADD_PROTOTYPE(spPawRing01);

	SP(CKiana_CatPaw_Ring_Atk02) spPawRing02(CKiana_CatPaw_Ring_Atk02::Create(true, this));
	ADD_PROTOTYPE(spPawRing02);

	SP(CKiana_Pistol) spPistol(CKiana_Pistol::Create(true, this));
	ADD_PROTOTYPE(spPistol);


	SP(CTheresa) spTheresaPrototype(CTheresa::Create(true, this));
	ADD_PROTOTYPE(spTheresaPrototype);



	SP(CSakura) spSakuraPrototype(CSakura::Create(true, this));
	ADD_PROTOTYPE(spSakuraPrototype);
}

void CStaticScene::InitEffectPrototypes(void)
{
	// Attack Trail
	SP(CMeshEffect_Client) spKiana_Trail(CKiana_Trail::Create(true, this));
	GetObjectFactory()->AddPrototype(spKiana_Trail);

	SP(CMeshEffect_Client) spKiana_Ult_Trail(CKiana_Ult_Trail::Create(true, this));
	GetObjectFactory()->AddPrototype(spKiana_Ult_Trail);

	// Attack Range
	SP(CMeshEffect_Client) spAttack_Range_Circle(CAttackRange_Circle::Create(true, this));
	GetObjectFactory()->AddPrototype(spAttack_Range_Circle);

	// Kiana Effect
	SP(CMeshEffect_Client) spKiana_Ult_Eff(CKiana_Ult_Eff::Create(true, this));
	GetObjectFactory()->AddPrototype(spKiana_Ult_Eff);

	SP(CMeshEffect_Client) spKiana_Ult_Eff_Plane(CKiana_Ult_Plane::Create(true, this));
	GetObjectFactory()->AddPrototype(spKiana_Ult_Eff_Plane);

	SP(CMeshEffect_Client) spKiana_Ult_Eff_Ring(CKiana_Ult_Ring::Create(true, this));
	GetObjectFactory()->AddPrototype(spKiana_Ult_Eff_Ring);

	SP(CMeshEffect_Client) spKiana_Ult_Eff_Shield(CKiana_Ult_Shield::Create(true, this));
	GetObjectFactory()->AddPrototype(spKiana_Ult_Eff_Shield);

	SP(CMeshEffect_Client) spTheresa_Ult_Eff(CTheresa_Ult_Eff::Create(true, this));
	GetObjectFactory()->AddPrototype(spTheresa_Ult_Eff);

	// Theresa Effect
	SP(CMeshEffect_Client) spTheresa_Trail(CTheresa_Trail::Create(true, this));
	GetObjectFactory()->AddPrototype(spTheresa_Trail);

	SP(CMeshEffect_Client) spTheresa_Ult_Trail(CTheresa_Ult_Trail::Create(true, this));
	GetObjectFactory()->AddPrototype(spTheresa_Ult_Trail);

	SP(CMeshEffect_Client) spTheresa_Ult_Eff_Charge(CTheresa_Ult_Charge::Create(true, this));
	GetObjectFactory()->AddPrototype(spTheresa_Ult_Eff_Charge);

	SP(CMeshEffect_Client) spTheresa_Ult_Eff_Smoke(CTheresa_Ult_Smoke::Create(true, this));
	GetObjectFactory()->AddPrototype(spTheresa_Ult_Eff_Smoke);

	SP(CMeshEffect_Client) spTheresa_Ult_Eff_Fire(CTheresa_Ult_Fire::Create(true, this));
	GetObjectFactory()->AddPrototype(spTheresa_Ult_Eff_Fire);

	SP(CMeshEffect_Client) spTheresa_Ult_Eff_Boom(CTheresa_Ult_Boom::Create(true, this));
	GetObjectFactory()->AddPrototype(spTheresa_Ult_Eff_Boom);

	SP(CMeshEffect_Client) spTheresa_Ult_Eff_Crack(CTheresa_Ult_Crack::Create(true, this));
	GetObjectFactory()->AddPrototype(spTheresa_Ult_Eff_Crack);

	SP(CMeshEffect_Client) spTheresa_Ult_Eff_ChargeAtt(CTheresaCharge_Att::Create(true, this));
	GetObjectFactory()->AddPrototype(spTheresa_Ult_Eff_ChargeAtt);

	SP(CMeshEffect_Client) spTheresa_Ult_Eff_MoveUpSmoke(CMoveUpSmoke::Create(true, this));
	GetObjectFactory()->AddPrototype(spTheresa_Ult_Eff_MoveUpSmoke);

	// Sakura

	SP(CMeshEffect_Client) spSakura_Charge_Att(CSakura_Charge_Att::Create(true, this));
	GetObjectFactory()->AddPrototype(spSakura_Charge_Att);

	// Monster Spawn

	SP(CMeshEffect_Client) spMonster_Spawn_Beam(CMonsterSpawnBeam::Create(true, this));
	GetObjectFactory()->AddPrototype(spMonster_Spawn_Beam);

	SP(CMeshEffect_Client) spMonster_Spawn_Eff(CMonsterSpawnEff::Create(true, this));
	GetObjectFactory()->AddPrototype(spMonster_Spawn_Eff);

	// Hit
	SP(CSoftEffect) spHitEffect(CMonsterHitEffect::Create(true, this));
	GetObjectFactory()->AddPrototype(spHitEffect);
}
