// 注意: 本项目的所有源文件都必须是 UTF-8 编码

// 这是一个“反撤回”机器人
// 在群里回复 “/anti-recall enabled.” 或者 “撤回没用” 之后
// 如果有人在群里撤回，那么机器人会把撤回的内容再发出来

#include <iostream>
#include <map>
#include <mirai.h>
#include "QUtil.h"
#include "QCollectorServerApi.h"
#include "mirai/third-party/nlohmann/json.hpp"
//#include "myheader.h"

int main()
{
	using namespace std;
	using namespace Cyan;

#if defined(WIN32) || defined(_WIN32)
	// 切换代码页，让 CMD 可以显示 UTF-8 字符
	system("chcp 65001");
#endif
	QCollectorServerApi qCollectorServerApi;
	
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


	// 获取群组列表
	auto groups = bot.GetGroupList();
	int i = 1;
	for (const auto& g : groups)
	{
		cout << (i++) << ". " << g.GID << ", " << g.Name << ", " << GroupPermissionStr(g.Permission) << endl;
		// 获取群成员列表
		//auto gMembers = bot.GetGroupMembers(g.GID);
		//for (const auto& gMem : gMembers)
		//{
		//	cout << " | " << gMem.QQ << ", " << gMem.MemberName << ", " << GroupPermissionStr(gMem.Permission);
			// 获取群成员的信息（群名片、群头衔）
		//	auto info = bot.GetGroupMemberInfo(gMem.Group.GID, gMem.QQ);
		//	cout << ", 1: " << (info.Name.empty() ? "None" : info.Name)
		//		 << ", 2: " << (info.SpecialTitle.empty() ? "None" : info.SpecialTitle) << endl;
		//}
	}





	// 用map记录哪些群启用了“反撤回”功能
	map<GID_t, bool> groupMap;

	bot.On<GroupMessage>(
		[&](GroupMessage m)
		{
			try
			{
				string plain = m.MessageChain.GetPlainText();
				/*
				string plain = m.MessageChain.GetPlainText();
				if (plain == "/anti-recall enabled." || plain == "撤回没用"_UTF8)
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
				}*/
				//上传数据到数据库 暂时这么写 
				json j;
				j["rawMessage"] = plain;
				j["groupid"]="123";
				j["DOrP"]=1;
				j["telNO"]="123";
				j["messageDate"]="2017-12-12";
				std::string s = j.dump(); 
				qCollectorServerApi.PostQMessageData(s);

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
				/*
				if (!groups[e.Group.GID]) return;
				auto recalled_mc = bot.GetGroupMessageFromId(e.MessageId).MessageChain;
				auto mc = "刚刚有人撤回了: " + recalled_mc;
				bot.SendMessage(e.Group.GID, mc);*/
			}
			catch (const std::exception& ex)
			{
				cout << ex.what() << endl;
			}
		})
		.On<FriendMessage>(
		[&](FriendMessage fm)
		{
			/*
			string plain = fm.MessageChain.GetPlainText();
			string plain2 = string_To_UTF8("你好"); 
			if(plain == plain2)
			{
			cout<<plain2<<" = "<<plain<<endl;
			}
			cout<<plain<<endl;
			fm.Reply("hello, " + fm.MessageChain);*/
		});


	bot.EventLoop();

	return 0;
}