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

private:
	void InitPrototypes(void) override;
	void InputSetting();

private:
	_bool m_pickingMode = true;
	_bool m_createMode = false;

	class CMainFrame* m_pMain;
	class CMapToolView* m_pMainView;
	class CToolMenuView* m_pMenuView;

	GETTOR_SETTOR(Engine::CObject*, m_pCurSelectedObject, nullptr, CurSelObj);
	
	_float m_pickRadius = 4.f;
	//_bool m_bPickingMode = false;
	//_bool m_bClick = true;
	//_bool m_bShownCurObjInfo = true; // true면 보여줬음. false면 보여줘야됨.

	//std::unordered_map<_uint, std::vector<_vec3>> m_mNaviPos; // 네비 구의 정점 위치들을 그룹별로 저장하는 맵
};
