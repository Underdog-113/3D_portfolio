#pragma once
#include "ValkyrieFSM.h"
class CValkyrieSelect :
	public CValkyrieFSM
{
public:
	CValkyrieSelect();
	virtual ~CValkyrieSelect();

	// CValkyrieFSM을(를) 통해 상속됨
	virtual void Start() override;
	virtual void End() override;
	virtual _uint FixedUpdate() override;
	virtual _uint Update() override;
	virtual _uint LateUpdate() override;
	virtual void OnDestroy(void) override;

private:
	void MainCanvas();
	void ValkyrieStatus();

	void ValkyrieStatusSetting();
	void DataSetting(std::wstring keyValue);

	void PartyJoin(); // 파티 추가
	void PartySwap(); // 파티 스왑
	void PartySecession(); // 파티 탈퇴
	void Not(); // 미동작
	void SceneChange();

private:
	_bool m_init;

	Engine::CObject*  m_vValkyrie[3];
};

