#include "stdafx.h"
#include "JongScene.h"
#include "ObjectFactory.h"

#include "DataLoad.h"
#include "DynamicMeshData.h"

#include "DamageObjectPool.h"
#include "PatternMachineC.h"
#include "ClientPatterns.h"
#include "StageControlTower.h"
#include "FSM_KianaC.h"
#include "Kiana.h"
#include "AniCtrl.h"

#include "Kiana_CatPaw_Atk01.h"
#include "Kiana_CatPaw_Atk02.h"
#include "Kiana_CatPaw_Atk03.h"
#include "Kiana_CatPaw_Atk04.h"
#include "Kiana_CatPaw_Atk05.h"

#include "Kiana_CatPaw_Ring_Atk01.h"
#include "Kiana_Pistol.h"

#include "Theresa.h"

#include "MO_Dummy.h"
#include "MO_Sickle.h"

CJongScene::CJongScene()
{
}


CJongScene::~CJongScene()
{
}

CClientScene* CJongScene::Create(void)
{
	CJongScene* pInstance = new CJongScene;
	pInstance->Awake((_int)ELayerID::NumOfLayerID);

	return pInstance;
}

void CJongScene::Free(void)
{
	OnDestroy();
	delete this;
}

void CJongScene::Awake(_int numOfLayers)
{
	__super::Awake(numOfLayers);

	m_pControlTower = CStageControlTower::GetInstance();
	m_pControlTower->Awake();
}

void CJongScene::Start(void)
{
	__super::Start();
	CDamageObjectPool::GetInstance()->Start(this);

	//KianaTest();
	TheresaTest();
	//static_cast<CValkyrie*>(m_spTheresa.get())->SetIsWait(true);
	//SakuraTest();
	//static_cast<CValkyrie*>(m_spSakura.get())->SetIsWait(true);
	m_pControlTower->Start(CStageControlTower::ALL);

	//SetSceneCamera(m_spKiana);
	SetSceneCamera(m_spTheresa);

	//CollisionDummy();
	//SickleTest();
	//SpiderTest();
	//GaneshaTest();
	//RobotTest();

	FloorTest();


	SetupStageUI();
}

void CJongScene::FixedUpdate(void)
{
	__super::FixedUpdate();
}

void CJongScene::Update(void)
{
	__super::Update();
	m_pControlTower->Update();

	if (Engine::CInputManager::GetInstance()->KeyDown(KEY_C))
	{
// 		HitInfo info;
// 		info.SetDamageRate(1.f);
// 		info.SetStrengthType(HitInfo::Str_Low);
// 		info.SetCrowdControlType(HitInfo::CC_None);
// 
// 		((CKiana*)m_spKiana.get())->ApplyHitInfo(info);
// 		//m_pControlTower->HitValkyrie(m_spDummy.get(), m_spKiana.get(), info);

		//++idx;
		m_spTheresa->GetComponent<Engine::CMeshC>()->GetFirstMeshData_Dynamic()->GetAniCtrl()->ChangeAniSet(26);

		//m_pControlTower->HitValkyrie(m_spDummy.get(), m_spKiana.get(), info);
	}

	if (Engine::CInputManager::GetInstance()->KeyDown(KEY_V))
	{
// 		HitInfo info;
// 		info.SetDamageRate(1.f);
// 		info.SetStrengthType(HitInfo::Str_High);
// 		info.SetCrowdControlType(HitInfo::CC_None);
// 
// 		
// 		((CKiana*)m_spKiana.get())->ApplyHitInfo(info);
		//m_pControlTower->HitValkyrie(m_spDummy2.get(), m_spKiana.get(), info);
	}

//	_float3 pos = m_spKiana->GetTransform()->GetPosition();


}

void CJongScene::LateUpdate(void)
{
	__super::LateUpdate();
}

void CJongScene::OnDestroy(void)
{
	__super::OnDestroy();

	CBattleUiManager::DestroyInstance();
	CDamageObjectPool::DestroyInstance();
	m_pControlTower->DestroyInstance();
	m_pControlTower = nullptr;
}

void CJongScene::OnEnable(void)
{
	__super::OnEnable();

}

void CJongScene::OnDisable(void)
{
	__super::OnDisable();

}

void CJongScene::InitPrototypes(void)
{
}

void CJongScene::KianaTest()
{
	// Kiana Body

	SP(Engine::CObject) spKianaClone = ADD_CLONE(L"Kiana", true, (_uint)ELayerID::Player, L"Kiana");

	m_spKiana = spKianaClone;
	m_pControlTower->AddSquadMember(m_spKiana);
}

void CJongScene::TheresaTest()
{
	// Theresa

	SP(Engine::CObject) spTheresaClone = ADD_CLONE(L"Theresa", true, (_uint)ELayerID::Player, L"Theresa");

	m_spTheresa = spTheresaClone;
	m_pControlTower->AddSquadMember(m_spTheresa);
}

void CJongScene::SakuraTest()
{
	SP(Engine::CObject) spSakuraClone = ADD_CLONE(L"Sakura", true, (_uint)ELayerID::Player, L"Sakura");

	m_spSakura = spSakuraClone;
	m_pControlTower->AddSquadMember(m_spSakura);

	//spSakuraClone->GetComponent<Engine::CRigidBodyC>()->SetIsEnabled(false);
}

void CJongScene::SetSceneCamera(SP(Engine::CObject) pTarget)
{
	auto cam = Engine::CCameraManager::GetInstance()->GetCamera(m_objectKey + L"BasicCamera");
	cam->SetTarget(pTarget);
	cam->SetTargetDist(3.f);
	m_pControlTower->ActorControl_SetCurrentMainCam(cam);
}

void CJongScene::CollisionDummy()
{
	BaseStat stat;
	stat.SetBaseHp(321.f);
	stat.SetBaseAtk(120.f);
	stat.SetBaseDef(44.f);

	stat.SetGrowHp(10.f);
	stat.SetGrowAtk(1.2f);
	stat.SetGrowDef(1.f);


	m_spDummy = ADD_CLONE(L"MO_Dummy", true, (_uint)ELayerID::Enemy, L"MO_Dummy");
	m_spDummy->GetTransform()->SetPosition(0, 0, 5);


	m_spDummy2 = ADD_CLONE(L"MO_Dummy", true, (_uint)ELayerID::Enemy, L"MO_Dummy");
	m_spDummy2->GetTransform()->SetPosition(-2, 0, 5);

	static_cast<CMO_Dummy*>(m_spDummy2.get())->SetStatus(stat);
}

void CJongScene::SpiderTest()
{
	SP(Engine::CObject) spSpiderClone = ADD_CLONE(L"MO_Spider", true, (_uint)ELayerID::Enemy, L"MO_Spider");
	spSpiderClone->GetTransform()->SetPosition(0.f, 0.f, 5.f);
	spSpiderClone->AddComponent<CPatternMachineC>()->AddNecessaryPatterns(CSpiderBornPattern::Create(), CSpiderDiePattern::Create(), CSpiderBasePattern::Create(), CSpiderHitPattern::Create());
}

void CJongScene::SickleTest()
{
	/* Sickle */
	SP(Engine::CObject) spSickleClone = ADD_CLONE(L"MO_Sickle", true, (_uint)ELayerID::Enemy, L"MO_Sickle");
	spSickleClone->GetTransform()->SetSize(2, 2, 2);
	spSickleClone->GetTransform()->SetPosition(0, 0, 2);
	spSickleClone->GetTransform()->SetRotationY(D3DXToRadian(90));
	//spSickleClone->AddComponent<CPatternMachineC>()->AddNecessaryPatterns(CSickleBornPattern::Create(), CSickleDiePattern::Create(), CSickleBasePattern::Create(), CSickleHitPattern::Create());
	//spSickleClone->GetComponent<CPatternMachineC>()->AddPattern(CSickleAtk02Pattern::Create());
	m_spSickle = spSickleClone;
}

void CJongScene::GaneshaTest()
{
	/* Ganesha */
	SP(Engine::CObject) spGaneshaClone = ADD_CLONE(L"MB_Ganesha", true, (_uint)ELayerID::Enemy, L"MB_Ganesha");
	spGaneshaClone->GetTransform()->SetPosition(3, 0, 3);
	//spGaneshaClone->AddComponent<CPatternMachineC>()->AddNecessaryPatterns(CGaneshaBornPattern::Create(), CGaneshaDiePattern::Create(), CGaneshaBasePattern::Create(), CGaneshaHitPattern::Create());
	spGaneshaClone->GetComponent<CPatternMachineC>()->AddPattern(CGaneshaStampPattern::Create());
	spGaneshaClone->GetComponent<CPatternMachineC>()->AddPattern(CGaneshaRoll01Pattern::Create());
	//spGaneshaClone->GetComponent<CPatternMachineC>()->AddPattern(CGaneshaBurst01Pattern::Create());
	spGaneshaClone->GetComponent<CPatternMachineC>()->AddPattern(CGaneshaBurst02Pattern::Create());
	//m_spGanesha = spGaneshaClone;
}

void CJongScene::RobotTest()
{
	/* Ganesha */
	SP(Engine::CObject) spRobotClone = ADD_CLONE(L"MO_Robot", true, (_uint)ELayerID::Enemy, L"MO_Robot");
	spRobotClone->GetTransform()->SetPosition(3, 2, 3);
}

void CJongScene::FloorTest()
{
	// cube terrain
	{
		SP(Engine::CObject) spCube = ADD_CLONE(L"EmptyObject", true, (_int)ELayerID::Player, L"Cube0");


		spCube->AddComponent<Engine::CCollisionC>()->
			AddCollider(Engine::CAabbCollider::Create((_int)ECollisionID::Floor, _float3(20.f, 1.f, 20.f)));

		spCube->AddComponent<Engine::CDebugC>();
		spCube->AddComponent<Engine::CShaderC>();
		spCube->GetTransform()->SetSize(20, 1, 20);
		spCube->GetTransform()->SetPosition(0, -1.f, 0);

	}

}


void CJongScene::SetupStageUI()
{
	CDataLoad* Load = new CDataLoad();
	Load->Setting();
	Load->ButtonLoad(this);
	Load->ImageLoad(this);
	Load->SliderLoad(this);
	Load->ScrollViewLoad(this);
	Load->CanvasLoad(this);
	Load->TextLoad(this);
	//Load->MapLoad(this);
	delete(Load);

	CBattleUiManager::GetInstance()->Start(this);
}
