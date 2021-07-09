#pragma once
class CValkyrieFSM;
class CSupplyManager
{
public:	enum STATE { Weapon, Item, Out, STATEEND };
public:
	DECLARE_SINGLETON(CSupplyManager)

public:
	void Start(Engine::CScene * pScene);
	void Update(void);
	void OnDestroy(void);

	void WeaponFSM();
	void ItemFSM();
	void OutFSM();
private:
	void ChangeFSM(STATE state);
	void FSMCreate();
private:
	GETTOR(CValkyrieFSM*, m_supplyFSM[STATE::STATEEND], {}, SupplyFSM)
	GETTOR(STATE, m_supplyState, STATE::Weapon, SupplyState)
	GETTOR(STATE, m_supplyOldState, STATE::Weapon, SupplyOldState)

	GETTOR(Engine::CScene*, m_scene, {}, Scene)
};