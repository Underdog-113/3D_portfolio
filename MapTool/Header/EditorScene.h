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
	void InitPrototypes(void) override;
	void Picking();
	void InputSetting();
	class Engine::CObject* RayCast(_float3 origin, _float maxDistance, _float3& intersection);
	_float3 GetPickingDirection(_float3& origin, const _mat* pMatWorld);
	_float Distance(_float3 & thisPosition, _float3 targetPosition);

private:
	_bool m_pickingMode = true;
	_bool m_createMode = false;

	class CMainFrame* m_pMain;
	class CMapToolView* m_pMainView;
	class CToolMenuView* m_pMenuView;

	GETTOR_SETTOR(Engine::CObject*, m_pCurSelectedObject, nullptr, CurSelObj);

	//_bool m_bPickingMode = false;
	//_bool m_bClick = true;
	//_bool m_bShownCurObjInfo = true; // true�� ��������. false�� ������ߵ�.

	//std::unordered_map<_uint, std::vector<_vec3>> m_mNaviPos; // �׺� ���� ���� ��ġ���� �׷캰�� �����ϴ� ��
};
