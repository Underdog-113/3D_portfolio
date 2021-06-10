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
	void Setting();
	//void(CButtonFunction::*)(), CButtonFunction*
	void DelegatePush(void(CDataLoad::* function)(Engine::CScene*) , CDataLoad* dataload);
	void DeleGatePop(void(CDataLoad::* function)(Engine::CScene*), CDataLoad* dataload);
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

	void CanvasLoad(Engine::CScene* pScene);

	// �� �ε�
	void ToolLoad(Engine::CScene* pScene);
	
	void EffectLoad(Engine::CScene* pScene);

	void ButtonFunction(SP(CButton) button, std::wstring function);
};

