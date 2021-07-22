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

	void SupplyWeaponFSM();
	void SupplyItemFSM();
	void SupplyOutFSM();
	void SelectCanvasOff();
	void SelectCanvasOn();

private:
	void ChangeFSM(STATE state);
	void FSMCreate();
private:
	GETTOR(CValkyrieFSM*, m_supplyFSM[STATE::STATEEND], {}, SupplyFSM);
	GETTOR(STATE, m_supplyState, STATE::Weapon, SupplyState);
	GETTOR(STATE, m_supplyOldState, STATE::Weapon, SupplyOldState);

	GETTOR_SETTOR(_int, m_outCount, 0, OutCount);

	GETTOR(Engine::CScene*, m_scene, {}, Scene);
};