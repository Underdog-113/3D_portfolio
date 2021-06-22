#include "stdafx.h"
#include "WooScene.h"

//#include "EmptyObject.h"
//#include "ObjectFactory.h"

#include "StageControlTower.h"
//#include "AniCtrl.h"
#include "Kiana.h"

/* for.Monster */
#include "FSM_SpiderC.h"
//#include "FSMDefine_Spider.h"
#include "MO_Spider.h"

#include "FSM_SickleC.h"
#include "FSMDefine_Sickle.h"
#include "MO_Sickle.h"

#include "FSM_GaneshaC.h"
#include "FSMDefine_Ganesha.h"
#include "MB_Ganesha.h"

#include "PatternMachineC.h"
#include "ClientPatterns.h"
/**/

//#include "DataLoad.h"

CWooScene::CWooScene()
{
}

CWooScene::~CWooScene()
{
	m_pController->DestroyInstance();
}

CClientScene* CWooScene::Create(void)
{
	CWooScene* pInstance = new CWooScene;
	pInstance->Awake((_int)ELayerID::NumOfLayerID);

	return pInstance;
}

void CWooScene::Free(void)
{
	OnDestroy();
	delete this;
}

void CWooScene::Awake(_int numOfLayers)
{
	__super::Awake(numOfLayers);

	InitPrototypes();

	m_pController = CStageControlTower::GetInstance();
	m_pController->Awake();
}

void CWooScene::Start(void)
{
	__super::Start();
	{
		//CDataLoad* Load = new CDataLoad();
		//Load->Setting();
		//Load->ButtonLoad(this);
		//Load->ImageLoad(this);
		//Load->SliderLoad(this);
		//Load->ScrollViewLoad(this);
		//Load->CanvasLoad(this);
		//Load->TextLoad(this);
		//Load->ToolLoad(this);
		//delete(Load);

		// Kiana Setting
		{
			SP(Engine::CObject) spKianaClone = ADD_CLONE(L"Kiana", true, (_uint)ELayerID::Player, L"Kiana");

			m_spKiana = spKianaClone;
			m_pController->AddSquadMember(m_spKiana);
			m_pController->Start(CStageControlTower::WithoutUI);

			//spKianaClone->GetComponent<Engine::CRigidBodyC>()->SetIsEnabled(false);

			auto cam = Engine::CCameraManager::GetInstance()->GetCamera(m_objectKey + L"BasicCamera");
			cam->SetTarget(m_spKiana);
			cam->SetTargetDist(2.f);
			CStageControlTower::GetInstance()->SetCurrentMainCam(cam);
		}

		// cube terrain
		{

			SP(Engine::CObject) spCube = ADD_CLONE(L"EmptyObject", true, (_int)ELayerID::Player, L"Cube0");

			/*spCube->AddComponent<Engine::CMeshC>()->AddMeshData(L"Sphere");
			spCube->AddComponent<Engine::CTextureC>()->AddTexture(L"Castle_wall", 0);*/
			spCube->AddComponent<Engine::CGraphicsC>()->SetRenderID((_int)Engine::ERenderID::NonAlpha);

			spCube->AddComponent<Engine::CCollisionC>()->
				AddCollider(Engine::CAabbCollider::Create((_int)ECollisionID::Floor, _float3(50, 0, 50)));
			spCube->GetComponent<Engine::CCollisionC>()->
				AddCollider(Engine::CRayCollider::Create((_int)ECollisionID::WallRay, ZERO_VECTOR, FORWARD_VECTOR, 1.1f));

			spCube->AddComponent<Engine::CDebugC>();
			spCube->AddComponent<Engine::CShaderC>()/*->AddShader((_int)Engine::EShaderID::MeshShader)*/;
			spCube->AddComponent<Engine::CRigidBodyC>();
			spCube->GetComponent<Engine::CRigidBodyC>()->SetIsEnabled(false);
			spCube->GetTransform()->SetSize(10, 1, 10);
			spCube->GetTransform()->SetPosition(0, 0, 0);

			// 2
			m_pivot = ADD_CLONE(L"EmptyObject", true, (_int)ELayerID::Player, L"Cube0");

			m_pivot->AddComponent<Engine::CMeshC>()->SetMeshData(L"Sphere");
			m_pivot->AddComponent<Engine::CTextureC>()->AddTexture(L"Castle_wall", 0);
			m_pivot->AddComponent<Engine::CGraphicsC>()->SetRenderID((_int)Engine::ERenderID::NonAlpha);

			m_pivot->AddComponent<Engine::CCollisionC>()->
				AddCollider(Engine::CRayCollider::Create((_int)ECollisionID::FloorRay, _float3(0, 0, 0), _float3(0, -1, 0), 1.4f));
			m_pivot->GetComponent<Engine::CCollisionC>()->
				AddCollider(Engine::CRayCollider::Create((_int)ECollisionID::WallRay, ZERO_VECTOR, FORWARD_VECTOR, 1.1f));

			m_pivot->AddComponent<Engine::CDebugC>();
			m_pivot->AddComponent<Engine::CShaderC>()->AddShader((_int)Engine::EShaderID::MeshShader);
			m_pivot->AddComponent<Engine::CRigidBodyC>();
			m_pivot->GetComponent<Engine::CRigidBodyC>()->SetIsEnabled(false);
			m_pivot->GetTransform()->SetSize(0.1f, 0.1f, 0.1f);

			//3		
			m_pivot_kiana = ADD_CLONE(L"EmptyObject", true, (_int)ELayerID::Player, L"Cube0");

			m_pivot_kiana->AddComponent<Engine::CMeshC>()->SetMeshData(L"Sphere");
			m_pivot_kiana->AddComponent<Engine::CTextureC>()->AddTexture(L"Castle_wall", 0);
			m_pivot_kiana->AddComponent<Engine::CGraphicsC>()->SetRenderID((_int)Engine::ERenderID::NonAlpha);

			m_pivot_kiana->AddComponent<Engine::CCollisionC>()->
				AddCollider(Engine::CRayCollider::Create((_int)ECollisionID::FloorRay, _float3(0, 0, 0), _float3(0, -1, 0), 1.4f));
			m_pivot_kiana->GetComponent<Engine::CCollisionC>()->
				AddCollider(Engine::CRayCollider::Create((_int)ECollisionID::WallRay, ZERO_VECTOR, FORWARD_VECTOR, 1.1f));

			m_pivot_kiana->AddComponent<Engine::CDebugC>();
			m_pivot_kiana->AddComponent<Engine::CShaderC>()->AddShader((_int)Engine::EShaderID::MeshShader);
			m_pivot_kiana->AddComponent<Engine::CRigidBodyC>();
			m_pivot_kiana->GetComponent<Engine::CRigidBodyC>()->SetIsEnabled(false);
			m_pivot_kiana->GetTransform()->SetSize(0.1f, 0.1f, 0.1f);
		}

		// Monster
		{
			/* Sickle */
			SP(Engine::CObject) spSickleClone = ADD_CLONE(L"MO_Sickle", true, (_uint)ELayerID::Enemy, L"MO_Sickle");
			spSickleClone->GetTransform()->SetPosition(0, 10, 2);
			spSickleClone->AddComponent<CPatternMachineC>()->AddNecessaryPatterns(CSickleBornPattern::Create(), CSickleDiePattern::Create(), CSickleBasePattern::Create(), CSickleHitPattern::Create());
			//spSickleClone->GetComponent<CPatternMachineC>()->AddPattern(CSickleAtk02Pattern::Create());
			m_spSickle = spSickleClone;

			///* Spider */
			//SP(Engine::CObject) spSpiderClone = ADD_CLONE(L"MO_Spider", true, (_uint)ELayerID::Enemy, L"MO_Spider");
			//spSpiderClone->GetTransform()->SetPosition(-3, 0, -7);
			//spSpiderClone->GetTransform()->SetRotationY(D3DXToRadian(90));
			//spSpiderClone->AddComponent<CPatternMachineC>()->AddNecessaryPatterns(CSpiderBornPattern::Create(), CSpiderDiePattern::Create(), CSpiderBasePattern::Create(), CSpiderHitPattern::Create());
			//m_spSpider = spSpiderClone;

			///* Ganesha */
			//SP(Engine::CObject) spGaneshaClone = ADD_CLONE(L"MB_Ganesha", true, (_uint)ELayerID::Enemy, L"MB_Ganesha");
			//spGaneshaClone->GetTransform()->SetSize(2, 2, 2);
			//spGaneshaClone->GetTransform()->SetPosition(3, 0, 3);
			//spGaneshaClone->GetTransform()->SetRotationY(D3DXToRadian(90));
			//spGaneshaClone->AddComponent<CPatternMachineC>()->AddNecessaryPatterns(CGaneshaBornPattern::Create(), CGaneshaDiePattern::Create(), CGaneshaBasePattern::Create(), CGaneshaHitPattern::Create());
			//spGaneshaClone->GetComponent<CPatternMachineC>()->AddPattern(CGaneshaStampPattern::Create());
			//spGaneshaClone->GetComponent<CPatternMachineC>()->AddPattern(CGaneshaRoll01Pattern::Create());
			//spGaneshaClone->GetComponent<CPatternMachineC>()->AddPattern(CGaneshaBurst01Pattern::Create());
			//spGaneshaClone->GetComponent<CPatternMachineC>()->AddPattern(CGaneshaBurst02Pattern::Create());
			//m_spGanesha = spGaneshaClone;
		}
	}
}

void CWooScene::FixedUpdate(void)
{
	__super::FixedUpdate();
}

void CWooScene::Update(void)
{
	__super::Update();

	m_pController->Update();

	//_float3 pos1 = m_spKiana->GetTransform()->GetPosition();
	//_float3 pos2 = m_spSickle->GetTransform()->GetPosition();

	//m_pivot->GetTransform()->SetPosition(pos2);
	//m_pivot_kiana->GetTransform()->SetPosition(pos1);

	//SpiderPattern0();
	//GaneshaPattern0();
	//GaneshaPattern1();
	//GaneshaPattern2();

	//std::cout << "kiana  : " << pos2.x << "," << pos2.y << "," << pos2.z << std::endl;
	//std::cout << "moster : " << pos1.x << "," << pos1.y << "," << pos1.z << std::endl;
	//std::cout << "===========================================" << std::endl;
}

void CWooScene::LateUpdate(void)
{
	__super::LateUpdate();
}

void CWooScene::OnDestroy(void)
{
	__super::OnDestroy();

	m_pController->DestroyInstance();
}

void CWooScene::OnEnable(void)
{
	__super::OnEnable();
}

void CWooScene::OnDisable(void)
{
	__super::OnDisable();
}

void CWooScene::SpiderPattern0()
{
	//if (Name_Walk_Forward != m_fsm->GetCurStateString())
	//	m_fsm->ChangeState(Name_Walk_Forward);

	//_float3 tPos = m_spKiana->GetTransform()->GetPosition();
	//_float3 mPos = m_spSickle->GetTransform()->GetPosition();
	//_float mSpeed = 1.f;

	//static_cast<CMO_Spider*>(m_spSickle.get())->ChaseTarget(tPos);

	//_float3 dir = tPos - mPos;

	//mPos += *D3DXVec3Normalize(&dir, &dir) * mSpeed * GET_DT;
	//m_spSickle->GetTransform()->SetPosition(mPos);
}

void CWooScene::GaneshaPattern0()
{
	//_float3 tPos = m_spKiana->GetTransform()->GetPosition(); // target pos
	//_float3 mPos = m_spGanesha->GetTransform()->GetPosition(); // monster pos
	////_float mSpeed = 1.f;

	//_float len = D3DXVec3Length(&(tPos - mPos));

	//CoolTime(m_atkTime, m_sickleAtkCool, m_atkReady);
	//CoolTime(m_walkTime, m_sickleWalkCool, m_walkReady);

	//static_cast<CMB_Ganesha*>(m_spGanesha.get())->ChaseTarget(tPos);

	//if (false == m_pattern0)
	//	return;

	//// 상대가 공격 범위 밖이고
	//if (len > m_sickleAtkDis)
	//{
	//	// 공격 상태고, 애니가 끝났다면 
	//	if (Name_Attack01 == m_fsm->GetCurStateString() && m_fsm->GetDM()->IsAnimationEnd())
	//	{
	//		m_fsm->ChangeState(Name_Jump_Back);
	//		m_pattern1 = false;
	//		m_pattern2 = true;
	//	}

	//	// 내가 대기 상태면 이동 애니로 변경
	//	if (Name_StandBy == m_fsm->GetCurStateString() && m_fsm->GetDM()->IsAnimationEnd())
	//	{
	//		m_fsm->ChangeState(Name_Run);
	//	}
	//	// 내가 이동 중이라면
	//	else if (Name_Run == m_fsm->GetCurStateString())
	//	{
	//		_float3 dir = tPos - mPos;

	//		mPos += *D3DXVec3Normalize(&dir, &dir) * GET_DT;
	//		m_spGanesha->GetTransform()->SetPosition(mPos);
	//	}
	//	// 내가 뒤로 이동 중이라면
	//	else if (Name_Jump_Back == m_fsm->GetCurStateString() && m_fsm->GetDM()->IsAnimationEnd() && false == m_walkReady)
	//	{
	//		_float3 dir = tPos - mPos;

	//		mPos -= *D3DXVec3Normalize(&dir, &dir) * 1.5f;
	//		m_spGanesha->GetTransform()->SetPosition(mPos);
	//		m_fsm->GetDM()->GetAniCtrl()->SetSpeed(0.5f);
	//		m_walkReady = true;
	//	}
	//	// 내가 뒤로 이동 중이라면
	//	else if (Name_Jump_Back == m_fsm->GetCurStateString() && m_fsm->GetDM()->IsAnimationEnd() && true == m_walkReady)
	//	{
	//		m_fsm->ChangeState(Name_Run);
	//	}
	//}
	//// 상대가 공격 범위 안이고
	//else if (len <= m_sickleAtkDis)
	//{
	//	// 뒤로 이동 상태고, 애니가 끝났고, walkReady가 true라면 대기로 변경
	//	if (Name_Jump_Back == m_fsm->GetCurStateString() && m_fsm->GetDM()->IsAnimationEnd() && true == m_walkReady)
	//	{
	//		m_fsm->ChangeState(Name_StandBy);
	//	}
	//	
	//	// 이동 상태라면 대기로 변경
	//	if (Name_Run == m_fsm->GetCurStateString() && m_fsm->GetDM()->IsAnimationEnd())
	//	{
	//		m_fsm->ChangeState(Name_StandBy);
	//		m_pattern0 = false;
	//		m_pattern1 = true;
	//	}
	//	
	//	// 공격 상태고, 애니가 끝났다면 
	//	if (Name_Attack01 == m_fsm->GetCurStateString() && m_fsm->GetDM()->IsAnimationEnd())
	//	{
	//		m_fsm->ChangeState(Name_Run);
	//		m_pattern1 = false;
	//		m_pattern2 = true;
	//	}
	//}
}

void CWooScene::GaneshaPattern1()
{
	//if (false == m_pattern1)
	//	return;

	//m_fsm->ChangeState(Name_Attack01);
	//m_atkReady = false;
	//m_pattern0 = true;
	//m_pattern1 = false;
}

void CWooScene::GaneshaPattern2()
{
	//if (false == m_pattern2)
	//	return;

	//m_fsm->ChangeState(Name_Jump_Back);
	//m_walkReady = false;
	//m_pattern0 = true;
	//m_pattern2 = false;
}

void CWooScene::InitPrototypes(void)
{
}
