#pragma once
#include "Scene.h"

class Engine::CCamera;

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
	void InitPrototypes(void) override;
	void Picking();
	void InputSetting();
	class Engine::CObject* RayCast(_float3 origin, _float maxDistance, _float3& intersection);
	_float3 GetPickingDirection(_float3& origin, const _mat* pMatWorld);
	_float Distance(_float3 & thisPosition, _float3 targetPosition);

private:
	_bool m_pickingMode = false;
	_bool m_createMode = false;
	class Engine::CObject* m_pCurSelectedObject = nullptr;

	class CMainFrame* m_pMain;
	class CMapToolView* m_pMainView;
	class CToolMenuView* m_pMenuView;

	//_bool m_bPickingMode = false;
	//_bool m_bClick = true;
	//_bool m_bShownCurObjInfo = true; // true면 보여줬음. false면 보여줘야됨.

	//std::unordered_map<_uint, std::vector<_vec3>> m_mNaviPos; // 네비 구의 정점 위치들을 그룹별로 저장하는 맵
};
