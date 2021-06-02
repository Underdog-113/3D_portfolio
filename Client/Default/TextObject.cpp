#include "stdafx.h"
#include "TextObject.h"

CTextObject::CTextObject()
{
}


CTextObject::~CTextObject()
{
}

SP(Engine::CObject) CTextObject::MakeClone(void)
{
	SP(CTextObject) spClone(new CTextObject);
	spClone->AddComponent<Engine::CGraphicsC>();
	spClone->AddComponent<Engine::CBitmapC>();

	return spClone;
	return SP(CObject)();
}

void CTextObject::Awake(void)
{
}

void CTextObject::Start(void)
{
}

void CTextObject::FixedUpdate(void)
{
}

void CTextObject::Update(void)
{

}

void CTextObject::LateUpdate(void)
{
}

void CTextObject::OnDestroy(void)
{
}

void CTextObject::OnEnable(void)
{
}

void CTextObject::OnDisable(void)
{
}

void CTextObject::SetBasicName(void)
{
}
