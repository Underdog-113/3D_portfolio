#include "stdafx.h"
#include "StaticScene.h"

#pragma region MapPrototypes
#include "SkyBox.h"
#include "DecoObject.h"
#include "MapObject.h"
#include "MapObject2D.h"
#include "PhaseChanger.h"
#include "Portal.h"
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
#include "Bronya_Weapon.h"
#include "Monster.h"

#include "MeshEffect_Client.h"
#include "AttackRange_Circle.h"
#include "SparkEffect.h"

// Scout
#include "Scout_Att_Range.h"
#include "Scout_Att_Range_Hold.h"
#include "Scout_Laser.h"
#include "ScoutBall.h"
#include "ScoutMeteor.h"
#include "ScoutCircleRange.h"

#include "SoftEffect.h"
#include "MonsterHitEffect.h"
#include "MonsterSpawnBeam.h"
#include "MonsterSpawnEff.h"
#include "MonsterAttackSign.h"
#include "Sickle_Trail.h"
#include "SpiderExplosion.h"

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

// Robot
#include "RobotHookEff.h"
#include "Robot_Plane.h"
#include "Robot_Impact.h"
#include "Robot_Impact_Smoke.h"

// Lancer
#include "Lancer_Impact.h"
#include "Lancer_OutSideEff.h"
#include "Lancer_Att_Range.h"

//Ganesha
#include "Ganesha_LaserEff.h"
#include "Ganesha_Charge_Eff.h"
#include "Ganesha_Dome.h"
#include "Ganesha_Dome_Impact.h"
#include "Ganesha_SmokeEff.h"
#include "Ganesha_UpperEff.h"

//Bronya
#include "Bronya_Cannon_Charge.h"
#include "Bronya_Shot_Smoke.h"
#include "Bronya_Impact.h"
#include "Bronya_Impact_Ring.h"
#include "Bronya_Impact_TripleRing.h"
#include "Bronya_FlashBang.h"
#include "BronyaFlashBang_AS.h"
#include "Bronya_RandomSmoke.h"

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

	SP(CPortal) spPortal(CPortal::Create(true, this));
	GetObjectFactory()->AddPrototype(spPortal);
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

	SP(CBronya_Weapon) spBronyaWeapon(CBronya_Weapon::Create(true, this));
	ADD_PROTOTYPE(spBronyaWeapon);
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

	SP(CTheresa_CrossBloodyHug) spCrossBloodyHugPrototype(CTheresa_CrossBloodyHug::Create(true, this));
	ADD_PROTOTYPE(spCrossBloodyHugPrototype);

	SP(CTheresa_CrossBlade) spCrossBladePrototype(CTheresa_CrossBlade::Create(true, this));
	ADD_PROTOTYPE(spCrossBladePrototype);

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

	SP(CMonsterSpawnBeam) spMonster_Spawn_Beam(CMonsterSpawnBeam::Create(true, this));
	spMonster_Spawn_Beam->GetMesh()->SetMeshData(L"SpawnBeam");
	spMonster_Spawn_Beam->GetComponent<Engine::CGraphicsC>()->SetRenderID((_int)Engine::ERenderID::AlphaBlend);
	spMonster_Spawn_Beam->GetComponent<Engine::CTextureC>()->AddTexture(L"Portal_beam_4");
	spMonster_Spawn_Beam->GetComponent<Engine::CTextureC>()->AddTexture(L"Portal_beam_4");
	spMonster_Spawn_Beam->GetComponent<Engine::CTextureC>()->AddTexture(L"Portal_beam_4");
	spMonster_Spawn_Beam->GetComponent<Engine::CShaderC>()->AddShader((_int)EShaderID::AlphaMaskShader);
	spMonster_Spawn_Beam->GetCollision()->
		AddCollider(Engine::CRayCollider::Create((_int)ECollisionID::FloorRay, _float3(0, 0, 0), _float3(0, 0, 1), 2.5f));
	GetObjectFactory()->AddPrototype(spMonster_Spawn_Beam);

	SP(CMeshEffect_Client) spMonster_Spawn_Eff(CMonsterSpawnEff::Create(true, this));
	GetObjectFactory()->AddPrototype(spMonster_Spawn_Eff);

	// Hit
	SP(CSoftEffect) spHitEffect(CMonsterHitEffect::Create(true, this));
	GetObjectFactory()->AddPrototype(spHitEffect);

	// Spider
	SP(CSoftEffect) spSpiderExplosionEffect(CSpiderExplosion::Create(true, this));
	spSpiderExplosionEffect->GetComponent<Engine::CTextureC>()->AddTexture(L"Exp");
	spSpiderExplosionEffect->GetComponent<Engine::CTextureC>()->AddTexture(L"Exp");
	spSpiderExplosionEffect->GetComponent<Engine::CShaderC>()->AddShader((_int)EShaderID::SoftEffectShader);
	GetObjectFactory()->AddPrototype(spSpiderExplosionEffect);

	// Monster AttackSign
	SP(CSoftEffect) spMonsterAttack_Sign(CMonsterAttackSign::Create(true, this));
	spMonsterAttack_Sign->GetComponent<Engine::CGraphicsC>();
	spMonsterAttack_Sign->GetComponent<Engine::CTextureC>()->AddTexture(L"RedFlare");
	spMonsterAttack_Sign->GetComponent<Engine::CTextureC>()->AddTexture(L"RedFlare");
	spMonsterAttack_Sign->GetComponent<Engine::CShaderC>()->AddShader((_int)EShaderID::SoftEffectShader);
	GetObjectFactory()->AddPrototype(spMonsterAttack_Sign);

	// Sickle
	SP(CMeshEffect_Client) spSickleTrail(CSickle_Trail::Create(true, this));
	GetObjectFactory()->AddPrototype(spSickleTrail);

	// Scout
	SP(CMeshEffect_Client) spScoutAttRange(CScout_Att_Range::Create(true, this));
	GetObjectFactory()->AddPrototype(spScoutAttRange);
	
	SP(CMeshEffect_Client) spScoutAttRange_Hold(CScout_Att_Range_Hold::Create(true, this));
	GetObjectFactory()->AddPrototype(spScoutAttRange_Hold);

	SP(CMeshEffect_Client) spScoutLaser(CScout_Laser::Create(true, this));
	GetObjectFactory()->AddPrototype(spScoutLaser);

	SP(CMeshEffect_Client) spScoutBall(CScoutBall::Create(true, this));
	spScoutBall->GetComponent<Engine::CMeshC>()->SetMeshData(L"Scout_Ball");
	spScoutBall->GetComponent<Engine::CGraphicsC>()->SetRenderID((_int)Engine::ERenderID::AlphaBlend);
	spScoutBall->GetComponent<Engine::CTextureC>()->AddTexture(L"BallColor");
	spScoutBall->GetComponent<Engine::CTextureC>()->AddTexture(L"BallColor");
	spScoutBall->GetComponent<Engine::CShaderC>()->AddShader((_int)EShaderID::AlphaMaskShader);
	GetObjectFactory()->AddPrototype(spScoutBall);

	SP(CScoutMeteor) spScoutMeteor(CScoutMeteor::Create(true, this));
	spScoutMeteor->GetComponent<Engine::CGraphicsC>();
	spScoutMeteor->GetComponent<Engine::CTextureC>()->AddTexture(L"BallColor");
	spScoutMeteor->GetComponent<Engine::CTextureC>()->AddTexture(L"Scout_Meteor");
	spScoutMeteor->GetComponent<Engine::CShaderC>()->AddShader((_int)EShaderID::SoftEffectShader);
	spScoutMeteor->GetCollision()->
		AddCollider(Engine::CRayCollider::Create((_int)ECollisionID::FloorRay, _float3(0, 0, 0), _float3(0, -1, 0), 0.2f));
	GetObjectFactory()->AddPrototype(spScoutMeteor);

	SP(CSoftEffect) spSparkEffect(CSparkEffect::Create(true, this));
	spSparkEffect->GetComponent<Engine::CGraphicsC>();
	spSparkEffect->GetComponent<Engine::CTextureC>()->AddTexture(L"Spark_v2");
	spSparkEffect->GetComponent<Engine::CTextureC>()->AddTexture(L"Spark_v2");
	spSparkEffect->GetComponent<Engine::CShaderC>()->AddShader((_int)EShaderID::SoftEffectShader);	
	GetObjectFactory()->AddPrototype(spSparkEffect);

	SP(CMeshEffect_Client) spScoutCircleRange(CScoutCircleRange::Create(true, this));
	spScoutCircleRange->GetComponent<Engine::CMeshC>()->SetMeshData(L"AttackRange_Circle");
	spScoutCircleRange->GetComponent<Engine::CMeshC>()->SetIsEffectMesh(true);
	spScoutCircleRange->GetComponent<Engine::CGraphicsC>()->SetRenderID((_int)Engine::ERenderID::AlphaBlend);
	spScoutCircleRange->GetComponent<Engine::CTextureC>()->AddTexture(L"BonusShield_3");
	spScoutCircleRange->GetComponent<Engine::CTextureC>()->AddTexture(L"Sign");
	spScoutCircleRange->GetComponent<Engine::CShaderC>()->AddShader((_int)EShaderID::AlphaMaskShader);
	GetObjectFactory()->AddPrototype(spScoutCircleRange);

	// Robot
	SP(CSoftEffect) spRobotHookEffect(CRobotHookEff::Create(true, this));
	spRobotHookEffect->GetComponent<Engine::CGraphicsC>();
	spRobotHookEffect->GetComponent<Engine::CTextureC>()->AddTexture(L"RobotHook");
	spRobotHookEffect->GetComponent<Engine::CTextureC>()->AddTexture(L"RobotHook");
	spRobotHookEffect->GetComponent<Engine::CShaderC>()->AddShader((_int)EShaderID::SoftEffectShader);
	GetObjectFactory()->AddPrototype(spRobotHookEffect);

	SP(CMeshEffect_Client) spRobotPlane(CRobot_Plane::Create(true, this));
	spRobotPlane->GetComponent<Engine::CMeshC>()->SetMeshData(L"Robot_Plane");
	spRobotPlane->GetComponent<Engine::CMeshC>()->SetIsEffectMesh(true);
	spRobotPlane->GetComponent<Engine::CGraphicsC>()->SetRenderID((_int)Engine::ERenderID::AlphaBlend);
	spRobotPlane->GetComponent<Engine::CTextureC>()->AddTexture(L"SkyColor");
	spRobotPlane->GetComponent<Engine::CTextureC>()->AddTexture(L"SkyColor");
	spRobotPlane->GetComponent<Engine::CShaderC>()->AddShader((_int)EShaderID::AlphaMaskShader);
	GetObjectFactory()->AddPrototype(spRobotPlane);

	SP(CSoftEffect) spRobotImpact(CRobot_Impact::Create(true, this));
	spRobotImpact->GetComponent<Engine::CGraphicsC>();
	spRobotImpact->GetComponent<Engine::CTextureC>()->AddTexture(L"ImpactColor");
	spRobotImpact->GetComponent<Engine::CTextureC>()->AddTexture(L"Effect_Wave07");
	spRobotImpact->GetComponent<Engine::CShaderC>()->AddShader((_int)EShaderID::SoftEffectShader);
	GetObjectFactory()->AddPrototype(spRobotImpact);

	SP(CMeshEffect_Client) spRobotImpactSmoke(CRobot_Impact_Smoke::Create(true, this));
	spRobotImpactSmoke->GetComponent<Engine::CMeshC>()->SetMeshData(L"Robot_Impact");
	spRobotImpactSmoke->GetComponent<Engine::CMeshC>()->SetIsEffectMesh(true);
	spRobotImpactSmoke->GetComponent<Engine::CGraphicsC>()->SetRenderID((_int)Engine::ERenderID::AlphaBlend);
	spRobotImpactSmoke->GetComponent<Engine::CTextureC>()->AddTexture(L"Gray");
	spRobotImpactSmoke->GetComponent<Engine::CTextureC>()->AddTexture(L"Austerity");
	spRobotImpactSmoke->GetComponent<Engine::CShaderC>()->AddShader((_int)EShaderID::AlphaMaskShader);
	GetObjectFactory()->AddPrototype(spRobotImpactSmoke);

	// Lancer
	SP(CMeshEffect_Client) spLancer_Att_Range(CLancer_Att_Range::Create(true, this));
	spLancer_Att_Range->GetComponent<Engine::CMeshC>()->SetMeshData(L"Lancer_Att_Range");
	spLancer_Att_Range->GetComponent<Engine::CMeshC>()->SetIsEffectMesh(true);
	spLancer_Att_Range->GetComponent<Engine::CGraphicsC>()->SetRenderID((_int)Engine::ERenderID::AlphaBlend);
	spLancer_Att_Range->GetComponent<Engine::CTextureC>()->AddTexture(L"Sign");
	spLancer_Att_Range->GetComponent<Engine::CTextureC>()->AddTexture(L"Sign");
	spLancer_Att_Range->GetComponent<Engine::CShaderC>()->AddShader((_int)EShaderID::AlphaMaskShader);
	GetObjectFactory()->AddPrototype(spLancer_Att_Range);

	SP(CMeshEffect_Client) spLancer_OutSideEff(CLancer_OutSideEff::Create(true, this));
	spLancer_OutSideEff->GetComponent<Engine::CMeshC>()->SetMeshData(L"Lancer_OutSideEff");
	spLancer_OutSideEff->GetComponent<Engine::CMeshC>()->SetIsEffectMesh(true);
	spLancer_OutSideEff->GetComponent<Engine::CGraphicsC>()->SetRenderID((_int)Engine::ERenderID::AlphaBlend);
	spLancer_OutSideEff->GetComponent<Engine::CTextureC>()->AddTexture(L"Lancer_Eff_Color");
	spLancer_OutSideEff->GetComponent<Engine::CTextureC>()->AddTexture(L"Soft");
	spLancer_OutSideEff->GetComponent<Engine::CShaderC>()->AddShader((_int)EShaderID::AlphaMaskShader);
	GetObjectFactory()->AddPrototype(spLancer_OutSideEff);

	SP(CSoftEffect) spLancer_Impact(CLancer_Impact::Create(true, this));
	spLancer_Impact->GetComponent<Engine::CGraphicsC>();
	spLancer_Impact->GetComponent<Engine::CTextureC>()->AddTexture(L"puncture");
	spLancer_Impact->GetComponent<Engine::CTextureC>()->AddTexture(L"puncture");
	spLancer_Impact->GetComponent<Engine::CShaderC>()->AddShader((_int)EShaderID::SoftEffectShader);
	GetObjectFactory()->AddPrototype(spLancer_Impact);


	// Ganesha
	SP(CMeshEffect_Client) spGaneshaLaserEffect(CGanesha_LaserEff::Create(true, this));
	spGaneshaLaserEffect->GetComponent<Engine::CMeshC>()->SetMeshData(L"Ganesha_Laser");
	spGaneshaLaserEffect->GetComponent<Engine::CMeshC>()->SetIsEffectMesh(true);
	spGaneshaLaserEffect->GetComponent<Engine::CGraphicsC>()->SetRenderID((_int)Engine::ERenderID::AlphaBlend);
	spGaneshaLaserEffect->GetComponent<Engine::CTextureC>()->AddTexture(L"LaserColor2");
	spGaneshaLaserEffect->GetComponent<Engine::CTextureC>()->AddTexture(L"LaserColor2");
	spGaneshaLaserEffect->GetComponent<Engine::CShaderC>()->AddShader((_int)EShaderID::AlphaMaskShader);
	GetObjectFactory()->AddPrototype(spGaneshaLaserEffect);

	SP(CMeshEffect_Client) spGaneshaChargeEffect(CGanesha_Charge_Eff::Create(true, this));
	spGaneshaChargeEffect->GetComponent<Engine::CMeshC>()->SetMeshData(L"Ganesha_Charge");
	spGaneshaChargeEffect->GetComponent<Engine::CMeshC>()->SetIsEffectMesh(true);
	spGaneshaChargeEffect->GetComponent<Engine::CGraphicsC>()->SetRenderID((_int)Engine::ERenderID::AlphaBlend);
	spGaneshaChargeEffect->GetComponent<Engine::CTextureC>()->AddTexture(L"Lancer_Eff_Color");
	spGaneshaChargeEffect->GetComponent<Engine::CTextureC>()->AddTexture(L"Ability_aura");
	spGaneshaChargeEffect->GetComponent<Engine::CShaderC>()->AddShader((_int)EShaderID::AlphaMaskShader);
	GetObjectFactory()->AddPrototype(spGaneshaChargeEffect);

	SP(CMeshEffect_Client) spGaneshaDomeEff(CGanesha_Dome::Create(true, this));
	spGaneshaDomeEff->GetComponent<Engine::CMeshC>()->SetMeshData(L"Ganesha_Dome");
	spGaneshaDomeEff->GetComponent<Engine::CMeshC>()->SetIsEffectMesh(true);
	spGaneshaDomeEff->GetComponent<Engine::CGraphicsC>()->SetRenderID((_int)Engine::ERenderID::AlphaBlend);
	spGaneshaDomeEff->GetComponent<Engine::CTextureC>()->AddTexture(L"Dome_Color");
	spGaneshaDomeEff->GetComponent<Engine::CTextureC>()->AddTexture(L"Dome_Color");
	spGaneshaDomeEff->GetComponent<Engine::CShaderC>()->AddShader((_int)EShaderID::AlphaMaskShader);
	GetObjectFactory()->AddPrototype(spGaneshaDomeEff);

	SP(CMeshEffect_Client) spGaneshaDomeImpact(CGanesha_Dome_Impact::Create(true, this));
	spGaneshaDomeImpact->GetComponent<Engine::CMeshC>()->SetMeshData(L"Ganesha_Charge");
	spGaneshaDomeImpact->GetComponent<Engine::CMeshC>()->SetIsEffectMesh(true);
	spGaneshaDomeImpact->GetComponent<Engine::CGraphicsC>()->SetRenderID((_int)Engine::ERenderID::AlphaBlend);
	spGaneshaDomeImpact->GetComponent<Engine::CTextureC>()->AddTexture(L"effect_Ring07");
	spGaneshaDomeImpact->GetComponent<Engine::CTextureC>()->AddTexture(L"effect_Ring07");
	spGaneshaDomeImpact->GetComponent<Engine::CShaderC>()->AddShader((_int)EShaderID::AlphaMaskShader);
	GetObjectFactory()->AddPrototype(spGaneshaDomeImpact);

	SP(CSoftEffect) spGaneshaSmoke(CGanesha_SmokeEff::Create(true, this));
	spGaneshaSmoke->GetComponent<Engine::CGraphicsC>();
	spGaneshaSmoke->GetComponent<Engine::CTextureC>()->AddTexture(L"hit_explosion5_new");
	spGaneshaSmoke->GetComponent<Engine::CTextureC>()->AddTexture(L"hit_explosion5_new");
	spGaneshaSmoke->GetComponent<Engine::CShaderC>()->AddShader((_int)EShaderID::SoftEffectShader);
	GetObjectFactory()->AddPrototype(spGaneshaSmoke);


	// 텍스처 추가해야함
	/*SP(CSoftEffect) spGaneshaUpper(CGanesha_UpperEff::Create(true, this));
	spGaneshaUpper->GetComponent<Engine::CGraphicsC>();
	spGaneshaUpper->GetComponent<Engine::CTextureC>()->AddTexture(L"hit_explosion5_new");
	spGaneshaUpper->GetComponent<Engine::CTextureC>()->AddTexture(L"hit_explosion5_new");
	spGaneshaUpper->GetComponent<Engine::CShaderC>()->AddShader((_int)EShaderID::SoftEffectShader);
	GetObjectFactory()->AddPrototype(spGaneshaUpper);*/


	SP(CMeshEffect_Client) spBronyaCharge(CBronya_Cannon_Charge::Create(true, this));
	spBronyaCharge->GetComponent<Engine::CMeshC>()->SetMeshData(L"Bronya_Plane");
	spBronyaCharge->GetComponent<Engine::CMeshC>()->SetIsEffectMesh(true);
	spBronyaCharge->GetComponent<Engine::CGraphicsC>()->SetRenderID((_int)Engine::ERenderID::AlphaBlend);
	spBronyaCharge->GetComponent<Engine::CTextureC>()->AddTexture(L"Swirl");
	spBronyaCharge->GetComponent<Engine::CTextureC>()->AddTexture(L"Swirl");
	spBronyaCharge->GetComponent<Engine::CShaderC>()->AddShader((_int)EShaderID::AlphaMaskShader);
	GetObjectFactory()->AddPrototype(spBronyaCharge);

	SP(CMeshEffect_Client) spBronyaShotSmoke(CBronya_Shot_Smoke::Create(true, this));
	spBronyaShotSmoke->GetComponent<Engine::CMeshC>()->SetMeshData(L"Bronya_Plane");
	spBronyaShotSmoke->GetComponent<Engine::CMeshC>()->SetIsEffectMesh(true);
	spBronyaShotSmoke->GetComponent<Engine::CGraphicsC>()->SetRenderID((_int)Engine::ERenderID::AlphaBlend);
	spBronyaShotSmoke->GetComponent<Engine::CTextureC>()->AddTexture(L"machineSmoke_3");
	spBronyaShotSmoke->GetComponent<Engine::CTextureC>()->AddTexture(L"machineSmoke_3");
	spBronyaShotSmoke->GetComponent<Engine::CShaderC>()->AddShader((_int)EShaderID::AlphaMaskShader);
	GetObjectFactory()->AddPrototype(spBronyaShotSmoke);


	SP(CMeshEffect_Client) spBronyaImpact(CBronya_Impact::Create(true, this));
	spBronyaImpact->GetComponent<Engine::CMeshC>()->SetMeshData(L"Bronya_Impact");
	spBronyaImpact->GetComponent<Engine::CMeshC>()->SetIsEffectMesh(true);
	spBronyaImpact->GetComponent<Engine::CGraphicsC>()->SetRenderID((_int)Engine::ERenderID::AlphaBlend);
	spBronyaImpact->GetComponent<Engine::CTextureC>()->AddTexture(L"Wave01");
	spBronyaImpact->GetComponent<Engine::CTextureC>()->AddTexture(L"Wave01");
	spBronyaImpact->GetComponent<Engine::CTextureC>()->AddTexture(L"Impact_Red");
	spBronyaImpact->GetComponent<Engine::CShaderC>()->AddShader((_int)EShaderID::DissolveShader);
	GetObjectFactory()->AddPrototype(spBronyaImpact);

	SP(CMeshEffect_Client) spBronyaImpact_Ring(CBronya_Impact_Ring::Create(true, this));
	spBronyaImpact_Ring->GetComponent<Engine::CMeshC>()->SetMeshData(L"Bronya_Impact_ring");
	spBronyaImpact_Ring->GetComponent<Engine::CMeshC>()->SetIsEffectMesh(true);
	spBronyaImpact_Ring->GetComponent<Engine::CGraphicsC>()->SetRenderID((_int)Engine::ERenderID::AlphaBlend);
	spBronyaImpact_Ring->GetComponent<Engine::CTextureC>()->AddTexture(L"Impact_Red");
	spBronyaImpact_Ring->GetComponent<Engine::CTextureC>()->AddTexture(L"Eff_Noise_08");
	spBronyaImpact_Ring->GetComponent<Engine::CTextureC>()->AddTexture(L"Impact_Red");
	spBronyaImpact_Ring->GetComponent<Engine::CShaderC>()->AddShader((_int)EShaderID::DissolveShader);
	GetObjectFactory()->AddPrototype(spBronyaImpact_Ring);

	SP(CMeshEffect_Client) spBronyaImpact_TriRing(CBronya_Impact_TripleRing::Create(true, this));
	spBronyaImpact_TriRing->GetComponent<Engine::CMeshC>()->SetMeshData(L"Bronya_Impact_TripleRing");
	spBronyaImpact_TriRing->GetComponent<Engine::CMeshC>()->SetIsEffectMesh(true);
	spBronyaImpact_TriRing->GetComponent<Engine::CGraphicsC>()->SetRenderID((_int)Engine::ERenderID::AlphaBlend);
	spBronyaImpact_TriRing->GetComponent<Engine::CTextureC>()->AddTexture(L"Impact_Red");
	spBronyaImpact_TriRing->GetComponent<Engine::CTextureC>()->AddTexture(L"Eff_Noise_08");
	spBronyaImpact_TriRing->GetComponent<Engine::CTextureC>()->AddTexture(L"Impact_Red");
	spBronyaImpact_TriRing->GetComponent<Engine::CShaderC>()->AddShader((_int)EShaderID::DissolveShader);
	GetObjectFactory()->AddPrototype(spBronyaImpact_TriRing);

	SP(CMeshEffect_Client) spBronyaFlashBang(CBronya_FlashBang::Create(true, this));
	spBronyaFlashBang->GetComponent<Engine::CMeshC>()->SetMeshData(L"Bronya_FlashBang");
	spBronyaFlashBang->GetComponent<Engine::CMeshC>()->SetIsEffectMesh(true);
	spBronyaFlashBang->GetComponent<Engine::CGraphicsC>()->SetRenderID((_int)Engine::ERenderID::AlphaBlend);
	spBronyaFlashBang->GetComponent<Engine::CTextureC>()->AddTexture(L"FlashBang");
	spBronyaFlashBang->GetComponent<Engine::CTextureC>()->AddTexture(L"FlashBang");
	spBronyaFlashBang->GetComponent<Engine::CTextureC>()->AddTexture(L"FlashBang");
	spBronyaFlashBang->GetComponent<Engine::CShaderC>()->AddShader((_int)EShaderID::AlphaMaskShader);
	GetObjectFactory()->AddPrototype(spBronyaFlashBang);

	SP(CSoftEffect) spBronyaFlashBangAS(CBronyaFlashBang_AS::Create(true, this));
	spBronyaFlashBangAS->GetComponent<Engine::CGraphicsC>();
	spBronyaFlashBangAS->GetComponent<Engine::CTextureC>()->AddTexture(L"FlashBang_Impact_1");
	spBronyaFlashBangAS->GetComponent<Engine::CTextureC>()->AddTexture(L"FlashBang_Impact");
	spBronyaFlashBangAS->GetComponent<Engine::CShaderC>()->AddShader((_int)EShaderID::SoftEffectShader);
	GetObjectFactory()->AddPrototype(spBronyaFlashBangAS);

	SP(CSoftEffect) spBronyaRandomSmoke(CBronya_RandomSmoke::Create(true, this));
	spBronyaFlashBangAS->GetComponent<Engine::CGraphicsC>();
	spBronyaRandomSmoke->GetComponent<Engine::CGraphicsC>()->SetRenderID((_int)Engine::ERenderID::AlphaBlend);
	spBronyaRandomSmoke->GetComponent<Engine::CShaderC>()->AddShader((_int)EShaderID::AlphaMaskShader);
	GetObjectFactory()->AddPrototype(spBronyaRandomSmoke);
}
