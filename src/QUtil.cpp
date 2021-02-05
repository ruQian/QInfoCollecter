#include "QUtil.h"

#include <mirai.h>
// UTF8转std:string
// 转换过程：先将utf8转双字节Unicode编码，再通过WideCharToMultiByte将宽字符转换为多字节。
std::string UTF8_To_string(const std::string& str) 
{ 
    int nwLen = MultiByteToWideChar(CP_UTF8, 0, str.c_str(), -1, NULL, 0); 
    wchar_t* pwBuf = new wchar_t[nwLen + 1];    //一定要加1，不然会出现尾巴 
    memset(pwBuf, 0, nwLen * 2 + 2); 
    MultiByteToWideChar(CP_UTF8, 0, str.c_str(), str.length(), pwBuf, nwLen); 
    int nLen = WideCharToMultiByte(CP_ACP, 0, pwBuf, -1, NULL, NULL, NULL, NULL); 
    char* pBuf = new char[nLen + 1]; 
    memset(pBuf, 0, nLen + 1); 
    WideCharToMultiByte(CP_ACP, 0, pwBuf, nwLen, pBuf, nLen, NULL, NULL);

    std::string strRet = pBuf; 

    delete []pBuf; 
    delete []pwBuf; 
    pBuf = NULL; 
    pwBuf = NULL; 

    return strRet; 
} 

// std:string转UTF8
std::string string_To_UTF8(const std::string& str) 
{ 
    int nwLen = ::MultiByteToWideChar(CP_ACP, 0, str.c_str(), -1, NULL, 0); 
    wchar_t* pwBuf = new wchar_t[nwLen + 1];    //一定要加1，不然会出现尾巴 
    ZeroMemory(pwBuf, nwLen * 2 + 2); 
    ::MultiByteToWideChar(CP_ACP, 0, str.c_str(), str.length(), pwBuf, nwLen); 
    int nLen = ::WideCharToMultiByte(CP_UTF8, 0, pwBuf, -1, NULL, NULL, NULL, NULL); 
    char* pBuf = new char[nLen + 1]; 
    ZeroMemory(pBuf, nLen + 1); 
    ::WideCharToMultiByte(CP_UTF8, 0, pwBuf, nwLen, pBuf, nLen, NULL, NULL); 

    std::string strRet(pBuf); 

    delete []pwBuf; 
    delete []pBuf; 
    pwBuf = NULL; 
    pBuf  = NULL; 

    return strRet; 
} 
