#pragma once
class CValkyrieFSM;
class CValkyriegManager
{
public:	enum STATE { Select, Property, Weapon, STATEEND };
public:
	DECLARE_SINGLETON(CValkyriegManager)

public:
	void Start(Engine::CScene * pScene);
	void Update(void);
	void OnDestroy(void);

	void ChangeFSM(STATE state);
	void ChangeFSMProperty();
private:
	void FSMCreate();
private:
	CValkyrieFSM* m_valkyrieFSM[STATE::STATEEND];
	GETTOR(STATE, m_valkyrieState, STATE::Select, valkyrieState);
	GETTOR(STATE, m_valkyrieOldState, STATE::Select, valkyrieOldState);

	GETTOR(Engine::CScene*, m_scene, {}, Scene);

	static std::wstring m_oldSelectValkyrie; // 전에 씬에서 선택한 발키리
	static std::wstring m_selectValkyrie; // 현재 선택한 발키리
};