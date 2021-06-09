#pragma once
#include "DeleGate.h"

class CScene;
class CDataLoad
{
	Delegate<Engine::CScene*> m_loadDeleGate;
public:
	CDataLoad();
	~CDataLoad();

public:
	void Load(Engine::CScene* pScene);

private:
	// �̹��� �ε�
	void ImageLoad(Engine::CScene* pScene);
	
	// �����̴� �ε�
	void SliderLoad(Engine::CScene* pScene);

	// ��ư �ε�
	void ButtonLoad(Engine::CScene* pScene);

	// ��ũ�Ѻ� �ε�
	void ScrollViewLoad(Engine::CScene* pScene);

	// �� �ε�
	void ToolLoad(Engine::CScene* pScene);
};

