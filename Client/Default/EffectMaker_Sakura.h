#pragma once
#include "EffectMaker.h"

class CSakura;
class CEffectMaker_Sakura :	public CEffectMaker
{
public:
	CEffectMaker_Sakura(CSakura* pSakura);
	~CEffectMaker_Sakura();

	void CreateEffect_Attack1();
	void CreateEffect_Attack2();
	void CreateEffect_Attack2_2();
	void CreateEffect_Attack3();
	void CreateEffect_Attack4();
	void CreateEffect_Attack4_2();
	void CreateEffect_Attack4_3();

	void CreateEffect_Beam();

	void CreateEffect_Cyclone();

	void CreateEffect_Dash();

private:
	CSakura* m_pSakura;


};

