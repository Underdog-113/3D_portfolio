#ifndef ENGINEFUNCTION_H
#define ENGINEFUNCTION_H



namespace Engine
{
	//smart pointer�� private Destructor������ ���� �ذ�
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

	//ClassName ������ �Լ�
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

	// DWORD ��ȯ �Լ�
	inline DWORD FtoDW(_float f)
	{
		return *((DWORD*)&f);
	}

	//String ��ȯ �Լ�
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

	//FileName string���� Ȯ���ڸ� ���� �Լ�
	inline std::wstring RemoveExtension(const std::wstring& fileName)
	{
		_size lastindex = fileName.find_first_of('.');
		return fileName.substr(0, lastindex);
	}

	inline _bool CheckExtension(const std::wstring& fileName, const std::wstring& compare)
	{
		_size lastindex = fileName.find_last_of('.');
		return (fileName.substr(++lastindex) == compare);
	}

	inline char* _wstringTOpchar(std::wstring wstr)
	{
		size_t getVal = 0;
		size_t len = wcslen((wchar_t*)wstr.c_str());
		char* name = new char[2 * len + 1];
		wcstombs_s(&getVal, name, 2 * len + 1, wstr.c_str(), _TRUNCATE);

		return name;
	}

	//���� ���� �̸� ������ �Լ�
	inline std::wstring GetCurFileName(const std::string& str)
	{
		return StrToWStr(str.substr(str.find_last_of('\\') + 1));
	}

	inline float Direction(_float3 pointOne, _float3 pointTwo)
	{
		_float x = pointOne.x - pointTwo.x;
		_float y = pointOne.y - pointTwo.y;
		_float z = pointOne.z - pointTwo.z;
		return sqrt((x * x) + (y * y) + (z * z));
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
