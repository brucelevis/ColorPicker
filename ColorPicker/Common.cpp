#include "stdafx.h"
#include "Common.h"


CCommon::CCommon()
{
}


CCommon::~CCommon()
{
}

std::wstring CCommon::StrToUnicode(const char * str, bool utf8)
{
	std::wstring result;
	int size;
	size = MultiByteToWideChar((utf8 ? CP_UTF8 : CP_ACP), 0, str, -1, NULL, 0);
	if (size <= 0) return std::wstring();
	wchar_t* str_unicode = new wchar_t[size + 1];
	MultiByteToWideChar((utf8 ? CP_UTF8 : CP_ACP), 0, str, -1, str_unicode, size);
	result.assign(str_unicode);
	delete[] str_unicode;
	return result;
}

std::string CCommon::UnicodeToStr(const wchar_t * wstr, bool utf8)
{
	std::string result;
	int size{ 0 };
	size = WideCharToMultiByte((utf8 ? CP_UTF8 : CP_ACP), 0, wstr, -1, NULL, 0, NULL, NULL);
	if (size <= 0) return std::string();
	char* str = new char[size + 1];
	WideCharToMultiByte((utf8 ? CP_UTF8 : CP_ACP), 0, wstr, -1, str, size, NULL, NULL);
	result.assign(str);
	delete[] str;
	return result;
}

void CCommon::StringNormalize(std::wstring & str)
{
	if (str.empty()) return;

	int size = str.size();	//�ַ����ĳ���
	if (size < 0) return;

	int index1 = 0;		//�ַ����е�1�����ǿո������ַ���λ��
	int index2 = size - 1;	//�ַ��������һ�����ǿո������ַ���λ��
	while (index1 < size && str[index1] >= 0 && str[index1] <= 32)
		index1++;
	while (index2 >= 0 && str[index2] >= 0 && str[index2] <= 32)
		index2--;
	if (index1 > index2)	//���index1 > index2��˵���ַ���ȫ�ǿո������ַ�
		str.clear();
	else if (index1 == 0 && index2 == size - 1)	//���index1��index2��ֵ�ֱ�Ϊ0��size - 1��˵���ַ���ǰ��û�пո������ַ���ֱ�ӷ���
		return;
	else
		str = str.substr(index1, index2 - index1 + 1);

}

void CCommon::SetDrawRect(CDC * pDC, CRect rect)
{
	CRgn rgn;
	rgn.CreateRectRgnIndirect(rect);
	pDC->SelectClipRgn(&rgn);
}