#ifndef BUTTONFUNCTION_H
#define BUTTONFUNCTION_H

class CButtonFunction
{
public:
	CButtonFunction();
	~CButtonFunction();

public:
	void MainRoomScene();
	void StageSelectionScene();
	void ReadyToSortieScene();
	void PartySettingScene();
	void InventoryScene();
	void Sally();
	void BattleEndScene();
	void SupplyScene();

	void BattleRenunciation();

	void ObjectOn();
	void ObjectOff();

public:
	static _int stageValue; // 출격할 스테이지의 벨류
	static _int squadValue; // 현재 선택된 스쿼드 맴버의 자리
private:

};

#endif