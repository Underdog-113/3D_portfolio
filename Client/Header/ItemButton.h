#ifndef ITEMBUTTON_H
#define ITEMBUTTON_H

#include "Object.h"
#include "TextObject.h"
class CItemButton final : public Engine::CObject
{
	SMART_DELETER_REGISTER
private:
	explicit						CItemButton(void);
	~CItemButton(void);

public:
	static		SP(CItemButton)			Create(_bool isStatic, Engine::CScene* pScene);

	SP(Engine::CObject)	MakeClone(void) override;

	void				Awake(void) override;
	void				Start(void) override;

	void				FixedUpdate(void) override;
	void				Update(void) override;
	void				LateUpdate(void) override;

	void				PreRender(LPD3DXEFFECT pEffect) override;
	void				Render(LPD3DXEFFECT pEffect) override;
	void				PostRender(LPD3DXEFFECT pEffect) override;

	void				OnDestroy(void) override;

	void				OnEnable(void) override;
	void				OnDisable(void) override;

	void ButtonCreate(std::wstring name, _float3 pos, _float3 size, std::wstring textureKey, CButton::EButton_Type buttonType);
	void ImageCreate(std::wstring name, _float3 pos, _float3 size, std::wstring textureKey);
	void textCreate(std::wstring name , _float2 pos, _float sort, _int fontSize, D3DXCOLOR color, std::wstring alignment, std::wstring message);

	void ItemSelect();
private:
	void				SetBasicName(void) override;
private:
	static		_uint				m_s_uniqueID;

	GETTOR_SETTOR(std::wstring, m_itemName, L"", ItemName);
	GETTOR(SP(CButton), m_button, nullptr, Button);
	GETTOR(SP(Engine::CImageObject), m_image, nullptr , Image);
	GETTOR(SP(Engine::CTextObject), m_textObj, nullptr, TextObject);


	std::wstring m_buttonTexture;
	std::wstring m_imageTexture;
	_int m_itemCount;
	Engine::CObject* m_selectObject;
};

#endif


// 하얀색 배경 버튼 // 텍스처 , 함수
// 아이템 이미지 // 텍스처
// 아래쪽에 갯수 // 문자열
// 누르면 선택된 아이템은 크기가 커진다.
