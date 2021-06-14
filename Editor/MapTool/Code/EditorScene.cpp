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
#include "StageController_Editor.h"

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

	//SP(Engine::CObject) spBaseMap
	//	= m_pObjectFactory->AddClone(L"EmptyObject", true, (_int)ELayerID::Map, L"BaseMap");

	//spBaseMap->AddComponent<Engine::CMeshC>()->AddMeshData(L"Stage02_NonAlpha_Deco");
	//spBaseMap->GetComponent<Engine::CMeshC>()->SetInitTex(true);
	//spBaseMap->AddComponent<Engine::CTextureC>()/*->AddTexture(L"Castle_wall", 0)*/;
	//spBaseMap->AddComponent<Engine::CGraphicsC>()->SetRenderID((_int)Engine::ERenderID::NonAlpha);
	//spBaseMap->GetComponent<Engine::CGraphicsC>()->SetColorReverse(false);
	//spBaseMap->AddComponent<Engine::CShaderC>()->AddShader((_int)Engine::EShaderID::MeshShader);
	//spCube->GetTransform()->SetSize(300, 1, 300);
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
	CStageController_Editor::GetInstance()->Update();
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

	m_pickRadius = _pObject->GetTransform()->GetSize().x * 0.3f;

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

void CEditorScene::SetPickingMode()
{
	if (Engine::IMKEY_DOWN(KEY_Q))
	{
		if (false == m_pickingMode)
		{
			m_pickingMode = true;
			std::cout << "Picking Mode On" << std::endl;
		}
		else if (true == m_pickingMode)
		{
			m_pickingMode = false;
			std::cout << "Picking Mode Off" << std::endl;
		}
	}
}

void CEditorScene::SetCreateObject()
{
	if (Engine::IMKEY_DOWN(MOUSE_RIGHT))
	{
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

				//<< << << < HEAD
					if (len < shortLen)
					{
						pTarget = pObject.get();
						shortLen = len;
						intersection = correctPoint;
						m_intersect = intersection;
					}
				//== == == =
			//SetInitAnimation(spObj);

			//m_pCurSelectedObject = spObj.get();
			//m_pMenuView->m_curObjName.SetWindowTextW(m_pCurSelectedObject->GetName().c_str());

			//// add collider
			//CString cstrVal;
			//m_pMenuView->m_colliderID.GetLBText(m_pMenuView->m_colliderID.GetCurSel(), cstrVal);

			//std::string str = CStrToStr(cstrVal);
			//std::wstring wstr = Engine::StrToWStr(str);
			//_int colID = 0;

			//if (L"" == wstr)
			//	return;
			//else if (L"Player" == wstr)
			//	colID = (_int)ECollisionID::Player;
			//else if (L"Enemy" == wstr)
			//	colID = (_int)ECollisionID::Enemy;
			//else if (L"Object" == wstr)
			//	colID = (_int)ECollisionID::Object;
			//else if (L"Map" == wstr)
			//	colID = (_int)ECollisionID::Map;

			//m_pCurSelectedObject->AddComponent<Engine::CCollisionC>()->SetCollisionID(colID);
			//m_pCurSelectedObject->AddComponent<Engine::CDebugC>();

			////m_pMenuView->m_showCol.EnableWindow(true);
			//m_pMenuView->m_colType[0].EnableWindow(true);
			//m_pMenuView->m_colType[1].EnableWindow(true);

			////
			//_float3 size = _float3(1, 1, 1);
			//_float3 offset = ZERO_VECTOR;

			//if (1 == m_pMenuView->m_colType[0].GetCheck())
			//{
			//	m_pCurSelectedObject->GetComponent<Engine::CCollisionC>()->AddCollider(Engine::CAabbCollider::Create(size, offset));
			//	std::cout << "add aabb collider" << std::endl;
//>>>>>>> 0be8f21ad0ba9e8d3eae8a19b9ea9d71b985be08
			}
		}

		CString cstrLayerID;
		CString cstrName;
		
		ELayerID curLayerID = ELayerID::NumOfLayerID;
		m_pMenuView->m_layerID.GetLBText(m_pMenuView->m_layerID.GetCurSel(), cstrLayerID);
		m_pMenuView->m_curObjName.GetWindowTextW(cstrName);

		if (L"Player" == cstrLayerID)
			curLayerID = ELayerID::Player;
		else if (L"Enemy" == cstrLayerID)
			curLayerID = ELayerID::Enemy;
		else if (L"Map" == cstrLayerID)
			curLayerID = ELayerID::Map;

		CreateObject(true, curLayerID, CStrToWStr(cstrName), _float3(1.f, 1.f, 1.f), intersection);
	}
}

void CEditorScene::SetPickObject()
{
	if (Engine::IMKEY_DOWN(MOUSE_LEFT))
	{
		if (false == m_pickingMode)
			return;

		Engine::CObject* pTarget = nullptr;
		_float shortLen = 1000.f;

		for (auto& pLayer : m_vLayers)
		{
			for (auto pObject : pLayer->GetGameObjects())
			{
				if (pObject->GetLayerID() == (_int)Engine::ELayerID::Camera)
					continue;

				if (L"DebugCollider" == pObject->GetObjectKey())
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
			if (L"BaseMap" == pTarget->GetName())
				return;

			if (nullptr != m_pCurSelectedObject)
				m_pCurSelectedObject->GetComponent<Engine::CGraphicsC>()->SetColorReverse(false);

			m_pCurSelectedObject = pTarget;
			m_pCurSelectedObject->GetComponent<Engine::CGraphicsC>()->SetColorReverse(true);
			m_pMenuView->m_curObjName.SetWindowTextW(m_pCurSelectedObject->GetName().c_str());
			m_pMenuView->m_curObjNameChk.SetCheck(1);

			CString str;
			std::wstring wstr;

			_int total = m_pMenuView->m_objList.GetCount();

			for (_int i = 0; i < total; ++i)
			{
				m_pMenuView->m_objList.GetText(i, str);
				wstr = CStrToWStr(str);

				if (wstr == m_pCurSelectedObject->GetName())
					m_pMenuView->m_objList.SetCurSel(i);
			}

			std::wcout << pTarget->GetName() << std::endl;

			m_pMenuView->SetPosition(m_pCurSelectedObject->GetTransform()->GetPosition());
			m_pMenuView->SetRotation(m_pCurSelectedObject->GetTransform()->GetRotation());
			m_pMenuView->SetScale(m_pCurSelectedObject->GetTransform()->GetSize());

			if (false == m_pCurSelectedObject->GetIsEnabled())
				m_pMenuView->m_showObjectChk.SetCheck(0);
			else if (true == m_pCurSelectedObject->GetIsEnabled())
				m_pMenuView->m_showObjectChk.SetCheck(1);

			if (nullptr != m_pCurSelectedObject->GetComponent<Engine::CCollisionC>())
			{
				m_pMenuView->m_addColC.EnableWindow(false);
				m_pMenuView->m_colType[0].EnableWindow(true);
				m_pMenuView->m_colType[1].EnableWindow(true);
				m_pMenuView->m_colType[2].EnableWindow(true);
			}
			else
			{
				m_pMenuView->m_addColC.EnableWindow(true);
				m_pMenuView->m_colType[0].EnableWindow(false);
				m_pMenuView->m_colType[1].EnableWindow(false);
				m_pMenuView->m_colType[2].EnableWindow(false);
				m_pMenuView->m_showAllCol.EnableWindow(false);
			}

			CStageController_Editor::GetInstance()->SetCurrentActor(m_pCurSelectedObject);

			m_pMenuView->m_aabbCnt.ResetContent();

			// collision cnt reset
			if (nullptr != m_pCurSelectedObject->GetComponent<Engine::CCollisionC>())
			{
				_int idx = 0;

				auto& vCol = m_pCurSelectedObject->GetComponent<Engine::CCollisionC>()->GetColliders();
				auto& col = vCol.begin();

				for (; col != vCol.end(); ++col)
				{
					if (3 == (*col)->GetColliderType())
					{
						m_pMenuView->m_aabbCnt.AddString(IntToCStr(idx));
					}
					++idx;
				}
			}
		}
	}
}

void CEditorScene::SetDeleteObject()
{
	if (nullptr != m_pCurSelectedObject && Engine::IMKEY_DOWN(KEY_R))
	{
		m_pMenuView->OnBnClickedDelObjectWithObjList();

		//m_pCurSelectedObject->SetDeleteThis(true);
		//std::cout << "del" << std::endl;
		//m_pCurSelectedObject = nullptr;
	}
}

void CEditorScene::SetLastDeleteObject()
{
	// delete last created object
	if (Engine::IMKEY_DOWN(MOUSE_WHEEL))
	{
		m_vLayers[(_int)ELayerID::Map]->GetGameObjects().back()->GetDeleteThis();
		std::cout << "delete last object" << std::endl;
	}
}

void CEditorScene::CreateObject(_bool isStatic, ELayerID layerID, std::wstring objName, _float3 size, _float3 intersection)
{
	std::wstring fileName(m_pMenuView->GetCurSelFileName());

	SP(Engine::CObject) spObj = m_pObjectFactory->AddClone(L"EmptyObject", isStatic, (_int)layerID, objName);

	spObj->AddComponent<Engine::CMeshC>()->AddMeshData(Engine::RemoveExtension(fileName));

	if (1 == m_pMenuView->m_initTexture.GetCheck())
	{
		spObj->GetComponent<Engine::CMeshC>()->SetInitTex(true);

		if (Engine::RemoveExtension(fileName) != L"Cube")
			spObj->AddComponent<Engine::CTextureC>();
		else
			spObj->AddComponent<Engine::CTextureC>()->AddTexture(L"Castle_wall", 0);
	}
	else if (0 == m_pMenuView->m_initTexture.GetCheck())
	{
		spObj->GetComponent<Engine::CMeshC>()->SetInitTex(false);
		spObj->AddComponent<Engine::CTextureC>()->AddTexture(Engine::StrToWStr(CStrToStr(m_pMenuView->GetCurSelTextureFileName())), 0);
	}

	switch (m_pMenuView->m_renderAlpha.GetCheck())
	{
	case 0:
		spObj->AddComponent<Engine::CGraphicsC>()->SetRenderID((_int)Engine::ERenderID::NonAlpha);
		break;
	case 1:
		spObj->AddComponent<Engine::CGraphicsC>()->SetRenderID((_int)Engine::ERenderID::AlphaTest);
		break;
	}

	spObj->GetComponent<Engine::CGraphicsC>()->SetColorReverse(true);
	spObj->AddComponent<Engine::CShaderC>()->AddShader((_int)Engine::EShaderID::MeshShader);
	spObj->GetTransform()->SetSize(size);
	spObj->GetTransform()->SetPosition(intersection);

	SetInitAnimation(spObj);

	if (nullptr != m_pCurSelectedObject)
		m_pCurSelectedObject->GetComponent<Engine::CGraphicsC>()->SetColorReverse(false);

	m_pCurSelectedObject = spObj.get();
	m_pCurSelectedObject->SetLayerID((_int)layerID);
	m_pMenuView->m_curObjName.SetWindowTextW(m_pCurSelectedObject->GetName().c_str());

	m_pMenuView->m_renderAlpha.SetCheck(0);
	std::cout << "Create!" << std::endl;

	// add to obj in list
	m_pMenuView->m_objList.AddString(m_pCurSelectedObject->GetName().c_str());
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
	if (Engine::IMKEY_DOWN(KEY_F5))
	{
		if (true == m_stopAllKey)
		{
			m_stopAllKey = false;
			std::cout << "InputSetting off" << std::endl;
		}
		else if (false == m_stopAllKey)
		{
			m_stopAllKey = true;
			std::cout << "InputSetting on" << std::endl;
		}
	}

	SetPickingMode(); // key q
	SetCreateObject(); // mouse r
	SetPickObject(); // mouse l
	SetDeleteObject(); // key r
	SetLastDeleteObject(); // mouse wheel
}
