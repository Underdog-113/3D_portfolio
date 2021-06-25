#pragma once
class CItemData
{
public:
	CItemData();
	~CItemData();

	void AddItemData(std::wstring name,
		std::wstring rank,
		std::wstring explanation,
		std::wstring textureKey);

private:
	GETTOR_SETTOR(std::wstring, m_name, L"", Name);
	GETTOR_SETTOR(std::wstring, m_rank, 0, Rank);
	GETTOR_SETTOR(std::wstring, m_explanation, {}, Explanation);
	GETTOR_SETTOR(_int, m_count, 0, Count);

	GETTOR_SETTOR(std::wstring, m_textureKey, {}, TextureKey);
};

