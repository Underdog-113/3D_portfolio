#pragma once

#ifndef STAGEUILINKER_H
#define STAGEUILINKER_H

// crt chance -> crt * 0.21


class CValkyrie;
class CMonster;

class CUILinker;
class CStageControlTower;
class CStatusDealer
{
public:
	CStatusDealer();
	~CStatusDealer();

public:	/* Character */
	bool Damage_VtoM(V_Stat* pSrc, M_Stat* pDst, _float dmgRate);
	bool Damage_MtoV(M_Stat* pSrc, V_Stat* pDst, _float dmgRate);
	void HpUp_Solo(Chara_Stat* pSrc, _float value);
	void HpDown_Solo(Chara_Stat* pSrc, _float value);

public:	/* Valkyrie */
	void SpUp(V_Stat* pStat, _float value);
	void SpDown(V_Stat* pStat, _float value);

//	void HpBuff(V_Stat* pStat);
//	void SpBuff(V_Stat* pStat);
//	void AtkBuff(V_Stat* pStat);
//	void DefBuff(V_Stat* pStat);
//	void CrtBuff(V_Stat* pStat);
//
//	void HpDebuff(V_Stat* pStat);
//	void SpDebuff(V_Stat* pStat);
//	void AtkDebuff(V_Stat* pStat);
//	void DefDebuff(V_Stat* pStat);
//	void CrtDebuff(V_Stat* pStat);

	// add status CC
	
public: /* Monster */

	bool BreakGauge(M_Stat* pStat, _float value);

private:
	
	GETTOR_SETTOR		(CStageControlTower*,		m_pCT,			nullptr,		ControlTower)
	GETTOR_SETTOR		(CUILinker*,			m_pLinker,			nullptr,		UILinker)
};


#endif
