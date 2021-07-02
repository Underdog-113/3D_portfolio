#pragma once
class CItemData
{
public:
	CItemData();
	~CItemData();

	void AddItemData(std::wstring name,
		_int rank,
		std::wstring explanation,
		_int experience,
		std::wstring textureKey);

	void CountDown(_int value);
private:
	GETTOR_SETTOR(std::wstring, m_name, L"", Name);
	GETTOR_SETTOR(_int, m_rank, 0, Rank);
	GETTOR_SETTOR(std::wstring, m_explanation, L"", Explanation);
	GETTOR_SETTOR(_int, m_experience, 0, Experience);
	GETTOR_SETTOR(std::wstring, m_textureKey, L"", TextureKey);

	GETTOR_SETTOR(_int, m_count, 0, Count);
};

