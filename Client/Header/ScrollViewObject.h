#ifndef SCROLLVIEW_H
#define SCROLLVIEW_H

#include "Object.h"
#include "ImageObject.h"
class CScrollViewObject final : public Engine::CObject
{
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

	void PreRender(void) override;
	void Render(void) override;
	void PostRender(void) override;

	void OnDestroy(void) override;

	void OnEnable(void) override;
	void OnDisable(void) override;

	void AddScrollViewData(_int column, _float2 distanceXY, std::wstring texture);
	CScrollViewObject* AddImageObjectData(std::wstring texture);
private:
	void SetBasicName(void) override;
	void ImageObjectSort();
private:
	static _uint m_s_uniqueID;

	GETTOR_SETTOR(_int, m_column, 1, Column); // ��
	GETTOR_SETTOR(_float2, m_distanceXY, _float2(1,1), DistanceXY); // �̹��� ������ �Ÿ�
	GETTOR_SETTOR(std::vector<Engine::CImageObject>, m_vImageObject, {}, ImageObject); // �׷��ߵ� ������Ʈ�� �׷�

	GETTOR(SP(Engine::CGraphicsC), m_spGraphics, nullptr, Graphics)
	GETTOR(SP(Engine::CTextureC), m_spTexture, nullptr, Texture)
	GETTOR(SP(Engine::CRectTexC), m_spRectTex, nullptr, RectTex)
};
#endif