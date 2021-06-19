#pragma once
#ifndef KIANA_H
#define KIANA_H

#include "Valkyrie.h"

class CFSM_KianaC;
class CKiana final : public CValkyrie
{
	SMART_DELETER_REGISTER

public:
	enum UltraAttack { 
		ATK01, ATK02, ATK03, ATK04, ATK05,
		Branch_ATK01, Branch_ATK02,
		QTE_ATK
	};
private:
	CKiana();
	~CKiana();

public:
	static			SP(CKiana)				Create(_bool isStatic, Engine::CScene* pScene);

public:
					SP(Engine::CObject)		MakeClone			(void) override;
		
					void					Awake				(void) override;
					void					Start				(void) override;
		
					void					FixedUpdate			(void) override;
					void					Update				(void) override;
					void					LateUpdate			(void) override;

					void					PreRender			(LPD3DXEFFECT pEffect) override;
					void					Render				(LPD3DXEFFECT pEffect) override;
					void					PostRender			(LPD3DXEFFECT pEffect) override;
		
					void					OnDestroy			(void) override;
		
					void					OnEnable			(void) override;
					void					OnDisable			(void) override;

					void					SetBasicName		(void) override;
					
public:
					void					Update_WeaponTransform(void);

					void					CreatePistol		(void);
					void					CreateCatPaw		(void);
					void					UseUltraCost		(void);
					void					UltraAtk			(UltraAttack index);
					void					UltraAtk_Ring		(UltraAttack index);

					void					SetUltraMode		(bool value);;

private:
	GETTOR			(SP(Engine::CObject),	m_spWeapon_Left,		nullptr, Weapon_Left)
	GETTOR			(SP(Engine::CObject),	m_spWeapon_Right,		nullptr, Weapon_Right)


private:
	GETTOR			(SP(Engine::CObject),	m_spCatPaw_Atk01,		nullptr, CatPaw_Atk01)
	GETTOR			(SP(Engine::CObject),	m_spCatPaw_Atk02,		nullptr, CatPaw_Atk02)
	GETTOR			(SP(Engine::CObject),	m_spCatPaw_Atk03,		nullptr, CatPaw_Atk03)
	GETTOR			(SP(Engine::CObject),	m_spCatPaw_Atk04,		nullptr, CatPaw_Atk04)
	GETTOR			(SP(Engine::CObject),	m_spCatPaw_Atk05,		nullptr, CatPaw_Atk05)

		
	GETTOR			(SP(Engine::CObject),	m_spCatPaw_Ring_Atk01,	nullptr, CatPaw_Ring_Atk01)
	GETTOR			(SP(Engine::CObject),	m_spCatPaw_Ring_Atk02,	nullptr, CatPaw_Ring_Atk02)
	GETTOR			(SP(Engine::CObject),	m_spCatPaw_Ring_Atk03,	nullptr, CatPaw_Ring_Atk03)
	GETTOR			(SP(Engine::CObject),	m_spCatPaw_Ring_Atk04,	nullptr, CatPaw_Ring_Atk04)
	GETTOR			(SP(Engine::CObject),	m_spCatPaw_Ring_Atk05,	nullptr, CatPaw_Ring_Atk05)

	GETTOR			(_bool,					m_ultraMode,		false, UltraMode)

private:

	_mat*						m_pRightToe_World = nullptr;
	_mat*						m_pRightToe_BoneOffset = nullptr;
	Engine::D3DXFRAME_DERIVED*	m_pRightToe_Frame = nullptr;

	_mat*						m_pLeftHand_World = nullptr;
	_mat*						m_pLeftHand_BoneOffset = nullptr;
	Engine::D3DXFRAME_DERIVED*	m_pLeftHand_Frame = nullptr;

	_mat*						m_pRightHand_World = nullptr;
	_mat*						m_pRightHand_BoneOffset = nullptr;
	Engine::D3DXFRAME_DERIVED*	m_pRightHand_Frame = nullptr;

	_mat* m_pRightHand = nullptr;

};

#endif