#pragma once
class CMainRoomManager
{
public:
	DECLARE_SINGLETON(CMainRoomManager)

public:
	void Start(Engine::CScene * pScene);
	void Update(void);
	void OnDestroy(void);
private:
	_bool m_init;

	SP(Engine::CObject) m_vPlayer = nullptr;
};

