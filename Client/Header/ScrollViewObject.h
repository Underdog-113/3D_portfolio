
#ifndef SCROLLVIEW_H
#define SCROLLVIEW_H

#include "Object.h"
#include "ImageObject.h"
#include "Button.h"
#include "TextObject.h"

class CScrollViewObject final : public Engine::CObject
{
	enum EDir_Type { UpandDown = 0, RightandLeft = 1};

	struct ImageInfo
	{
		SP(Engine::CImageObject) m_image;
		_float3 m_offset;
	};

	struct TextInfo
	{
		SP(Engine::CTextObject) m_text;
		_float2 m_offset;
	};


	SMART_DELETER_REGISTER
private:
	CScrollViewObject();
	~CScrollViewObject();

public:
	// CObject��(��) ���� ��ӵ�
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

	void AllDelete();

	void AddScrollViewData(_int column, _float2 distanceXY, _float2 offSet);
	CScrollViewObject* AddImageObjectData(_int number, std::wstring texture, _float3 size, _float2 offset, _float sort = 0);
	CScrollViewObject* AddTextObjectData(_int number, _float2 offset, _int fontSize, D3DXCOLOR color, std::wstring message);


	template<typename Function, typename Object>
	CScrollViewObject* AddButtonObjectData(Function function, Object object, _float2 size, std::wstring name, std::wstring texture1, std::wstring texture2)
	{
		SP(CButton) button =
			std::static_pointer_cast<CButton>(GetScene()->GetObjectFactory()->AddClone(L"Button", true, (_int)Engine::ELayerID::UI, name));
		//button->GetComponent<Engine::CGraphicsC>()->SetIsEnabled(false);
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

		m_init = false;
		return this;
	}

private:
	void SetBasicName(void) override;
	void ImageObjectSort();

	void Scroll();
	bool ScrollChack(_float dir);
	void Directionadjustment(_float3 pos1, _float3 pos2, _float& dir);
private:
	static _uint m_s_uniqueID;

	GETTOR(SP(Engine::CGraphicsC), m_spGraphics, nullptr, Graphics)
	GETTOR(SP(Engine::CTextureC), m_spTexture, nullptr, Texture)
	GETTOR(SP(Engine::CRectTexC), m_spRectTex, nullptr, RectTex)
	GETTOR(SP(Engine::CShaderC), m_spShader, nullptr, Shader)

	GETTOR_SETTOR(_int, m_column, 1, Column) // ���� ����
	GETTOR_SETTOR(_float2, m_offSet, _float2(0, 0), OffSet) // �̹��� ���� ��ġ
	GETTOR_SETTOR(_float2, m_distanceXY, _float2(1, 1), DistanceXY) // �̹��� ������ �Ÿ�

	GETTOR_SETTOR(std::vector<SP(CButton)>, m_vButtonObject, {}, ButtonObject) // �׷��ߵ� ��ư������Ʈ�� �׷� (�̳��� ������ �Ѱ���
	GETTOR_SETTOR(std::vector<std::vector<ImageInfo>>, m_vImageObject, {}, ImageObject) // �׷��ߵ� �̹���������Ʈ�� �׷� (�̳��� ��������)
	GETTOR_SETTOR(std::vector<TextInfo>, m_vTextObject, {}, TextObject) // �׷��ߵ� �̹���������Ʈ�� �׷� (�̳��� ��������)

	GETTOR_SETTOR(EDir_Type, m_dirType, EDir_Type::UpandDown, DirType);

	_float3 m_dir;
	_float3 m_oldMousePos;
	_float m_speed;

	_bool m_chack;
	_bool m_init;
};
#endif
