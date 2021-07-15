#pragma once
#include "ValkyrieFSM.h"
class CValkyrieSelect :
	public CValkyrieFSM
{
public:
	CValkyrieSelect();
	virtual ~CValkyrieSelect();

	// CValkyrieFSM��(��) ���� ��ӵ�
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

	void PartyJoin(); // ��Ƽ �߰�
	void PartySwap(); // ��Ƽ ����
	void PartySecession(); // ��Ƽ Ż��
	void Not(); // �̵���
	void SceneChange();

private:
	_bool m_init;

	Engine::CObject*  m_vValkyrie[3];
};

