#pragma once
#include "ValkyrieFSM.h"
class CSupplyWapon :
	public CValkyrieFSM
{
public:
	CSupplyWapon();
	virtual ~CSupplyWapon();

	// CValkyrieFSM��(��) ���� ��ӵ�
	virtual void Start() override;
	virtual void End() override;
	virtual _uint FixedUpdate() override;
	virtual _uint Update() override;
	virtual _uint LateUpdate() override;
	virtual void OnDestroy(void) override;

	//Ȯ�ι�ư

private:
	_bool m_init;
};

