// testjsoncpp.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "json\json.h"
#include "string"
#include "signal.h"
#include "UIData.h"
#ifdef _DEBUG
#pragma comment(lib, "json_vc71_libmtd.lib")
#else
#pragma comment(lib, "json_vc71_libmt.lib")
#endif
using namespace std;
int test();

int _tmain(int argc, _TCHAR* argv[])
{
	test();
	Json::Value root;  // 表示整个 json 对象
	root["common"]["deviseNumber"] = Json::Value("2323233"); 
	root["common"]["softVersion"] = Json::Value("2323233");      
	root["common"]["deviceModel"] = Json::Value("2323233");
	root["common"]["configVersion"] = Json::Value("2323233");
	root["record"]["workStatus"] = Json::Value("2323233");
	root["record"]["systemTime"] = Json::Value("2323233");
	root["record"]["dayMileage"] = Json::Value("2323233");
	root["record"]["totalMileage"] = Json::Value("2323233");
	root["record"]["workDuration"] = Json::Value(22222);

	Json::ValueType type = root.type();                

	string strJson = root.toStyledString();
	if (!strJson.empty())
	{
		printf("json value is %s", strJson.c_str());
	}
	system("pause");
}



void testSignal(WebService::Signal* s)
{

	std::cout << "signal name : " << s->name() << std::endl;

	s->setValue(std::string("hello"));

	std::string val;
	s->getValue(&val);
	std::cout << "signal value : " << val << std::endl;

	return;
}

void testGroup(WebService::SignalGroup* group)
{
	std::cout << "signal name list: " << std::endl;
	auto nameList = group->signalNameList();
	for (auto& i : nameList){
		std::cout << '\t' << i << std::endl;
	}
	std::cout << "\r\n" << std::endl;

	auto s = group->signal("ProductName");
	if (s){
		testSignal(s);
	}

	return;
}

void testManager()
{
	auto sm = WebService::SignalManager::instance();

	auto nameList = sm->groupNameList();
	std::cout << "group name list: " << std::endl;
	for (auto& i : nameList){
		std::cout << '\t' << i << std::endl;
	}

	std::cout << "\r\n" << std::endl;

	WebService::SignalGroup*  group = sm->group("Product Infomation Group");
	if (group){
		testGroup(group);
	}

	return;
}
int test()
{
	//testManager();
	InitTestSignalData();
	std::string sssss;
	sssss = GetParamsJson(sssss);
	sssss = GetHomePageJson(sssss);
	//std::string VersionJson = GetVersionJson();
	//printf("GetVersionJson is %s\r\n", VersionJson.c_str());
	Json::Value jsonRoot;
	//jsonRoot["username"] = "leafe1222";
	//jsonRoot["password"] = "111111";
	//ForgetPasswd(jsonRoot.toStyledString());
	jsonRoot["id"] = "WheelDiameter3";
	jsonRoot["direction"] = 0;
	ChangeVariable(jsonRoot.toStyledString());
	std::string ss = InitMenusJson();
	InitRoleSetttingJson();
	Json::Value jsonRole;
	jsonRole["roleId"] = "2";
	jsonRole["menus"] = "1,2,3,4,5,6";
	UpdateRoleRuleSettingJson(jsonRole.toStyledString());
	ss = GetMenus(ss);
	return 0;
}
