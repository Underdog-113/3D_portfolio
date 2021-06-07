#include "EngineStdafx.h"
#include "InputManager.h"
#include "WndApp.h"
#include "Object.h"
#include "Layer.h"
#include "StaticMeshData.h"
#include "DynamicMeshData.h"

USING(Engine)
IMPLEMENT_SINGLETON(CInputManager)

void CInputManager::Awake(void)
{
	__super::Awake();
}


void CInputManager::Start(void)
{
	m_mouseSensitivity = _float2(3.5f, 3.5f);
}

void CInputManager::FixedUpdate(void)
{
}

void CInputManager::Update(void)
{
	KeyUpdate();
	MouseUpdate();
}

void CInputManager::LateUpdate(void)
{
}

void CInputManager::OnDestroy(void)
{
}

void CInputManager::OnEnable(void)
{
}

void CInputManager::OnDisable(void)
{
}
bool CInputManager::KeyUp(DWORD key)
{
	if ((m_lastFrameKey & key) && !(m_key & key))
		return true;

	return false;
}

bool CInputManager::KeyDown(DWORD key)
{
	if (!(m_lastFrameKey & key) && (m_key & key))
		return true;

	return false;
}

bool CInputManager::KeyPress(DWORD key)
{
	if (m_key & key)
		return true;

	return false;
}


void CInputManager::KeyUpdate(void)
{
	m_lastFrameKey = m_key;
	m_key = 0;

	if (GetAsyncKeyState(VK_LEFT) & 0x8000)
		m_key |= KEY_LEFT;
	if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
		m_key |= KEY_RIGHT;
	if (GetAsyncKeyState(VK_UP) & 0x8000)
		m_key |= KEY_UP;
	if (GetAsyncKeyState(VK_DOWN) & 0x8000)
		m_key |= KEY_DOWN;
	if (GetAsyncKeyState(VK_SPACE) & 0x8000)
		m_key |= KEY_SPACE;
	if (GetAsyncKeyState(VK_CONTROL) & 0x8000)
		m_key |= KEY_CONTROL;
	if (GetAsyncKeyState(VK_F1) & 0x8000)
		m_key |= KEY_F1;
	if (GetAsyncKeyState(VK_F2) & 0x8000)
		m_key |= KEY_F2;
	if (GetAsyncKeyState(VK_F3) & 0x8000)
		m_key |= KEY_F3;
	if (GetAsyncKeyState(VK_F4) & 0x8000)
		m_key |= KEY_F4;
	if (GetAsyncKeyState(VK_F5) & 0x8000)
		m_key |= KEY_F5;
	if (GetAsyncKeyState(0x57) & 0x8000)
		m_key |= KEY_W;
	if (GetAsyncKeyState(0x41) & 0x8000)
		m_key |= KEY_A;
	if (GetAsyncKeyState(0x53) & 0x8000)
		m_key |= KEY_S;
	if (GetAsyncKeyState(0x44) & 0x8000)
		m_key |= KEY_D;
	if (GetAsyncKeyState('E') & 0x8000)
		m_key |= KEY_E;
	if (GetAsyncKeyState('Q') & 0x8000)
		m_key |= KEY_Q;
	if (GetAsyncKeyState('1') & 0x8000)
		m_key |= KEY_1;
	if (GetAsyncKeyState('2') & 0x8000)
		m_key |= KEY_2;
	if (GetAsyncKeyState('3') & 0x8000)
		m_key |= KEY_3;
	if (GetAsyncKeyState('4') & 0x8000)
		m_key |= KEY_4;
	if (GetAsyncKeyState('5') & 0x8000)
		m_key |= KEY_5;
	if (GetAsyncKeyState(VK_TAB) & 0x8000)
		m_key |= KEY_TAB;
	if (GetAsyncKeyState(VK_SHIFT) & 0x8000)
		m_key |= KEY_SHIFT;
	if (GetAsyncKeyState('Z') & 0x8000)
		m_key |= KEY_Z;
	if (GetAsyncKeyState('X') & 0x8000)
		m_key |= KEY_X;
}

void CInputManager::MouseUpdate(void)
{
	m_mouseLastFramePos = m_mousePos;

	POINT p;
	GetCursorPos(&p);
	ScreenToClient(GET_HANDLE, &p);

	m_mousePos = _float3((_float)p.x, (_float)p.y, 0);

	m_mousePos.x -= (GET_WND_WIDTH / 2.f);
	m_mousePos.y = (m_mousePos.y * -1) + GET_WND_HEIGHT / 2.f;

	if (GetAsyncKeyState(VK_LBUTTON) & 0x8000)
		m_key |= MOUSE_LEFT;
	if (GetAsyncKeyState(VK_RBUTTON) & 0x8000)
		m_key |= MOUSE_RIGHT;
}

void CInputManager::MoveMouseToCenter(void)
{
	m_mouseLastFramePos = m_mousePos;
	POINT mousePos = { GET_WND_WIDTH >> 1, GET_WND_HEIGHT >> 1 };;
	ClientToScreen(GET_HANDLE, &mousePos);
	SetCursorPos(mousePos.x, mousePos.y);

	m_mousePos = _float3(0, 0, 0);
}

CObject* CInputManager::MousePicking(_int layerID, _float3& intersection)
{
	_float3 rayStartPos = GET_MAIN_CAM->GetTransform()->GetPosition(); // 원점
	_float3 rayDir = GetPickingDirection(); // 방향

	_float t = FLT_MAX;
	CObject* pGameObject = nullptr;

	CLayer* pLayer = GET_CUR_SCENE->GetLayers()[layerID];

	for (auto& object : pLayer->GetGameObjects())
	{
		_float tMin = GET_MAIN_CAM->GetNear();
		_float tMax = GET_MAIN_CAM->GetFar(); // 거리

 		auto& pTransform = object->GetComponent<CTransformC>();

		_float3 minPos = _float3(-0.5f, -0.5f, -0.5f);
		_float3 maxPos = _float3(0.5f, 0.5f, 0.5f);

		D3DXVec3TransformCoord(&minPos, &minPos, &pTransform->GetWorldMatrix());
		D3DXVec3TransformCoord(&maxPos, &maxPos, &pTransform->GetWorldMatrix());


		if (!RayIntersectCheck(rayDir.x, rayStartPos.x, 
							   minPos.x, maxPos.x,
							   tMin, tMax))
			continue;
		if (!RayIntersectCheck(rayDir.y, rayStartPos.y, 
							   minPos.y, maxPos.y,
							   tMin, tMax))
			continue;
		if (!RayIntersectCheck(rayDir.z, rayStartPos.z, 
							   minPos.z, maxPos.z,
							   tMin, tMax))
			continue;

		if (tMin < t)
		{
			t = tMin;
			pGameObject = object.get();
		}
	}
	
	intersection = rayStartPos + t * rayDir;
	return pGameObject;
}

CObject * CInputManager::MousePickingLocal(_int layerID, _float3 & intersection)
{
	POINT pt;
	GetCursorPos(&pt);
	ScreenToClient(GET_HANDLE, &pt);

	/* 뷰포트 -> 투영스페이스 */
	_float3 mousePos;
	mousePos.x = pt.x / (GET_WND_WIDTH * 0.5f) - 1.f;
	mousePos.y = 1.f - pt.y / (GET_WND_HEIGHT * 0.5f);
	mousePos.z = 0.f;


	_mat invProjMat;
	D3DXMatrixInverse(&invProjMat, 0, &GET_MAIN_CAM->GetProjMatrix());
	D3DXVec3TransformCoord(&mousePos, &mousePos, &invProjMat);

	_float3 rayPos, rayDir;
	rayPos = ZERO_VECTOR;
	rayDir = mousePos - rayPos;
	D3DXVec3Normalize(&rayDir, &rayDir);

	_mat invViewMat;
	D3DXMatrixInverse(&invViewMat, 0, &GET_MAIN_CAM->GetViewMatrix());
	D3DXVec3TransformCoord(&rayPos, &rayPos, &invViewMat);
	D3DXVec3TransformNormal(&rayDir, &rayDir, &invViewMat);
	D3DXVec3Normalize(&rayDir, &rayDir);

	


	_float t = FLT_MAX;
	CObject* pObject = nullptr;
	

	_float tMin = GET_MAIN_CAM->GetNear();
	_float tMax = GET_MAIN_CAM->GetFar(); // 거리

	CLayer* pLayer = GET_CUR_SCENE->GetLayers()[layerID];
	for (auto& object : pLayer->GetGameObjects())
	{
		_mat invWorldMat;
		D3DXMatrixInverse(&invWorldMat, 0, &object->GetTransform()->GetLastWorldMatrix());
		D3DXVec3TransformCoord(&rayPos, &rayPos, &invWorldMat);
		D3DXVec3TransformNormal(&rayDir, &rayDir, &invWorldMat);
		D3DXVec3Normalize(&rayDir, &rayDir);

		_float fU, fV, fDist;
		DWORD _0, _1, _2;

		SP(CMeshC) spMesh = object->GetComponent<CMeshC>();
		
		for (auto& meshData : spMesh->GetMeshDatas())
		{
			if (meshData->GetMeshType() == (_int)EMeshType::Static)
			{
				CStaticMeshData* pSM = static_cast<CStaticMeshData*>(meshData);
				LPD3DXMESH pMesh = pSM->GetMesh();

				IDirect3DIndexBuffer9* pIndexBuffer;
				pMesh->GetIndexBuffer(&pIndexBuffer);
				
				D3DINDEXBUFFER_DESC indexBufferDesc;
				pIndexBuffer->GetDesc(&indexBufferDesc);

				void* pVertices;
				void* pIndices;
				pMesh->LockIndexBuffer(0, &pIndices);
				pMesh->LockVertexBuffer(0, &pVertices);

				D3DVERTEXELEMENT9 decl[MAX_FVF_DECL_SIZE];
				ZeroMemory(decl, sizeof(D3DVERTEXELEMENT9) * MAX_FVF_DECL_SIZE);
				pMesh->GetDeclaration(decl);

				_ubyte byOffset = 0;
				for (_ulong i = 0; i < MAX_FVF_DECL_SIZE; ++i)
				{
					if (decl[i].Usage == D3DDECLUSAGE_POSITION)
					{
						byOffset = (_ubyte)decl[i].Offset;
						break;
					}
				}
				_ulong FVF = pMesh->GetFVF();
				_uint stride = D3DXGetFVFVertexSize(FVF);

				

				for (_uint i = 0; i < pMesh->GetNumFaces(); ++i)
				{
					if (indexBufferDesc.Format == D3DFMT_INDEX16)
					{
						auto index = (INDEX16*)pIndices;
						_0 = index[i]._0;
						_1 = index[i]._1;
						_2 = index[i]._2;
					}
					else
					{
						auto index = (INDEX32*)pIndices;
						_0 = index[i]._0;
						_1 = index[i]._1;
						_2 = index[i]._2;
					}

					_float3 point[3];
					point[0] = *((_float3*)(((_ubyte*)pVertices) + (stride * _0 + byOffset)));
					point[1] = *((_float3*)(((_ubyte*)pVertices) + (stride * _1 + byOffset)));
					point[2] = *((_float3*)(((_ubyte*)pVertices) + (stride * _2 + byOffset)));

					if (D3DXIntersectTri(&point[0], &point[1], &point[2],
										 &rayPos, &rayDir,
										 &fU, &fV, &fDist))
					{
						if (fDist <= tMax && fDist >= tMin)
						{
							if (fDist < t)
							{
								t = fDist;
								intersection = point[0] + fU * (point[1] - point[0]) + fV * (point[2] - point[0]);
								D3DXVec3TransformCoord(&intersection, &intersection, &object->GetTransform()->GetLastWorldMatrix());
								pObject = object.get();
							}
						}
					}
				}

			}
			else
			{
				CDynamicMeshData* pDM = static_cast<CDynamicMeshData*>(meshData);

				for (_size i = 0; i < pDM->GetMeshContainers().size(); ++i)
				{
					LPD3DXMESH pMesh = pDM->GetMeshContainers()[i]->pOriMesh;

					IDirect3DIndexBuffer9* pIndexBuffer;
					pMesh->GetIndexBuffer(&pIndexBuffer);

					D3DINDEXBUFFER_DESC indexBufferDesc;
					pIndexBuffer->GetDesc(&indexBufferDesc);

					void* pVertices;
					void* pIndices;
					pMesh->LockIndexBuffer(0, &pIndices);
					pMesh->LockVertexBuffer(0, &pVertices);

					D3DVERTEXELEMENT9 decl[MAX_FVF_DECL_SIZE];
					ZeroMemory(decl, sizeof(D3DVERTEXELEMENT9) * MAX_FVF_DECL_SIZE);
					pMesh->GetDeclaration(decl);

					_ubyte byOffset = 0;
					for (_ulong j = 0; j < MAX_FVF_DECL_SIZE; ++j)
					{
						if (decl[j].Usage == D3DDECLUSAGE_POSITION)
						{
							byOffset = (_ubyte)decl[j].Offset;
							break;
						}
					}
					_ulong FVF = pMesh->GetFVF();
					_uint stride = D3DXGetFVFVertexSize(FVF);


					_uint faceNum = pMesh->GetNumFaces();
					for (_uint j = 0; j < pMesh->GetNumFaces(); ++j)
					{
						if (indexBufferDesc.Format == D3DFMT_INDEX16)
						{
							auto index = (INDEX16*)pIndices;
							_0 = index[j]._0;
							_1 = index[j]._1;
							_2 = index[j]._2;
						}
						else
						{
							auto index = (INDEX32*)pIndices;
							_0 = index[j]._0;
							_1 = index[j]._1;
							_2 = index[j]._2;
						}

						_float3 point[3];
						point[0] = *((_float3*)(((_ubyte*)pVertices) + (stride * _0 + byOffset)));
						point[1] = *((_float3*)(((_ubyte*)pVertices) + (stride * _1 + byOffset)));
						point[2] = *((_float3*)(((_ubyte*)pVertices) + (stride * _2 + byOffset)));

						if (D3DXIntersectTri(&point[0], &point[1], &point[2],
							&rayPos, &rayDir,
							&fU, &fV, &fDist))
						{
							if (fDist <= tMax && fDist >= tMin)
							{
								if (fDist < t)
								{
									t = fDist;
									intersection = point[0] + fU * (point[1] - point[0]) + fV * (point[2] - point[0]);
									D3DXVec3TransformCoord(&intersection, &intersection, &object->GetTransform()->GetLastWorldMatrix());
									pObject = object.get();
								}
							}
						}
					}
				}
			}
		}
	}




	return pObject;
}

_float3 CInputManager::GetMousePosDelta(void)
{
	return (m_mousePos - m_mouseLastFramePos);
}

void CInputManager::ResetMousePosDelta(void)
{
	m_mouseLastFramePos = m_mousePos;
}


_float3 CInputManager::GetPickingDirection(void)
{
	POINT pt;
	GetCursorPos(&pt);
	ScreenToClient(GET_HANDLE, &pt);

	/* 뷰포트 -> 투영스페이스 */
	_float3 vMouse;
	vMouse.x = pt.x / (GET_WND_WIDTH * 0.5f) - 1.f;
	vMouse.y = 1.f - pt.y / (GET_WND_HEIGHT * 0.5f);
	vMouse.z = 0.f;

	_mat matInvProj;
	D3DXMatrixInverse(&matInvProj, 0, &GET_MAIN_CAM->GetProjMatrix());
	D3DXVec3TransformCoord(&vMouse, &vMouse, &matInvProj);

	_float3 rayDir = vMouse;
	D3DXVec3Normalize(&rayDir, &rayDir);

	_mat matInvView;
	D3DXMatrixInverse(&matInvView, 0, &GET_MAIN_CAM->GetViewMatrix());
	D3DXVec3TransformNormal(&rayDir, &rayDir, &matInvView);
	D3DXVec3Normalize(&rayDir, &rayDir);


	return rayDir;
}

_bool CInputManager::RayIntersectCheck(_float rayAxisDir, _float rayAxisStart, 
									   _float aabbAxisMin, _float aabbAxisMax, 
									   _float& tMin, _float& tMax)
{
	if (abs(rayAxisDir) < EPSILON)
	{
		//no hit if origin not within axis
		if (rayAxisStart < aabbAxisMin || rayAxisStart > aabbAxisMax)
			return false;
	}
	else
	{
		//compute intersection t value of near and far plane of axis
		float ood = 1.f / rayAxisDir;
		float t1 = (aabbAxisMin - rayAxisStart) * ood;
		float t2 = (aabbAxisMax - rayAxisStart) * ood;
		//make t1 be intersection with near plane, t2 with far
		if (t1 > t2)
		{
			_float temp = t1;
			t1 = t2;
			t2 = temp;
		}

		//compute intersection on axis 
		if (t1 > tMin)
			tMin = t1;
		if (t2 < tMax)
			tMax = t2;

		//Exit with no collision as soon as intersection becomes empty
		if (tMin > tMax)
			return false;
	}

	return true;
}

