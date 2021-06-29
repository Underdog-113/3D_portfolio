#pragma once
class CValkyrieFSM;
class CValkyriegManager
{
public:	enum STATE { Select, Property, Weapon, LevelUp, STATEEND };
public:
	DECLARE_SINGLETON(CValkyriegManager)

public:
	void Start(Engine::CScene * pScene);
	void Update(void);
	void OnDestroy(void);

	void ChangeFSMSelect();
	void ChangeFSMProperty();
	void ChangeFSMLevelUp();
private:
	void ChangeFSM(STATE state);
	void FSMCreate();
private:
	GETTOR(CValkyrieFSM*, m_valkyrieFSM[STATE::STATEEND], {}, ValkyrieFSM);
	GETTOR(STATE, m_valkyrieState, STATE::Select, valkyrieState);
	GETTOR(STATE, m_valkyrieOldState, STATE::Select, valkyrieOldState);

	GETTOR(Engine::CScene*, m_scene, {}, Scene);

	static std::wstring g_oldSelectValkyrie; // 전에 씬에서 선택한 발키리
	static std::wstring g_selectValkyrie; // 현재 선택한 발키리
};