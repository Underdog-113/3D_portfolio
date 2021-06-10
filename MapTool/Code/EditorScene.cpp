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

#include "DynamicMeshData.h"
#include "DebugCollider.h"

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
	m_pDataStore->AddDataSection(L"Enemy", (_uint)EDataID::Enemy);
	m_pDataStore->AddDataSection(L"UI", (_uint)EDataID::UI);

	m_pDataStore->InitDataForScene(L"StaticScene", true);
	m_pMeshStore->InitMeshForScene(L"StaticScene", true);
	m_pTextureStore->InitTextureForScene(L"StaticScene", true);

	m_pDataStore->InitDataForScene(m_objectKey);
	m_pMeshStore->InitMeshForScene(m_objectKey);
	m_pTextureStore->InitTextureForScene(m_objectKey);

	InitPrototypes();

	m_pMain = dynamic_cast<CMainFrame*>(::AfxGetApp()->GetMainWnd());
	m_pMainView = dynamic_cast<CMapToolView*>(m_pMain->GetMainSplitter().GetPane(0, 0));
	m_pMenuView = dynamic_cast<CToolMenuView*>(m_pMain->GetMainSplitter().GetPane(0, 1));
}

void CEditorScene::Start(void)
{
	__super::Start();

	SP(Engine::CObject) spCube
		= m_pObjectFactory->AddClone(L"EmptyObject", true, (_int)ELayerID::Map, L"Cube0");

	spCube->AddComponent<Engine::CMeshC>()->AddMeshData(L"tes3t");
	spCube->GetComponent<Engine::CMeshC>()->SetInitTex(true);
	spCube->AddComponent<Engine::CTextureC>()/*->AddTexture(L"Castle_wall", 0)*/;
	spCube->AddComponent<Engine::CGraphicsC>()->SetRenderID((_int)Engine::ERenderID::NonAlpha);
	spCube->AddComponent<Engine::CShaderC>()->AddShader((_int)Engine::EShaderID::MeshShader);
	//spCube->GetTransform()->SetSize(300, 1, 300);
	spCube->GetTransform()->SetSize(5, 5, 5);
	spCube->GetTransform()->SetPosition(0.f, -1.f, 0.f);
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

bool CEditorScene::IsObjectPicked(Engine::CObject * _pObject, _float3 * _pOutPickPoint)
{
	_float3 rayPos, rayDir;
	GetMouseRay(_pObject->GetTransform()->GetWorldMatrix(), &rayPos, &rayDir);

	m_rayDir = rayDir;

	D3DXVec3TransformCoord(&rayPos, &rayPos, &_pObject->GetTransform()->GetWorldMatrix());
	D3DXVec3TransformNormal(&rayDir, &rayDir, &_pObject->GetTransform()->GetWorldMatrix());

	D3DXVec3Normalize(&rayDir, &rayDir);

	_float3 modifyPos = _pObject->GetTransform()->GetPosition();
	modifyPos.y += _pObject->GetComponent<Engine::CMeshC>()->GetHalfYOffset();

	_float3 objCenterRay = (modifyPos) - rayPos;
	D3DXVec3Normalize(&objCenterRay, &objCenterRay);
	_float cosValue = D3DXVec3Dot(&objCenterRay, &rayDir);
	_float radian = acosf(cosValue);

	objCenterRay = _pObject->GetTransform()->GetPosition() - rayPos;
	_float len = D3DXVec3Length(&objCenterRay);
	_float dist = len * sinf(radian);


	if (dist < m_pickRadius)
		return true;
	else
		return false;
}

bool CEditorScene::IsMeshPicked(Engine::CObject * _pObject, _float3 * _pOutPickPoint)
{
	_float3 rayPos, rayDir;
	GetMouseRay(_pObject->GetTransform()->GetWorldMatrix(), &rayPos, &rayDir);

	m_rayDir = rayDir;

	Engine::CStaticMeshData* pStaticMesh = (Engine::CStaticMeshData*)_pObject->GetComponent<Engine::CMeshC>()->GetMeshDatas()[0];

	return CheckIntersect(pStaticMesh->GetMesh(), rayPos, rayDir, _pOutPickPoint);
}

bool CEditorScene::CheckIntersect(LPD3DXMESH _mesh, _float3 _rayPos, _float3 _rayDir, _float3 * _pOutPickPoint)
{
	LPDIRECT3DVERTEXBUFFER9 pVertexBuffer;
	LPDIRECT3DINDEXBUFFER9 pIndexBuffer;

	WORD* pIndices;
	Engine::VERTEX_VNT* pVertices;

	_float u, v, distance;
	_float minDistance = FLT_MAX;

	_mesh->GetVertexBuffer(&pVertexBuffer);
	_mesh->GetIndexBuffer(&pIndexBuffer);

	pIndexBuffer->Lock(0, 0, (void**)&pIndices, 0);
	pVertexBuffer->Lock(0, 0, (void**)&pVertices, 0);

	for (_uint i = 0; i < _mesh->GetNumFaces(); ++i)
	{
		_float3 p0 = pVertices[pIndices[3 * i + 0]].position;
		_float3 p1 = pVertices[pIndices[3 * i + 1]].position;
		_float3 p2 = pVertices[pIndices[3 * i + 2]].position;

		if (D3DXIntersectTri(
			&p0,
			&p1,
			&p2,
			&_rayPos, &_rayDir, &u, &v, &distance))
		{
			if (distance < minDistance)
			{
				minDistance = distance;
				*_pOutPickPoint = p0 + u*(p1 - p0) + v*(p2 - p0);
			}
		}
	}

	if (minDistance == FLT_MAX)
		return false;
	else
		return true;
}
void CEditorScene::GetMouseRay(_mat _targetWorldMatrix, _float3 * _pOutRayPos, _float3 * _pOutRayDir)
{
	D3DVIEWPORT9 ViewPort;
	ZeroMemory(&ViewPort, sizeof(D3DVIEWPORT9));

	Engine::GET_DEVICE->GetViewport(&ViewPort);

	POINT mousePoint{};

	GetCursorPos(&mousePoint);
	ScreenToClient(m_pMainView->m_hWnd, &mousePoint);

	RECT winRect;
	m_pMainView->GetClientRect(&winRect);
	if (mousePoint.x < winRect.left || mousePoint.x > winRect.right ||
		mousePoint.y < winRect.top || mousePoint.y > winRect.bottom)
		return;

	mousePoint.x = LONG((float)mousePoint.x / (float)(winRect.right - winRect.left) * (float)ViewPort.Width);
	mousePoint.y = LONG((float)mousePoint.y / (float)(winRect.bottom - winRect.top) * (float)ViewPort.Height);

	// viewport -> projection
	_float3 mousePos;

	mousePos.x = mousePoint.x / (ViewPort.Width * 0.5f) - 1.f;
	mousePos.y = mousePoint.y / (ViewPort.Height * -0.5f) + 1.f;
	mousePos.z = 0.f;

	// projection -> view
	_mat projMat = Engine::GET_MAIN_CAM->GetProjMatrix();
	D3DXMatrixInverse(&projMat, NULL, &projMat);
	D3DXVec3TransformCoord(&mousePos, &mousePos, &projMat);

	// view -> world
	*_pOutRayPos = _float3(0.f, 0.f, 0.f);
	*_pOutRayDir = mousePos - *_pOutRayPos;
	D3DXVec3Normalize(_pOutRayDir, _pOutRayDir);

	_mat viewMat = Engine::GET_MAIN_CAM->GetViewMatrix();
	D3DXMatrixInverse(&viewMat, NULL, &viewMat);

	D3DXVec3TransformCoord(_pOutRayPos, _pOutRayPos, &viewMat);
	D3DXVec3TransformNormal(_pOutRayDir, _pOutRayDir, &viewMat);
	D3DXVec3Normalize(_pOutRayDir, _pOutRayDir);

	// world -> local
	D3DXMatrixInverse(&_targetWorldMatrix, NULL, &_targetWorldMatrix);

	D3DXVec3TransformCoord(_pOutRayPos, _pOutRayPos, &_targetWorldMatrix);
	D3DXVec3TransformNormal(_pOutRayDir, _pOutRayDir, &_targetWorldMatrix);
	D3DXVec3Normalize(_pOutRayDir, _pOutRayDir);
}

void CEditorScene::SetInitAnimation(SP(Engine::CObject) spObj)
{
	std::wstring meshKey = spObj->GetComponent<Engine::CMeshC>()->GetMeshDatas()[0]->GetMeshKey();

	if (L"Kiana" == meshKey)
		static_cast<Engine::CDynamicMeshData*>(spObj->GetComponent<Engine::CMeshC>()->GetMeshDatas()[0])->ChangeAniSet("StandBy");

	else if (L"Theresa" == meshKey)
		static_cast<Engine::CDynamicMeshData*>(spObj->GetComponent<Engine::CMeshC>()->GetMeshDatas()[0])->ChangeAniSet("IDLE");

	else if (L"Sakura" == meshKey)
		static_cast<Engine::CDynamicMeshData*>(spObj->GetComponent<Engine::CMeshC>()->GetMeshDatas()[0])->ChangeAniSet("ui_standby");

	else if (L"MB_Ganesha" == meshKey)
		static_cast<Engine::CDynamicMeshData*>(spObj->GetComponent<Engine::CMeshC>()->GetMeshDatas()[0])->ChangeAniSet("StandBy");

	else if (L"MB_Bronya" == meshKey)
		static_cast<Engine::CDynamicMeshData*>(spObj->GetComponent<Engine::CMeshC>()->GetMeshDatas()[0])->ChangeAniSet("IDLE");

	else if (L"MO_Ninza" == meshKey)
		static_cast<Engine::CDynamicMeshData*>(spObj->GetComponent<Engine::CMeshC>()->GetMeshDatas()[0])->ChangeAniSet("standy");

	else if (L"MO_Robot" == meshKey)
		static_cast<Engine::CDynamicMeshData*>(spObj->GetComponent<Engine::CMeshC>()->GetMeshDatas()[0])->ChangeAniSet("StandBy");

	else if (L"MO_Scout" == meshKey)
		static_cast<Engine::CDynamicMeshData*>(spObj->GetComponent<Engine::CMeshC>()->GetMeshDatas()[0])->ChangeAniSet("IDLE");

	else if (L"MO_Spider" == meshKey)
		static_cast<Engine::CDynamicMeshData*>(spObj->GetComponent<Engine::CMeshC>()->GetMeshDatas()[0])->ChangeAniSet("StandBy");

	else if (L"MO_Lancer" == meshKey)
		static_cast<Engine::CDynamicMeshData*>(spObj->GetComponent<Engine::CMeshC>()->GetMeshDatas()[0])->ChangeAniSet("STAND");
}

void CEditorScene::InitPrototypes(void)
{
	SP(Engine::CObject) spEmptyObjectPrototype(Engine::CEmptyObject::Create(true, this));
	ADD_PROTOTYPE(spEmptyObjectPrototype);

	SP(Engine::CDebugCollider) spDebugColliderPrototype(Engine::CDebugCollider::Create(true, this));
	ADD_PROTOTYPE(spDebugColliderPrototype);

	SP(Engine::CCamera) spCameraPrototype(Engine::CCamera::Create(true, this));
	ADD_PROTOTYPE(spCameraPrototype);
}

void CEditorScene::InputSetting()
{
	if (Engine::IMKEY_DOWN(KEY_Q))
	{
		if (false == m_pickingMode)
		{
			m_pickingMode = true;
			std::cout << "Create Mode On" << std::endl;
		}
		else if (true == m_pickingMode)
		{
			m_pickingMode = false;
			std::cout << "Create Mode Off" << std::endl;
		}
	}

	if (Engine::IMKEY_DOWN(MOUSE_RIGHT))
	{
		//if (true == m_createMode) // 클릭시 오브젝트 생성
		//{
			_float3 intersection;
			_float shortLen = 1000.f;

			Engine::CObject* pTarget = nullptr;

			for (auto& pObject : m_vLayers[(_int)ELayerID::Map]->GetGameObjects())
			{
				_float3 pickPoint = ZERO_VECTOR;

				if (IsMeshPicked(pObject.get(), &pickPoint))
				{
					_float3 correctPoint = ZERO_VECTOR;
					D3DXVec3TransformCoord(&correctPoint, &pickPoint, &pObject.get()->GetTransform()->GetWorldMatrix());
					
					_float3 camPos = Engine::GET_MAIN_CAM->GetTransform()->GetPosition();
					_float len = D3DXVec3Length(&_float3(correctPoint - camPos));

					if (len < shortLen)
					{
						pTarget = pObject.get();
						shortLen = len;
						intersection = correctPoint;
						m_intersect = intersection;
					}
				}
			}

			std::wstring fileName(m_pMenuView->GetCurSelFileName());

			CString cstr;
			ELayerID curLayerID = ELayerID::NumOfLayerID;
			m_pMenuView->m_layerID.GetLBText(m_pMenuView->m_layerID.GetCurSel(), cstr);

			if (L"Player" == cstr)
				curLayerID = ELayerID::Player;
			else if (L"Enemy" == cstr)
				curLayerID = ELayerID::Enemy;
			else if (L"Map" == cstr)
				curLayerID = ELayerID::Map;

			SP(Engine::CObject) spObj = m_pObjectFactory->AddClone(L"EmptyObject", true, (_int)curLayerID, L"hi");
			spObj->AddComponent<Engine::CMeshC>()->AddMeshData(Engine::RemoveExtension(fileName));

			if (1 == m_pMenuView->m_initTexture.GetCheck())
			{
				spObj->GetComponent<Engine::CMeshC>()->SetInitTex(true);
				spObj->AddComponent<Engine::CTextureC>();
			}
			else if (0 == m_pMenuView->m_initTexture.GetCheck())
			{
				spObj->GetComponent<Engine::CMeshC>()->SetInitTex(false);
				spObj->AddComponent<Engine::CTextureC>()->AddTexture(Engine::StrToWStr(CStrToStr(m_pMenuView->GetCurSelTextureFileName())), 0);
			}

			spObj->AddComponent<Engine::CGraphicsC>()->SetRenderID((_int)Engine::ERenderID::NonAlpha);
			spObj->GetTransform()->SetSize(10, 10, 10);
			spObj->GetTransform()->SetPosition(intersection);

			SetInitAnimation(spObj);

			m_pCurSelectedObject = spObj.get();
			m_pMenuView->m_curObjName.SetWindowTextW(m_pCurSelectedObject->GetName().c_str());

			// add collider
			CString cstrVal;
			m_pMenuView->m_colliderID.GetLBText(m_colliderID.GetCurSel(), cstrVal);

			std::string str = CStrToStr(cstrVal);
			std::wstring wstr = Engine::StrToWStr(str);
	}
//}

	if (Engine::IMKEY_DOWN(MOUSE_LEFT))
	{
		Engine::CObject* pTarget = nullptr;
		_float shortLen = 1000.f;

		for (auto& pLayer : m_vLayers)
		{
			for (auto pObject : pLayer->GetGameObjects())
			{
				if (pObject->GetLayerID() == (_int)Engine::ELayerID::Camera)
					continue;

				_float3 pickPoint = ZERO_VECTOR;

				if (IsObjectPicked(pObject.get(), &pickPoint))
				{
					_float3 correctPoint = ZERO_VECTOR;
					D3DXVec3TransformCoord(&correctPoint, &pickPoint, &pObject.get()->GetTransform()->GetWorldMatrix());

					_float3 camPos = Engine::GET_MAIN_CAM->GetTransform()->GetPosition();
					_float len = D3DXVec3Length(&_float3(correctPoint - camPos));

					if (len < shortLen)
					{
						pTarget = pObject.get();
						shortLen = len;
					}
				}
			}
		}

		if (nullptr != pTarget)
		{
			if (L"Cube0" == pTarget->GetName())
				return;

			m_pCurSelectedObject = pTarget;
			m_pMenuView->m_curObjName.SetWindowTextW(m_pCurSelectedObject->GetName().c_str());
			std::wcout << pTarget->GetName() << std::endl;

			m_pMenuView->SetPosition(m_pCurSelectedObject->GetTransform()->GetPosition());
			m_pMenuView->SetRotation(m_pCurSelectedObject->GetTransform()->GetRotation());
			m_pMenuView->SetScale(m_pCurSelectedObject->GetTransform()->GetSize());

			if (nullptr == m_pCurSelectedObject->GetComponent<Engine::CCollisionC>())
				m_pMenuView->m_addCollisionC.EnableWindow(true);
			else
				m_pMenuView->m_addCollisionC.EnableWindow(false);
		}
		//else
		//	std::wcout << "target not found" << std::endl;
	}

	// create
	//if (Engine::IMKEY_DOWN(KEY_E))
	//{
	//	if (false == m_createMode)
	//	{
	//		m_createMode = true;
	//		std::cout << "Create mode on" << std::endl;
	//	}
	//	else
	//	{
	//		m_createMode = false;
	//		std::cout << "Create mode off" << std::endl;
	//	}
	//}

	// delete
	if (nullptr != m_pCurSelectedObject && Engine::IMKEY_DOWN(KEY_R))
	{
		m_pCurSelectedObject->SetDeleteThis(true);
		std::cout << "del" << std::endl;
		m_pCurSelectedObject = nullptr;
	}
}
