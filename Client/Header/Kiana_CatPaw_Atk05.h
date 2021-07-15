#pragma once
#ifndef KIANA_CATPAW_ATK05_H
#define KIANA_CATPAW_ATK05_H

#include "Kiana_CatPaw_Abs.h"

class CKiana_CatPaw_Atk05 final : public CKiana_CatPaw_Abs
{
	SMART_DELETER_REGISTER

private:
	CKiana_CatPaw_Atk05();
	~CKiana_CatPaw_Atk05();
	
public:
	static			SP(CKiana_CatPaw_Atk05)		Create(_bool isStatic, Engine::CScene* pScene);

public:
					SP(Engine::CObject)		MakeClone			(void) override;
					void						OnEnable(void) override;
		
};


#endif // KIANA_CATPAW_ATK05_H


