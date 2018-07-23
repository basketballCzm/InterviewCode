#ifndef CSTRING_HPP_INCLUDE
#define CSTRING_HPP_INCLUDE
#include <iostream>
#include <cstdlib>
using namespace std;

class CString;
ostream& operator << (ostream &out, const CString &obj);
istream& operator >> (istream &in, const CString &obj);

//注意区分const常量的对象是调用const型的成员函数。
//非const型的变量首先调用非const型的类成员函数，当没有非const型的成员函数时再调用const型的成员函数
class CString{
private:
	char *m_pStr;
public:
//rewrite common string processing function

	bool Strcpy(const char *pStr);
	int Strlen(const char *pStr);
	//const variable use const function
	const char* GetString() const;
	char* operator = (const char *pStr);
	char* operator = (const CString &obj);

	CString(char *pStr)
	{
		m_pStr = NULL;
		if(NULL != pStr)
		{
			Strcpy(pStr);
		}
	}

	CString(const CString &obj)
	{
		m_pStr = NULL;
		if(NULL != obj.GetString())
		{
			Strcpy(obj.GetString());
		}
	}

	~CString()
	{
		if(NULL != m_pStr)
		{
			delete [] m_pStr;
		}
	}

};


//public function
bool CString::Strcpy(const char *pStr)
{
	if(NULL != m_pStr)
	{
		delete [] m_pStr;
	}
	if(NULL != pStr)
	{
		int nSize = Strlen(pStr) + 1;
		m_pStr = new char [nSize];
		for(int i = 0; (m_pStr[i] = pStr[i]) != '\0'; i++);
	}
}

int CString::Strlen(const char *pStr)
{
	if(NULL == pStr)
	{
		return 0;
	}
	int nSize = 0;
	while('\0' != pStr[nSize++]);
	return nSize;
}

const char* CString::GetString () const
{
	return m_pStr;
}


char* CString::operator = (const char *pStr)
{
	if(NULL != pStr)
	{
		Strcpy(pStr);
	}
	return m_pStr;
}
char* CString::operator = (const CString &obj)
{
	if(NULL != obj.GetString())
	{
		Strcpy(obj.GetString());
	}
	return m_pStr;
}

//global function
ostream& operator << (ostream &out, CString &obj)
{
	out << obj.GetString();
	return out;
}

istream& operator >> (istream &in, CString &obj)
{
	char szBuf[255] = "";
	in >> szBuf;
	obj = (const char*)szBuf;
	return in;
}

#endif