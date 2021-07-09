#pragma once
#include "ValkyrieFSM.h"
class CSupplyOut :
	public CValkyrieFSM
{
public:
	CSupplyOut();
	virtual ~CSupplyOut();

	// CValkyrieFSM��(��) ���� ��ӵ�
	virtual void Start() override;
	virtual void End() override;
	virtual _uint FixedUpdate() override;
	virtual _uint Update() override;
	virtual _uint LateUpdate() override;
	virtual void OnDestroy(void) override;

private:
	_bool m_init;
};

