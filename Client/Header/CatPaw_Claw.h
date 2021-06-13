#pragma once
#ifndef CATPAW_CLAW_H
#define CATPAW_CLAW_H

#include "Object.h"

class CCatPaw_Claw final : public Engine::CObject
{
	SMART_DELETER_REGISTER

private:
	CCatPaw_Claw();
	~CCatPaw_Claw();


protected:
	static			_uint							m_s_uniqueID;
	GETTOR			(SP(Engine::CMeshC),			m_spMesh,			nullptr,	Mesh)
	GETTOR			(SP(Engine::CGraphicsC),		m_spGraphics,		nullptr,	Graphics)
	GETTOR			(SP(Engine::CTextureC),			m_spTexture,		nullptr,	Texture)
};


#endif // CATPAW_H


