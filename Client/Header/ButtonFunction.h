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
	static _int stageValue; // ����� ���������� ����
	static _int squadValue; // ���� ���õ� ������ �ɹ��� �ڸ�
private:

};

#endif