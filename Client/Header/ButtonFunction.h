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
	void Sally();
	void BattleEndScene();

	void BattleRenunciation();

	void ObjectOn();
	void ObjectOff();

private:
	static _int stageValue;
};

#endif