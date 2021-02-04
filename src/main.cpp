// 注意: 本项目的所有源文件都必须是 UTF-8 编码

// 这是一个“反撤回”机器人
// 在群里回复 “/anti-recall enabled.” 或者 “撤回没用” 之后
// 如果有人在群里撤回，那么机器人会把撤回的内容再发出来

#include <iostream>
#include <map>
#include <mirai.h>
//#include "myheader.h"


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






int main()
{
	using namespace std;
	using namespace Cyan;

#if defined(WIN32) || defined(_WIN32)
	// 切换代码页，让 CMD 可以显示 UTF-8 字符
	system("chcp 65001");
#endif

	MiraiBot bot("8.131.255.126", 8822);
	while (true)
	{
		try
		{
			bot.Auth("INITKEY7IDHq9QW", 3331720495_qq);
			break;
		}
		catch (const std::exception& ex)
		{
			cout << ex.what() << endl;
		}
		MiraiBot::SleepSeconds(1);
	}
	cout << "Bot Working..." << endl;

	// 用map记录哪些群启用了“反撤回”功能
	map<GID_t, bool> groups;

	bot.On<GroupMessage>(
		[&](GroupMessage m)
		{
			try
			{
				string plain = m.MessageChain.GetPlainText();
				if (plain == "/anti-recall enabled." || plain == "撤回没用")
				{
					groups[m.Sender.Group.GID] = true;
					m.Reply(MessageChain().Plain("撤回也没用，我都看到了"));
					return;
				}
				if (plain == "/anti-recall disabled." || plain == "撤回有用")
				{
					groups[m.Sender.Group.GID] = false;
					m.Reply(MessageChain().Plain("撤回有用"));
					return;
				}
			}
			catch (const std::exception& ex)
			{
				cout << ex.what() << endl;
			}
		});


	bot.On<GroupRecallEvent>(
		[&](GroupRecallEvent e)
		{
			try
			{
				if (!groups[e.Group.GID]) return;
				auto recalled_mc = bot.GetGroupMessageFromId(e.MessageId).MessageChain;
				auto mc = "刚刚有人撤回了: " + recalled_mc;
				bot.SendMessage(e.Group.GID, mc);
			}
			catch (const std::exception& ex)
			{
				cout << ex.what() << endl;
			}
		})
		.On<FriendMessage>(
		[&](FriendMessage fm)
		{
			string plain = fm.MessageChain.GetPlainText();
			string plain2 = string_To_UTF8("你好"); 
			if(plain == plain2)
			{
			cout<<plain2<<" = "<<plain<<endl;
			}
			cout<<plain<<endl;
			fm.Reply("hello, " + fm.MessageChain);
		});


	bot.EventLoop();

	return 0;
}