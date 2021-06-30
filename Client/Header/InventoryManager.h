#pragma once
class CValkyrieFSM;
class CInventoryManager
{
public:	enum STATE { Weapon, Item, STATEEND };
public:
	DECLARE_SINGLETON(CInventoryManager)

public:
	void Start(Engine::CScene * pScene);
	void Update(void);
	void OnDestroy(void);

	void WeaponFSM();
	void ItemFSM();
private:
	void ChangeFSM(STATE state);
	void FSMCreate();
private:
	GETTOR(CValkyrieFSM*, m_inventoryFSM[STATE::STATEEND], {}, InventoryFSM);
	GETTOR(STATE, m_inventoryState, STATE::Weapon, InventoryState);
	GETTOR(STATE, m_inventoryOldState, STATE::Weapon, InventoryOldState);

	GETTOR(Engine::CScene*, m_scene, {}, Scene);
};