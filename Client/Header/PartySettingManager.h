#pragma once
class CPartySettingManager
{
public:
	DECLARE_SINGLETON(CPartySettingManager)

public:
	void Start(Engine::CScene * pScene);
	void Update(void);
	void OnDestroy(void);
private:
	void MainCanvas(Engine::CScene * pScene);
	void ValkyrieStatus(Engine::CScene * pScene);

	void ValkyrieStatusSetting();
	void DataSetting(std::wstring keyValue);

	void PartyJoin();
	void PartySwap();
	void PartySecession();
	void Not();

	void SceneChange();
private:
	static std::wstring m_oldSelectValkyrie; // ���� ������ ������ ��Ű��
	static std::wstring m_selectValkyrie; // ���� ������ ��Ű��
};