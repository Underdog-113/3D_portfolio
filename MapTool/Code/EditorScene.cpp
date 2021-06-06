#include "stdafx.h"
#include "EditorScene.h"

#include "MeshData.h"
#include "StaticMeshData.h"
#include "DynamicMeshData.h"

#include "Object.h"
#include "ObjectFactory.h"

#include "InputManager.h"
#include "TextureStore.h"
#include "Layer.h"
#include "DataStore.h"

#include "MainFrm.h"
#include "MapToolView.h"
#include "ToolMenuView.h"
#include "SceneManager.h"
#include "WndApp.h"

#pragma region Prototypes
#include "EmptyObject.h"
#include "Grid.h"
#include "Camera.h"
#pragma endregion

CEditorScene::CEditorScene()
{
}

CEditorScene::~CEditorScene()
{
}

Engine::CScene* CEditorScene::Create(void)
{
	Engine::CScene* pEditorScene = new CEditorScene;
	pEditorScene->Awake((_int)ELayerID::NumOfLayerID);

	return pEditorScene;
}

void CEditorScene::Free(void)
{
	OnDestroy();
	delete this;
}

void CEditorScene::Awake(_int numOfLayers)
{
	__super::Awake(numOfLayers);

	//DataStore Init
	m_pDataStore->InitDataMap((_uint)EDataID::NumOfDataID);
	m_pDataStore->AddDataSection(L"BasicObject", (_uint)EDataID::BasicObject);
	m_pDataStore->AddDataSection(L"Player", (_uint)EDataID::Player);
	m_pDataStore->AddDataSection(L"Scene", (_uint)EDataID::Scene);
	
	m_pDataStore->InitDataForScene(L"StaticScene", true);
	m_pMeshStore->InitMeshForScene(L"StaticScene", true);
	m_pTextureStore->InitTextureForScene(L"StaticScene", true);

	m_pDataStore->InitDataForScene(m_objectKey);
	m_pMeshStore->InitMeshForScene(m_objectKey);
	m_pTextureStore->InitTextureForScene(m_objectKey);

	InitPrototypes();

	//m_pMain = dynamic_cast<CMainFrame*>(::AfxGetApp()->GetMainWnd());
	//m_pEditorView = dynamic_cast<CMy3DEditorView*>(m_pMain->m_mainSplitter.GetPane(0, 0));
	//m_pInspectorView = dynamic_cast<CInspectorView*>(m_pMain->m_mainSplitter.GetPane(0, 1));
}

void CEditorScene::Start(void)
{
	__super::Start();

	SP(Engine::CObject) spEmptyObject
		= m_pObjectFactory->AddClone(L"EmptyObject", true, (_int)ELayerID::Player, L"Kiana");

	spEmptyObject->AddComponent<Engine::CMeshC>()->AddMeshData(L"Kiana");
	spEmptyObject->GetComponent<Engine::CMeshC>()->SetInitTex(true);
	spEmptyObject->AddComponent<Engine::CTextureC>();
	spEmptyObject->AddComponent<Engine::CGraphicsC>()->SetRenderID((_int)Engine::ERenderID::NonAlpha);
	spEmptyObject->GetTransform()->SetSize(10, 10, 10);
	//spEmptyObject->GetTransform()->SetPosition(0.f, 0.f, 0.f);

	//SP(Engine::CObject) spCube
	//	= m_pObjectFactory->AddClone(L"EmptyObject", true, (_int)ELayerID::Player, L"Cube");

	//spCube->AddComponent<Engine::CMeshC>()->AddMeshData(L"Cube");
	//spCube->GetComponent<Engine::CMeshC>()->SetInitTex(true);
	//spCube->AddComponent<Engine::CTextureC>();
	//spCube->AddComponent<Engine::CGraphicsC>()->SetRenderID((_int)Engine::ERenderID::NonAlpha);
	//spCube->GetTransform()->SetSize(1, 1, 1);
	//spCube->GetTransform()->SetPosition(10.f, -1.f, 10.f);

	SP(Engine::CObject) spMap
		= m_pObjectFactory->AddClone(L"EmptyObject", true, (_int)ELayerID::Map, L"S02");

	spMap->AddComponent<Engine::CMeshC>()->AddMeshData(L"S02_del");
	spMap->GetComponent<Engine::CMeshC>()->SetInitTex(true);
	spMap->AddComponent<Engine::CTextureC>();
	spMap->AddComponent<Engine::CGraphicsC>()->SetRenderID((_int)Engine::ERenderID::NonAlpha);
}

void CEditorScene::FixedUpdate(void)
{
	__super::FixedUpdate();
}

void CEditorScene::Update(void)
{
	__super::Update();
	m_pMenuView->Update();

	InputSetting();
	Picking();
}

void CEditorScene::LateUpdate(void)
{
	__super::LateUpdate();
}

void CEditorScene::OnDestroy(void)
{
	__super::OnDestroy();
}

void CEditorScene::OnEnable(void)
{
	__super::OnEnable();
}

void CEditorScene::OnDisable(void)
{
	__super::OnDisable();
}

void CEditorScene::InitPrototypes(void)
{
	SP(Engine::CObject) spEmptyObjectPrototype(Engine::CEmptyObject::Create(true, this));
	ADD_PROTOTYPE(spEmptyObjectPrototype);

	SP(Engine::CCamera) spCameraPrototype(Engine::CCamera::Create(true, this));
	ADD_PROTOTYPE(spCameraPrototype);
}

void CEditorScene::Picking()
{
	_float3 origin = {};
	_float3 intersection = {};
	Engine::CScene* curScene = Engine::GET_CUR_SCENE;
	
	if (m_pickingMode && (Engine::IMKEY_DOWN(MOUSE_LEFT)))
	{
		_mat matCamWorld;
		D3DXMatrixInverse(&matCamWorld, NULL, &Engine::GET_MAIN_CAM->GetViewMatrix());
		origin = { matCamWorld._31, matCamWorld._32, matCamWorld._33 };

		Engine::CObject* pTarget = RayCast(origin, 1000.f, intersection);

		if (!pTarget)
			std::cout << "target not found" << std::endl;

		else // 피킹이 되었으면 오브젝트 생성 또는 저장
		{
			if (true == m_createMode) // 교차점에 오브젝트 생성
			{
				SP(Engine::CObject) spEmptyObject
					= m_pObjectFactory->AddClone(L"EmptyObject", true, (_int)ELayerID::Player, L"Kiana");

				spEmptyObject->AddComponent<Engine::CMeshC>()->AddMeshData(L"Kiana");
				spEmptyObject->GetComponent<Engine::CMeshC>()->SetInitTex(true);
				spEmptyObject->AddComponent<Engine::CTextureC>();
				spEmptyObject->AddComponent<Engine::CGraphicsC>()->SetRenderID((_int)Engine::ERenderID::NonAlpha);
				spEmptyObject->GetTransform()->SetSize(1, 1, 1);
				spEmptyObject->Awake();
				spEmptyObject->GetTransform()->SetPosition(intersection);

				std::cout << "create obj" << std::endl;
			}
			m_pCurSelectedObject = pTarget;
			std::wcout << pTarget->GetName() << std::endl;
		}
	}
}

void CEditorScene::InputSetting()
{
	// picking
	if (Engine::IMKEY_DOWN(KEY_Z))
	{
		m_pickingMode = !m_pickingMode;

		if (m_pickingMode)
			std::cout << "picking on" << std::endl;
		else
			std::cout << "picking off" << std::endl;
	}

	if (false == m_pCurSelectedObject)
		return;

	// delete
	if (Engine::IMKEY_DOWN(KEY_X))
	{
		m_pCurSelectedObject->SetDeleteThis(true);
		std::cout << "del" << std::endl;
		m_pCurSelectedObject = nullptr;
	}

	// create
	if (Engine::IMKEY_DOWN(KEY_F3))
	{
		if (false == m_createMode)
		{
			m_createMode = true;
			std::cout << "Create Mode On" << std::endl;
		}
		else if (true == m_createMode)
		{
			m_createMode = false;
			std::cout << "Create Mode Off" << std::endl;
		}
	}

	// pos
	if (Engine::IMKEY_DOWN(KEY_F5))
	{
		_float3 objPos = m_pCurSelectedObject->GetTransform()->GetPosition();
		m_pCurSelectedObject->GetTransform()->SetSize(objPos.x + 0.1f, objPos.y + 0.1f, objPos.z + 0.1f);
	}
	//else if (Engine::IMKEY_DOWN(KEY_F2))
	//{
	//	_float3 objPos = m_pCurSelectedObject->GetTransform()->GetPosition();
	//	m_pCurSelectedObject->GetTransform()->SetSize(objPos.x - 0.1f, objPos.y - 0.1f, objPos.z - 0.1f);
	//}

	// size
	if (Engine::IMKEY_DOWN(KEY_F1))
	{
		_float3 objSize = m_pCurSelectedObject->GetTransform()->GetSize();
		m_pCurSelectedObject->GetTransform()->SetSize(objSize.x + 0.1f, objSize.y + 0.1f, objSize.z + 0.1f);
	}
	else if (Engine::IMKEY_DOWN(KEY_F2))
	{
		_float3 objSize = m_pCurSelectedObject->GetTransform()->GetSize();
		m_pCurSelectedObject->GetTransform()->SetSize(objSize.x - 0.1f, objSize.y - 0.1f, objSize.z - 0.1f);
	}

	// rot
	if (Engine::IMKEY_DOWN(KEY_F3))
	{
		_float3 objRot = m_pCurSelectedObject->GetTransform()->GetRotation();
		m_pCurSelectedObject->GetTransform()->SetSize(objRot.x + 0.1f, objRot.y + 0.1f, objRot.z + 0.1f);
	}
	else if (Engine::IMKEY_DOWN(KEY_F4))
	{
		_float3 objRot = m_pCurSelectedObject->GetTransform()->GetRotation();
		m_pCurSelectedObject->GetTransform()->SetSize(objRot.x - 0.1f, objRot.y - 0.1f, objRot.z - 0.1f);
	}
}

Engine::CObject * CEditorScene::RayCast(_float3 origin, _float maxDistance, _float3 & intersection)
{
	_float t = FLT_MAX;
	_float3 tempIntersection = {};
	_bool checkFirstTime = true;

	Engine::CObject* pObject = nullptr;
	Engine::CMeshC* pMeshCom = nullptr;

	for (_int i = 0; i < (_int)ELayerID::NumOfLayerID; ++i)
	{
		auto& iter = m_vLayers[i]->GetGameObjects().begin();

		for (; iter != m_vLayers[i]->GetGameObjects().end();)
		{
			if (L"Camera0" == (*iter)->GetName())
			{
				++iter;
				continue;
			}

			_float tMin = 0;
			_float tMax = maxDistance;
			_float fU = 0.f, fV = 0.f, fT = 0.f;
			BOOL hit = false;
			DWORD dwFaceIndex = 0;

			_float3 direction = GetPickingDirection(origin, &(*iter)->GetTransform()->GetWorldMatrix());
			Engine::CMeshData* pMeshData = (*iter)->GetComponent<Engine::CMeshC>()->GetMeshDatas()[0];

			// 스태틱 메쉬
			if (0 == pMeshData->GetMeshType())
			{
				//ray와 메쉬 충돌 체크
				D3DXIntersect(
					static_cast<Engine::CStaticMeshData*>(pMeshData)->GetMesh(), // 해당 메쉬
					&origin, // 시작 위치
					&direction, // 방향
					&hit, // 충돌지점
					&dwFaceIndex, // 메쉬에서 충돌된 인덱스번호
					&fU, &fV, &fT, nullptr, nullptr); // fT는 거리
			}
			// 다이내믹 메쉬
			else if (1 == pMeshData->GetMeshType())
			{
				Engine::CDynamicMeshData* pDM = static_cast<Engine::CDynamicMeshData*>(pMeshData);
				size_t iSize = pDM->GetMeshContainers().size();

				for (size_t j = 0; j < iSize; ++j)
				{
					LPD3DXMESH pMesh = pDM->GetMeshContainers()[j]->MeshData.pMesh;

					// ray와 메쉬 충돌 체크
					D3DXIntersect(
						pMesh, // 해당 메쉬
						&origin, // 시작 위치
						&direction, // 방향
						&hit, // 충돌지점
						&dwFaceIndex, // 메쉬에서 충돌된 인덱스번호
						&fU, &fV, &fT, nullptr, nullptr); // fT는 거리

					if (hit)
						break;
				}
			}

			if (hit && fT <= tMax)
			{
				tempIntersection = origin + (fT * direction);

				if (checkFirstTime)
				{
					intersection = tempIntersection;
					checkFirstTime = false;
				}
				else if (Distance(origin, intersection) > Distance(origin, tempIntersection))
				{
					intersection = tempIntersection;
				}

				if (tMin < t)
				{
					t = tMin;
					pObject = iter->get();
					std::cout << "충돌됨" << std::endl;
					std::cout << "pos : " << (*iter)->GetTransform()->GetPosition().x << ", " << (*iter)->GetTransform()->GetPosition().y << ", " << (*iter)->GetTransform()->GetPosition().z << std::endl;
					std::cout << "inter : " << intersection.x << ", " << intersection.y << ", " << intersection.z << std::endl;
					break;
				}
			}

			++iter;
		}
	}
	 
	return pObject;
}

_float3 CEditorScene::GetPickingDirection(_float3 & origin, const _mat * pMatWorld)
{
	POINT pt;
	GetCursorPos(&pt);
	ScreenToClient(Engine::GET_HANDLE, &pt);
	
	/* 뷰포트 -> 투영스페이스 */
	_float3 mouse;
	mouse.x = pt.x / (VIEWCX * 0.5f) - 1.f;
	mouse.y = 1.f - pt.y / (VIEWCY * 0.5f);
	mouse.z = 0.f;
	
	/* 투영 -> 뷰 */
	_mat matInvProj;
	D3DXMatrixInverse(&matInvProj, 0, &Engine::GET_MAIN_CAM->GetProjMatrix());
	D3DXVec3TransformCoord(&mouse, &mouse, &matInvProj);
	
	_float3 rayDir = mouse;
	D3DXVec3Normalize(&rayDir, &rayDir);
	
	/* 투영스페이스 -> 월드스페이스 */
	_mat matInvView;
	D3DXMatrixInverse(&matInvView, 0, &Engine::GET_MAIN_CAM->GetViewMatrix());
	//D3DXVec3TransformCoord(&origin, &origin, &matInvView);
	D3DXVec3TransformNormal(&rayDir, &rayDir, &matInvView);
	D3DXVec3Normalize(&rayDir, &rayDir);
	
	/* 월드 -> 로컬 */
	_mat matInvWorld;
	D3DXMatrixInverse(&matInvWorld, 0, pMatWorld); // 피킹 대상의 월드
	D3DXVec3TransformCoord(&origin, &origin, &matInvWorld);
	D3DXVec3TransformNormal(&rayDir, &rayDir, &matInvWorld);
	D3DXVec3Normalize(&rayDir, &rayDir);
	
	return rayDir;
}

_float CEditorScene::Distance(_float3 & thisPosition, _float3 targetPosition)
{
	_float x = thisPosition.x - targetPosition.x;    // 선 a의 길이
	_float y = thisPosition.y - targetPosition.y;    // 선 b의 길이
	_float z = thisPosition.z - targetPosition.z;    // 선 b의 길이

	_float c = sqrt((x * x) + (y * y) + (z * z));
	return c;
}
