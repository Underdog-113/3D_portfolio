#pragma once
#include "Scene.h"

class Engine::CCamera;
class Engine::CObject;

class CEditorScene final : public Engine::CScene
{
private:
	explicit CEditorScene(void);
	~CEditorScene(void);

public:
	static Engine::CScene* Create(void);
	void Free(void) override;
		 
	void Awake(_int numOfLayers) override;
	void Start(void) override;
		 
	void FixedUpdate(void) override;
	void Update(void) override;
	void LateUpdate(void) override;
		 
	void OnDestroy(void) override;
		 
	void OnEnable(void) override;
	void OnDisable(void) override;
	
private:
	bool IsObjectPicked(Engine::CObject* _pObject, _float3* _pOutPickPoint);
	bool IsMeshPicked(Engine::CObject * _pObject, _float3 * _pOutPickPoint);
	bool CheckIntersect(LPD3DXMESH _mesh, _float3 _rayPos, _float3 _rayDir, _float3* _pOutPickPoint);
	void GetMouseRay(_mat _targetWorldMatrix, _float3 * _pOutRayPos, _float3 * _pOutRayDir);
	void SetInitAnimation(SP(Engine::CObject) spObj);

public:
	void CreateObject(_bool isStatic, ELayerID layerID, std::wstring objName, _float3 size = { 1.f, 1.f, 1.f }, _float3 intersection = { 0.f, 0.f, 0.f });

private:
	void InitPrototypes(void) override;
	void InputSetting();

private:
	_bool m_pickingMode = false;

	class CMainFrame* m_pMain;
	class CMapToolView* m_pMainView;
	class CToolMenuView* m_pMenuView;

	GETTOR_SETTOR(Engine::CObject*, m_pCurSelectedObject, nullptr, CurSelObj);
	//GETTOR_SETTOR(_bool, m_createMode, false, CreateMode);
	
	_float m_pickRadius = 4.f;

	// test
	_float3 m_rayDir;
	_float3 m_intersect;
};
