#ifndef ENGINEFUNCTION_H
#define ENGINEFUNCTION_H



namespace Engine
{
	//smart pointer랑 private Destructor사이의 문제 해결
	template <typename T>
	void SmartDeleter(T* something)
	{
		delete something;
	}

	template <typename T>
	void SafeDelete(T& ptr)
	{
		if (ptr)
		{
			delete ptr;
			ptr = nullptr;
		}
	}

	template <typename T>
	void SafeRelease(T& ptr)
	{
		if (ptr)
		{
			DWORD refCnt = ptr->Release();
			if (refCnt == 0)
				ptr = NULL;
		}
	}

	template <typename T>
	void SafeDeleteArray(T& ptr)
	{
		if (ptr)
		{
			delete[] ptr;
			ptr = nullptr;
		}
	}

	//ClassName 따오는 함수
	template <typename T>
	std::wstring GetCurClassName(void)
	{
		std::wstring className = StrToWStr(typeid(T).name());
		_size nameStartPos = className.find_last_of(':');
		if (nameStartPos == std::string::npos)
			className.erase(0, 7);
		else
			className.erase(0, nameStartPos + 2);

		return className;
	}

	template <typename T>
	std::wstring GetCurClassName(T* something)
	{
		std::wstring className = StrToWStr(typeid(*something).name());
		_size nameStartPos = className.find_last_of(':');
		if (nameStartPos == std::wstring::npos)
			className.erase(0, 7);
		else
			className.erase(0, nameStartPos + 2);

		return className;
	}

	// DWORD 반환 함수
	inline DWORD FtoDW(_float f)
	{
		return *((DWORD*)&f);
	}

	//String 변환 함수
	inline std::wstring StrToWStr(const std::string& str)
	{
		using convert_typeX = std::codecvt_utf8<wchar_t>;
		std::wstring_convert<convert_typeX, wchar_t> converterX;

		return converterX.from_bytes(str);
	}

	inline std::string WStrToStr(const std::wstring& wstr)
	{
		using convert_typeX = std::codecvt_utf8<wchar_t>;
		std::wstring_convert<convert_typeX, wchar_t> converterX;

		return converterX.to_bytes(wstr);
	}

	//FileName string에서 확장자명 떼는 함수
	inline std::wstring RemoveExtension(const std::wstring& fileName)
	{
		_size lastindex = fileName.find_first_of('.');
		return fileName.substr(0, lastindex);
	}

	inline constexpr unsigned int HashCode(const char* str)
	{
		return str[0] ? static_cast<unsigned int>(str[0]) + 0xEDB8832Full * HashCode(str + 1) : 8603;
		/*
		문자열 데이터를 정수형 데이터로 매핑하는 해시 함수
		constexpr : 변수 또는 함수의 값을 컴파일 시점에 도출하여 상수화 시켜주는 기능
		*/
	}

	//현재 파일 이름 따오는 함수
	inline std::wstring GetCurFileName(const std::string& str)
	{
		return StrToWStr(str.substr(str.find_last_of('\\') + 1));
	}

	inline std::wstringstream& operator >> (std::wstringstream& in, _float4 & float4)
	{
		std::wstring vecStr;
		std::wstring vecStrX, vecStrY, vecStrZ, vecStrW;

		in >> vecStr;

		_size xEndPos, yEndPos, zEndPos;

		xEndPos = vecStr.find_first_of(L',');
		yEndPos = vecStr.find_first_of(L',', xEndPos + 1);
		zEndPos = vecStr.find_last_of(L',');

		vecStrX = vecStr.substr(0, xEndPos);
		vecStrY = vecStr.substr(++xEndPos, yEndPos - xEndPos);
		vecStrZ = vecStr.substr(++yEndPos, zEndPos - yEndPos);
		vecStrW = vecStr.substr(++zEndPos);

		std::wstringstream ssX(vecStrX);
		std::wstringstream ssY(vecStrY);
		std::wstringstream ssZ(vecStrZ);
		std::wstringstream ssW(vecStrW);

		ssX >> float4.x;
		ssY >> float4.y;
		ssZ >> float4.z;
		ssW >> float4.w;

		return in;
	}

	inline std::wstringstream& operator >> (std::wstringstream& in, _float3 & float3)
	{
		std::wstring vecStr;
		std::wstring vecStrX, vecStrY, vecStrZ;

		in >> vecStr;

		_size xEndPos, yEndPos;

		xEndPos = vecStr.find_first_of(L",");
		yEndPos = vecStr.find_last_of(L",");

		vecStrX = vecStr.substr(0, xEndPos);
		vecStrY = vecStr.substr(++xEndPos, yEndPos - xEndPos);
		vecStrZ = vecStr.substr(++yEndPos);

		std::wstringstream ssX(vecStrX);
		std::wstringstream ssY(vecStrY);
		std::wstringstream ssZ(vecStrZ);

		ssX >> float3.x;
		ssY >> float3.y;
		ssZ >> float3.z;

		return in;
	}

	inline std::wstringstream& operator >> (std::wstringstream& in, _float2 & float2)
	{
		std::wstring vecStr;
		std::wstring vecStrX, vecStrY;

		in >> vecStr;

		_size xEndPos;

		xEndPos = vecStr.find_first_of(L",");

		vecStrX = vecStr.substr(0, xEndPos);
		vecStrY = vecStr.substr(++xEndPos);

		std::wstringstream ssX(vecStrX);
		std::wstringstream ssY(vecStrY);

		ssX >> float2.x;
		ssY >> float2.y;

		return in;
	}

	template<class T> inline T	operator	~	(T a)		{ return (T)~(int)a; }
	template<class T> inline T	operator	|	(T a, T b)	{ return (T)((int)a | (int)b); }
	template<class T> inline T	operator	&	(T a, T b)	{ return (T)((int)a & (int)b); }
	template<class T> inline T	operator	^	(T a, T b)	{ return (T)((int)a ^ (int)b); }
	template<class T> inline T& operator	|=	(T& a, T b) { return (T&)((int&)a |= (int)b); }
	template<class T> inline T& operator	&=	(T& a, T b) { return (T&)((int&)a &= (int)b); }
	template<class T> inline T& operator	^=	(T& a, T b) { return (T&)((int&)a ^= (int)b); }
}



#endif // !ENGINEFUNCTION_H





