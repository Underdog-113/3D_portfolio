#include "stdafx.h"
#include "StaticScene.h"

#pragma region MapPrototypes
#include "SkyBox.h"
#include "DecoObject.h"
#include "MapObject.h"
#include "MapObject2D.h"
#include "PhaseChanger.h"
#include "Portal.h"
#include "TrapObject.h"
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
#include "BronyaBullet.h"
#include "BronyaGrenade.h"
#include "Monster.h"
#include "OJ_Box.h"

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
#include "SpiderImpact.h"
#include "SpiderExplosion_Base.h"
// Kiana
#include "Kiana_Trail.h"
#include "Kiana_Ult_Trail.h"
#include "Kiana_Ult_Eff.h"
#include "Kiana_Ult_Plane.h"
#include "Kiana_Ult_Shield.h"
#include "Kiana_Ult_Ring.h"
#include "KianaBranchSign.h"
#include "Kiana_WSkill_Circle.h"
#include "Kiana_WSkill_Shoot.h"

// Theresa
#include "Theresa_Trail.h"
#include "Theresa_Ult_Trail.h"
#include "Theresa_Ult_Eff.h"
#include "Theresa_Ult_Charge.h"
#include "Theresa_Ult_Smoke.h"
#include "Theresa_Ult_Fire.h"
#include "Theresa_Ult_Explosion.h"
#include "Theresa_Ult_Crack.h"
#include "TheresaCharge_Att.h"
#include "MoveUpSmoke.h"

// Sakura
#include "Sakura_Charge_Att.h"
#include "Sakura_Trail.h"
#include "Sakura_WSkill_Impact.h"
#include "Sakura_WSkill_Smoke.h"
#include "Sakura_WSkill_Start.h"
#include "Sakura_WSkill_Twist.h"
#include "Sakura_WSkill_Twist_Wind.h"
#include "Sakura_DashShade.h"
#include "Sakura_Mark.h"
#include "Sakura_DamageMark.h"
#include "Sakura_EvadeSkill_Loop.h"
#include "Sakura_EvadeSkill_Start.h"

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
#include "Ganesha_Impact_Eff.h"
#include "Ganesha_SmokeEff.h"
#include "Ganesha_UpperEff.h"
#include "Ganesha_Cinema_Circle.h"
#include "Ganesha_Cinema_Dome.h"
#include "Ganesha_Cinema_Lightning.h"

//Bronya
#include "Bronya_Cannon_Charge.h"
#include "Bronya_Shot_Smoke.h"
#include "Bronya_Impact.h"
#include "Bronya_Impact_Ring.h"
#include "Bronya_Impact_TripleRing.h"
#include "Bronya_FlashBang.h"
#include "BronyaFlashBang_AS.h"
#include "Bronya_RandomSmoke.h"
#include "KianaUIAnim.h"
#include "Bronya_Impact_Dome.h"
#include "Bronya_LandSmoke.h"
#include "Bronya_LandImpact.h"
#include "Bronya_Teleport_Laser.h"
#include "Bronya_Teleport_Ring.h"
#include "Bronya_Grenade_Dome.h"
#include "Bronya_Grenade_Impact.h"
#include "Bronya_Grenade_TriRing.h"
#include "Bronya_Grenade.h"
#include "Bronya_Ult_Ring.h"
#include "Bronya_Ult_Wind.h"
#include "Bronya_Ult_Cannon.h"
#include "Bronya_Ult_Impact.h"
#include "Bronya_Ult_Impact_Smoke.h"
#include "Bronya_Ult_Range.h"
#include "Bronya_Ult_Laser.h"

//Particle
#include "TestParticle.h"

///// Ingame Deco Effect //////
//Stuc
#include "Stun_Eff.h"
#include "Stun_Star.h"

//Warning
#include "Warning_Ring.h"

//Portal
#include "Portal_Blue.h"
#include "Portal_Circle.h"
#include "Portal_Plane.h"
#include "Portal_Beam.h"

//Wall
#include "Stage_Wall.h"
#include "Stage_Wall_barrier.h"

//MainRoom
#include "CloudObject.h"
#include "MainRoomBG.h"

#pragma endregion

#pragma region Static setting
 
#pragma endregion

#include "Include_Valkyrie.h"
#include "ElevatorBase.h"
#include "ElevatorDoor.h"
#include "Elevator_L_Door.h"
#include "Elevator_R_Door.h"

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

	SP(Engine::CObject) spElevator_Base(CElevatorBase::Create(true, this));
	ADD_PROTOTYPE(spElevator_Base);

	SP(Engine::CObject) spElevator_Door(CElevatorDoor::Create(true, this));
	ADD_PROTOTYPE(spElevator_Door);

	SP(Engine::CObject) spElevator_L_Door(CElevator_L_Door::Create(true, this));
	ADD_PROTOTYPE(spElevator_L_Door);

	SP(Engine::CObject) spElevator_R_Door(CElevator_R_Door::Create(true, this));
	ADD_PROTOTYPE(spElevator_R_Door);

	
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

	SP(Engine::CObject) spTrap(CTrapObject::Create(true, this));
	GetObjectFactory()->AddPrototype(spTrap);
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

	SP(CBronyaBullet) spBronyaBullet(CBronyaBullet::Create(true, this));
	ADD_PROTOTYPE(spBronyaBullet);

	SP(CBronyaGrenade) spBronyaGrenade(CBronyaGrenade::Create(true, this));
	ADD_PROTOTYPE(spBronyaGrenade);

	SP(CMonster) spOJ_Box(COJ_Box::Create(true, this));
	GetObjectFactory()->AddPrototype(spOJ_Box);
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

	SP(CSoftEffect) spKiana_WSkill_Shoot(CKiana_WSkill_Shoot::Create(true, this));
	GetObjectFactory()->AddPrototype(spKiana_WSkill_Shoot);

	SP(CMeshEffect_Client) spKiana_WSkill_Circle(CKiana_WSkill_Circle::Create(true, this));
	GetObjectFactory()->AddPrototype(spKiana_WSkill_Circle);

	SP(CSoftEffect) spKianaBranchSign(CKianaBranchSign::Create(true, this));
	GetObjectFactory()->AddPrototype(spKianaBranchSign);

	SP(Engine::CObject) spKianaUIAnim(CKianaUIAnim::Create(true, this));
	GetObjectFactory()->AddPrototype(spKianaUIAnim);


	// Theresa Effect
	SP(CMeshEffect_Client) spTheresa_Ult_Eff(CTheresa_Ult_Eff::Create(true, this));
	GetObjectFactory()->AddPrototype(spTheresa_Ult_Eff);

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

	SP(CMeshEffect_Client) spTheresa_Ult_Eff_Explosion(CTheresa_Ult_Explosion::Create(true, this));
	GetObjectFactory()->AddPrototype(spTheresa_Ult_Eff_Explosion);

	SP(CMeshEffect_Client) spTheresa_Ult_Eff_Crack(CTheresa_Ult_Crack::Create(true, this));
	GetObjectFactory()->AddPrototype(spTheresa_Ult_Eff_Crack);

	SP(CMeshEffect_Client) spTheresa_Ult_Eff_ChargeAtt(CTheresaCharge_Att::Create(true, this));

	GetObjectFactory()->AddPrototype(spTheresa_Ult_Eff_ChargeAtt);

	SP(CMeshEffect_Client) spTheresa_Ult_Eff_MoveUpSmoke(CMoveUpSmoke::Create(true, this));
	GetObjectFactory()->AddPrototype(spTheresa_Ult_Eff_MoveUpSmoke);

	// Sakura

	SP(CMeshEffect_Client) spSakura_Charge_Att(CSakura_Charge_Att::Create(true, this));
	GetObjectFactory()->AddPrototype(spSakura_Charge_Att);

	SP(CMeshEffect_Client) spSakura_Trail(CSakura_Trail::Create(true, this));
	GetObjectFactory()->AddPrototype(spSakura_Trail);


	SP(CMeshEffect_Client) spSakura_WSkill_Impact(CSakura_WSkill_Impact::Create(true, this));
	GetObjectFactory()->AddPrototype(spSakura_WSkill_Impact);

	SP(CSoftEffect) spSakura_WSill_Smoke(CSakura_WSkill_Smoke::Create(true, this));
	GetObjectFactory()->AddPrototype(spSakura_WSill_Smoke);

	SP(CSoftEffect) spSakura_Mark(CSakura_Mark::Create(true, this));
	GetObjectFactory()->AddPrototype(spSakura_Mark);

	SP(CSoftEffect) spSakura_DmgMark(CSakura_DamageMark::Create(true, this));
	GetObjectFactory()->AddPrototype(spSakura_DmgMark);

	SP(CMeshEffect_Client) spSakura_WSkill_Start(CSakura_WSkill_Start::Create(true, this));	
	GetObjectFactory()->AddPrototype(spSakura_WSkill_Start);

	SP(CMeshEffect_Client) spSakura_WSkill_Twist(CSakura_WSkill_Twist::Create(true, this));	
	GetObjectFactory()->AddPrototype(spSakura_WSkill_Twist);

	SP(CMeshEffect_Client) spSakura_WSkill_TwistWind(CSakura_WSkill_Twist_Wind::Create(true, this));	
	GetObjectFactory()->AddPrototype(spSakura_WSkill_TwistWind);

	SP(Engine::CObject) spSakura_DashShade(CSakura_DashShade::Create(true, this));
	GetObjectFactory()->AddPrototype(spSakura_DashShade);


	SP(Engine::CObject) spSakura_EvadeSkill_Loop(CSakura_EvadeSkill_Loop::Create(true, this));
	GetObjectFactory()->AddPrototype(spSakura_EvadeSkill_Loop);


	SP(Engine::CObject) spSakura_EvadeSkill_Start(CSakura_EvadeSkill_Start::Create(true, this));
	GetObjectFactory()->AddPrototype(spSakura_EvadeSkill_Start);

	// Monster Spawn

	SP(CMonsterSpawnBeam) spMonster_Spawn_Beam(CMonsterSpawnBeam::Create(true, this));	
	GetObjectFactory()->AddPrototype(spMonster_Spawn_Beam);

	SP(CMeshEffect_Client) spMonster_Spawn_Eff(CMonsterSpawnEff::Create(true, this));
	GetObjectFactory()->AddPrototype(spMonster_Spawn_Eff);

	// Hit
	SP(CSoftEffect) spHitEffect(CMonsterHitEffect::Create(true, this));
	GetObjectFactory()->AddPrototype(spHitEffect);

	// Spider
	SP(CMeshEffect_Client) spSpiderExplosionEffect(CSpiderExplosion::Create(true, this));
	GetObjectFactory()->AddPrototype(spSpiderExplosionEffect);

	SP(CMeshEffect_Client) spSpiderImpact(CSpiderImpact ::Create(true, this));
	GetObjectFactory()->AddPrototype(spSpiderImpact);

	SP(CMeshEffect_Client) spSpiderExplosionBase(CSpiderExplosion_Base::Create(true, this));
	GetObjectFactory()->AddPrototype(spSpiderExplosionBase);

	// Monster AttackSign
	SP(CSoftEffect) spMonsterAttack_Sign(CMonsterAttackSign::Create(true, this));	
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
	GetObjectFactory()->AddPrototype(spScoutBall);

	SP(CScoutMeteor) spScoutMeteor(CScoutMeteor::Create(true, this));	
	GetObjectFactory()->AddPrototype(spScoutMeteor);

	SP(CSoftEffect) spSparkEffect(CSparkEffect::Create(true, this));	
	GetObjectFactory()->AddPrototype(spSparkEffect);

	SP(CMeshEffect_Client) spScoutCircleRange(CScoutCircleRange::Create(true, this));	
	GetObjectFactory()->AddPrototype(spScoutCircleRange);

	// Robot
	SP(CSoftEffect) spRobotHookEffect(CRobotHookEff::Create(true, this));	
	GetObjectFactory()->AddPrototype(spRobotHookEffect);

	SP(CMeshEffect_Client) spRobotPlane(CRobot_Plane::Create(true, this));	
	GetObjectFactory()->AddPrototype(spRobotPlane);

	SP(CMeshEffect_Client) spRobotImpact(CRobot_Impact::Create(true, this));	
	GetObjectFactory()->AddPrototype(spRobotImpact);

	SP(CMeshEffect_Client) spRobotImpactSmoke(CRobot_Impact_Smoke::Create(true, this));
	GetObjectFactory()->AddPrototype(spRobotImpactSmoke);

	// Lancer
	SP(CMeshEffect_Client) spLancer_Att_Range(CLancer_Att_Range::Create(true, this));
	GetObjectFactory()->AddPrototype(spLancer_Att_Range);

	SP(CMeshEffect_Client) spLancer_OutSideEff(CLancer_OutSideEff::Create(true, this));	
	GetObjectFactory()->AddPrototype(spLancer_OutSideEff);

	SP(CSoftEffect) spLancer_Impact(CLancer_Impact::Create(true, this));	
	GetObjectFactory()->AddPrototype(spLancer_Impact);


	// Ganesha
	SP(CMeshEffect_Client) spGaneshaLaserEffect(CGanesha_LaserEff::Create(true, this));
	GetObjectFactory()->AddPrototype(spGaneshaLaserEffect);

	SP(CMeshEffect_Client) spGaneshaChargeEffect(CGanesha_Charge_Eff::Create(true, this));	
	GetObjectFactory()->AddPrototype(spGaneshaChargeEffect);

	SP(CMeshEffect_Client) spGaneshaDomeEff(CGanesha_Dome::Create(true, this));	
	GetObjectFactory()->AddPrototype(spGaneshaDomeEff);

	SP(CMeshEffect_Client) spGaneshaDomeImpact(CGanesha_Dome_Impact::Create(true, this));	
	GetObjectFactory()->AddPrototype(spGaneshaDomeImpact);

	SP(CSoftEffect) spGaneshaSmoke(CGanesha_SmokeEff::Create(true, this));
	GetObjectFactory()->AddPrototype(spGaneshaSmoke);

	SP(CMeshEffect_Client) spGaneshaImpact(CGanesha_Impact_Eff::Create(true, this));	
	GetObjectFactory()->AddPrototype(spGaneshaImpact);

	SP(CMeshEffect_Client) spGanesha_Cinema_Circle(CGanesha_Cinema_Circle::Create(true, this));
	GetObjectFactory()->AddPrototype(spGanesha_Cinema_Circle);

	SP(CMeshEffect_Client) spGanesha_Cinema_Dome(CGanesha_Cinema_Dome::Create(true, this));
	GetObjectFactory()->AddPrototype(spGanesha_Cinema_Dome);

	SP(CSoftEffect) spGaneshaCinemaLightning(CGanesha_Cinema_Lightning::Create(true, this));
	GetObjectFactory()->AddPrototype(spGaneshaCinemaLightning);


	// 텍스처 추가해야함
	/*SP(CSoftEffect) spGaneshaUpper(CGanesha_UpperEff::Create(true, this));
	spGaneshaUpper->GetComponent<Engine::CGraphicsC>();
	spGaneshaUpper->GetComponent<Engine::CTextureC>()->AddTexture(L"hit_explosion5_new");
	spGaneshaUpper->GetComponent<Engine::CTextureC>()->AddTexture(L"hit_explosion5_new");
	spGaneshaUpper->GetComponent<Engine::CShaderC>()->AddShader((_int)EShaderID::SoftEffectShader);
	GetObjectFactory()->AddPrototype(spGaneshaUpper);*/


	// Bronya
	SP(CMeshEffect_Client) spBronyaCharge(CBronya_Cannon_Charge::Create(true, this));	
	GetObjectFactory()->AddPrototype(spBronyaCharge);

	SP(CMeshEffect_Client) spBronyaShotSmoke(CBronya_Shot_Smoke::Create(true, this));	
	GetObjectFactory()->AddPrototype(spBronyaShotSmoke);

	 
	SP(CMeshEffect_Client) spBronyaImpact(CBronya_Impact::Create(true, this));	
	GetObjectFactory()->AddPrototype(spBronyaImpact);

	SP(CMeshEffect_Client) spBronyaImpactDome(CBronya_Impact_Dome::Create(true, this));
	GetObjectFactory()->AddPrototype(spBronyaImpactDome);

	SP(CMeshEffect_Client) spBronyaImpact_Ring(CBronya_Impact_Ring::Create(true, this));	
	GetObjectFactory()->AddPrototype(spBronyaImpact_Ring);

	SP(CMeshEffect_Client) spBronyaImpact_TriRing(CBronya_Impact_TripleRing::Create(true, this));	
	GetObjectFactory()->AddPrototype(spBronyaImpact_TriRing);

	SP(CMeshEffect_Client) spBronyaFlashBang(CBronya_FlashBang::Create(true, this));	
	GetObjectFactory()->AddPrototype(spBronyaFlashBang);

	SP(CSoftEffect) spBronyaFlashBangAS(CBronyaFlashBang_AS::Create(true, this));
	GetObjectFactory()->AddPrototype(spBronyaFlashBangAS);

	SP(CSoftEffect) spBronyaRandomSmoke(CBronya_RandomSmoke::Create(true, this));
	GetObjectFactory()->AddPrototype(spBronyaRandomSmoke);


	SP(CMeshEffect_Client) spBronyaLandSmoke(CBronya_LandSmoke::Create(true, this));	
	GetObjectFactory()->AddPrototype(spBronyaLandSmoke);

	SP(CMeshEffect_Client) spBronyaLandImpact(CBronya_LandImpact::Create(true, this));	
	GetObjectFactory()->AddPrototype(spBronyaLandImpact);

	SP(CMeshEffect_Client) spBronyaTeleportLaser(CBronya_Teleport_Laser::Create(true, this));	
	GetObjectFactory()->AddPrototype(spBronyaTeleportLaser);

	SP(CSoftEffect) spBronyaTeleportRing(CBronya_Teleport_Ring::Create(true, this));
	GetObjectFactory()->AddPrototype(spBronyaTeleportRing);

	SP(CMeshEffect_Client) spBronyaGrenadeDome(CBronya_Grenade_Dome::Create(true, this));	
	GetObjectFactory()->AddPrototype(spBronyaGrenadeDome);

	SP(CMeshEffect_Client) spBronyaGrenadeImpact(CBronya_Grenade_Impact::Create(true, this));	
	GetObjectFactory()->AddPrototype(spBronyaGrenadeImpact);

	SP(CMeshEffect_Client) spBronya_Grenade_TriRing(CBronya_Grenade_TriRing::Create(true, this));	
	GetObjectFactory()->AddPrototype(spBronya_Grenade_TriRing);

	//SP(CMeshEffect_Client) spBronya_Grenade(CBronya_Grenade::Create(true, this));
	//spBronya_Grenade->GetComponent<Engine::CMeshC>()->SetMeshData(L"Bronya_Throw01_Grenade01");
	//spBronya_Grenade->GetComponent<Engine::CMeshC>()->SetIsEffectMesh(true);
	//spBronya_Grenade->GetComponent<Engine::CGraphicsC>()->SetRenderID((_int)Engine::ERenderID::AlphaBlend);
	//spBronya_Grenade->GetComponent<Engine::CTextureC>()->AddTexture(L"Grenade_Explosion");
	//spBronya_Grenade->GetComponent<Engine::CTextureC>()->AddTexture(L"Grenade_Explosion");
	//spBronya_Grenade->GetComponent<Engine::CShaderC>()->AddShader((_int)EShaderID::AlphaMaskShader);
	SP(CMeshEffect_Client) spBronya_Grenade(CBronya_Grenade::Create(true, this));	
	GetObjectFactory()->AddPrototype(spBronya_Grenade);

	SP(CMeshEffect_Client) spBronya_Ult_Ring(CBronya_Ult_Ring::Create(true, this));	
	GetObjectFactory()->AddPrototype(spBronya_Ult_Ring);

	SP(CMeshEffect_Client) spBronya_Ult_Wind(CBronya_Ult_Wind::Create(true, this));	
	GetObjectFactory()->AddPrototype(spBronya_Ult_Wind);

	SP(CMeshEffect_Client) spBronya_Cannon(CBronya_Ult_Cannon::Create(true, this));	
	GetObjectFactory()->AddPrototype(spBronya_Cannon);

	SP(CMeshEffect_Client) spBronya_Ult_Impact(CBronya_Ult_Impact::Create(true, this));	
	GetObjectFactory()->AddPrototype(spBronya_Ult_Impact);

	SP(CMeshEffect_Client) spBronya_Ult_Impact_Smoke(CBronya_Ult_Impact_Smoke::Create(true, this));	
	GetObjectFactory()->AddPrototype(spBronya_Ult_Impact_Smoke);

	SP(CMeshEffect_Client) spBronya_Ult_Range(CBronya_Ult_Range::Create(true, this));	
	GetObjectFactory()->AddPrototype(spBronya_Ult_Range);

	SP(CSoftEffect) spBronya_UIt_Laser(CBronya_Ult_Laser::Create(true, this));
	GetObjectFactory()->AddPrototype(spBronya_UIt_Laser);

	// Ingame

	SP(CMeshEffect_Client) spWarning_Ring(CWarning_Ring::Create(true, this));	
	GetObjectFactory()->AddPrototype(spWarning_Ring);

	// Portal

	SP(CMeshEffect_Client) spPortalPlane(CPortal_Plane::Create(true, this));	
	GetObjectFactory()->AddPrototype(spPortalPlane);

	SP(CMeshEffect_Client) spPortalCircle(CPortal_Circle::Create(true, this));
	GetObjectFactory()->AddPrototype(spPortalCircle);

	SP(CMeshEffect_Client) spPortalBlue(CPortal_Blue::Create(true, this));	
	GetObjectFactory()->AddPrototype(spPortalBlue);

	SP(CMeshEffect_Client) spPortalBeam(CPortal_Beam::Create(true, this));	
	GetObjectFactory()->AddPrototype(spPortalBeam);

	// Particle
	SP(Engine::CObject) spTestParticle(CTestParticle::Create(true, this));
	GetObjectFactory()->AddPrototype(spTestParticle);


	// Wall Effect
	SP(CMeshEffect_Client) spStageWall(CStage_Wall::Create(true, this));
	GetObjectFactory()->AddPrototype(spStageWall);

	SP(CMeshEffect_Client) spStageWallBarrier(CStage_Wall_barrier::Create(true, this));
	GetObjectFactory()->AddPrototype(spStageWallBarrier);

	// MainRoom
	SP(Engine::CObject) spCloudObject(CCloudObject::Create(true, this));
	GetObjectFactory()->AddPrototype(spCloudObject);

	SP(Engine::CObject) spMainRoomBG(CMainRoomBG::Create(true, this));
	GetObjectFactory()->AddPrototype(spMainRoomBG);

	SP(CMeshEffect_Client) spStun_Eff(CStun_Eff::Create(true, this));
	GetObjectFactory()->AddPrototype(spStun_Eff);

	SP(CMeshEffect_Client) spStun_Star(CStun_Star::Create(true, this));
	GetObjectFactory()->AddPrototype(spStun_Star);

}
