#include <string>
//#include <iostream>
using namespace std;
// UTF8转std:string
// 转换过程：先将utf8转双字节Unicode编码，再通过WideCharToMultiByte将宽字符转换为多字节。
std::string UTF8_To_string(const std::string& str);
// std:string转UTF8
std::string string_To_UTF8(const std::string& str);



inline string operator "" _UTF8(const char* v, size_t n)
{
	return UTF8_To_string(v);
}

