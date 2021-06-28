#pragma once
#include "ValkyrieFSM.h"
class CValkyrieProperty :
	public CValkyrieFSM
{
public:
	CValkyrieProperty();
	virtual ~CValkyrieProperty();

	// CValkyrieFSM��(��) ���� ��ӵ�
	virtual void Start() override;
	virtual void End() override;
	virtual _uint FixedUpdate() override;
	virtual _uint Update() override;
	virtual _uint LateUpdate() override;
	virtual void OnDestroy(void) override;

private:
	void PropertyCanvas();

	void ChangeSelect();
	void DataInput(std::wstring objectName, std::wstring  dataValue);

private:
	Engine::CScene* m_scene;
};
