#ifndef SCROLLVIEW_H
#define SCROLLVIEW_H

#include "Object.h"
#include "ImageObject.h"
#include "Button.h"
class CScrollViewObject final : public Engine::CObject
{
	struct ImageInfo
	{
		SP(Engine::CImageObject) m_image;
		_float2 m_offset;
	};

	SMART_DELETER_REGISTER
private:
	CScrollViewObject();
	~CScrollViewObject();

public:
	// CObject을(를) 통해 상속됨
	static	SP(CScrollViewObject) Create(_bool isStatic, Engine::CScene* pScene);
	SP(Engine::CObject) MakeClone(void) override;

	void Awake(void) override;
	void Start(void) override;

	void FixedUpdate(void) override;
	void Update(void) override;
	void LateUpdate(void) override;

	void PreRender(LPD3DXEFFECT pEffect) override;
	void Render(LPD3DXEFFECT pEffect) override;
	void PostRender(LPD3DXEFFECT pEffect) override;

	void OnDestroy(void) override;

	void OnEnable(void) override;
	void OnDisable(void) override;

	void AddScrollViewData(_int column, _float2 distanceXY, _float2 offSet);
	CScrollViewObject* AddImageObjectData(_int number, std::wstring texture, _float3 size, _float2 offset);

	template<typename Function, typename Object>
	CScrollViewObject* AddButtonObjectData(Function function, Object object, _float2 size, std::wstring name, std::wstring texture1, std::wstring texture2)
	{
		SP(CButton) button =
			std::dynamic_pointer_cast<CButton>(GetScene()->GetObjectFactory()->AddClone(L"Button", true, (_int)Engine::ELayerID::UI, name));
		button->GetTransform()->SetSize(_float3(size.x, size.y, 0.0f));
		button->SetButtonType(CButton::UP);
		button->GetTexture()->AddTexture(texture1, 0);
		button->GetTexture()->AddTexture(texture2, 0);
		button->GetShader()->AddShader((_int)Engine::EShaderID::RectTexShader);

		Delegate<> m_functionGate;
		m_functionGate += std::bind(function, object);

		button->AddFuncData(m_functionGate);

		m_vButtonObject.emplace_back(button);
		m_vImageObject.emplace_back();
		return this;
	}

private:
	void SetBasicName(void) override;
	void ImageObjectSort();
private:
	static _uint m_s_uniqueID;

	GETTOR(SP(Engine::CGraphicsC), m_spGraphics, nullptr, Graphics)
	GETTOR(SP(Engine::CTextureC), m_spTexture, nullptr, Texture)
	GETTOR(SP(Engine::CRectTexC), m_spRectTex, nullptr, RectTex)

	GETTOR_SETTOR(_int, m_column, 1, Column) // 열의 갯수
	GETTOR_SETTOR(_float2, m_offSet, _float2(0, 0), OffSet) // 이미지 시작 위치
	GETTOR_SETTOR(_float2, m_distanceXY, _float2(1,1), DistanceXY) // 이미지 사이의 거리

	GETTOR_SETTOR(std::vector<SP(CButton)>, m_vButtonObject, {}, ButtonObject) // 그려야될 버튼오브젝트의 그룹 (이놈은 무조건 한개임
	GETTOR_SETTOR(std::vector<std::vector<ImageInfo>>, m_vImageObject, {}, ImageObject) // 그려야될 이미지오브젝트의 그룹 (이놈은 여러개임)
};
#endif
