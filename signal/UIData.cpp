#include "UIData.h"
#include "string"
#include "json\json.h"
#include <iostream>
#include <fstream>

namespace UiService{
	enum VariablesAct
	{
		Variablesdel = 0,
		Variablesadd
	};
	//1：忘记密码 URL：account/forget (api/account/forget.json)
	std::string ForgetPasswd(const std::string& strParameter)
	{
		std::string strJson;
		Json::Reader jsonReader;
		Json::Value jsonRoot;
		//check Parameter json formart
		if (!jsonReader.parse(strParameter, jsonRoot))
			return strJson;
		if (!jsonRoot.isMember("username") || !jsonRoot.isMember("password"))
			return strJson;

		std::ifstream fin;
		fin.open(FILE_LOCAL_USERINFO);
		Json::Reader reader;
		Json::Value  root;
		//如果文件不存在
		if (!fin)
			root["userinfo"].append(jsonRoot);
		else
		{
			if (!reader.parse(fin, root, false))
			{
				fin.close();
				return strJson;
			}
			const Json::Value arrayObj = root["userinfo"];
			for (unsigned int i = 0; i < arrayObj.size(); i++)
			{
				if (arrayObj[i]["username"].asString() == jsonRoot["username"].asString())
					root["userinfo"][i]["password"] = jsonRoot["password"].asString();
				else if (i == arrayObj.size() - 1)
					root["userinfo"].append(jsonRoot);
			}
		}
		fin.close();
		strJson = root.toStyledString();
		std::ofstream ofs;
		ofs.open(FILE_LOCAL_USERINFO);
		ofs << strJson;
		ofs.close();
		return strJson;
	}

	//2：登录 URL：account/login (api/account/login.json)
	std::string LoginSystem(const std::string& strParameter)
	{
		std::string strJson;
		Json::Reader jsonReader;
		Json::Value jsonRoot;
		bool bLoginSuccess = false;
		//check Parameter json formart
		if (!jsonReader.parse(strParameter, jsonRoot))
			return strJson;
		if (!jsonRoot.isMember("username") || !jsonRoot.isMember("password"))
			return strJson;

		std::ifstream fin;
		fin.open(FILE_LOCAL_USERINFO);
		Json::Reader reader;
		Json::Value  root;
		//如果文件不存在
		if (!fin)
		{
			root["userinfo"].append(jsonRoot);
			strJson = root.toStyledString();
			std::ofstream ofs;
			ofs.open(FILE_LOCAL_USERINFO);
			ofs << strJson;
			ofs.close();
		}
		else
		{
			if (!reader.parse(fin, root, false))
			{
				fin.close();
				return strJson;
			}
			const Json::Value arrayObj = root["userinfo"];
			for (unsigned int i = 0; i < arrayObj.size(); i++)
			{
				if (arrayObj[i]["username"].asString() == jsonRoot["username"].asString() &&
					root["userinfo"][i]["password"] == jsonRoot["password"].asString())
				{
					//登陆成功
					bLoginSuccess = true;
				}
			}
		}
		fin.close();
		return strJson;
	}

	//3:更改变量 URL：page/changeVariable (api/page/changeVariable.json)
	std::string ChangeVariable(const std::string& strParameter)
	{
		std::string strJson;
		Json::Reader jsonReader;
		Json::Value jsonRoot;
		//check Parameter json formart
		if (!jsonReader.parse(strParameter, jsonRoot))
			return strJson;
		if (!jsonRoot.isMember("name") || !jsonRoot.isMember("direction"))
			return strJson;

		std::ifstream fin;
		fin.open(FILE_LOCAL_VARIABLES);
		Json::Reader reader;
		Json::Value  root;
		//如果文件不存在
		if (!fin)
		{
			if (jsonRoot["direction"].asInt() == VariablesAct::Variablesadd)
			{
				Json::Value jsontmp;
				jsontmp["name"] = jsonRoot["name"].asString();
				root["Variable"].append(jsontmp);
			}
			else
				return strJson;
		}
		else
		{
			if (!reader.parse(fin, root, false))
			{
				fin.close();
				return strJson;
			}
			const Json::Value arrayObj = root["Variable"];
			for (unsigned int i = 0; i < arrayObj.size(); i++)
			{
				if (arrayObj[i]["name"].asString() == jsonRoot["name"].asString()){
					if (jsonRoot["direction"].asInt() == VariablesAct::Variablesdel){
						root["Variable"][i].removeMember("id");
						root["Variable"][i].removeMember("direction");
					}

				}
				else if (i == arrayObj.size() - 1)
				{
					if (jsonRoot["direction"].asInt() == VariablesAct::Variablesadd){
						Json::Value jsontmp;
						jsontmp["name"] = jsonRoot["name"].asString();
						root["Variable"].append(jsontmp);
					}
				}
			}
		}
		fin.close();
		strJson = root.toStyledString();
		std::ofstream ofs;
		ofs.open(FILE_LOCAL_VARIABLES);
		ofs << strJson;
		ofs.close();
		return strJson;

	}

	//7:获取首页数据 /api/page/getHome.json
	std::string GetHomePageJson(const std::string& strParameter)
	{
		Json::Value root;  // 表示整个 json 对象
		const char* tab[][3] = {
			{ "common", "deviseNumber", "SerialNumber" },
			{ "common", "softVersion", "AppSoftwareVersion" },
			{ "common", "deviceModel", "ProductType" }
		};

#define Product_setValue(root, i) {\
	root[i[0]][i[1]] = Json::Value(GetSignalString("Product Infomation Group", i[2])); \
		}

		for (auto& i : tab){
			Product_setValue(root, i);
		}

		const char* tabPruduct[][3] = {
			{ "common", "configVersion", "ConfigVersion" },
			{ "record", "workStatus", "BootloaderVersion" },
			{ "record", "systemTime", "CurrentSystemTime" },
			{ "record", "dayMileage", "CurrentMileage" },
			{ "record", "totalMileage", "TotalMileage" },
			{ "record", "workDuration", "TotalRunTime" },
		};

#define Pruduct_setValue(root, i) {\
	root[i[0]][i[1]] = Json::Value(GetSignalString("Pruduct State Group", i[2])); \
		}

		for (auto& i : tabPruduct){
			Pruduct_setValue(root, i);
		}
		std::string s = root.toStyledString();
		/*****************storage 存储器状态 *********************/
		//数据存储
		root["storage"]["type"] = Json::Value(22222);
		//总容量，含单位
		root["storage"]["totalCapacity"] = Json::Value(22222);
		//剩余容量，含单位 
		root["storage"]["limitCapacity"] = Json::Value(22222);
		//剩余百分比
		root["storage"]["percent"] = Json::Value(22222);
		//冻结容量，含单位
		root["storage"]["freezeCapacity"] = Json::Value(22222);
		//状态
		root["storage"]["status"] = Json::Value(22222);

		return root.toStyledString();
	}

	//10:获取参数页数据 page/getParams (api/page/getParams.json)
	std::string GetParamsJson(const std::string& strParameter)
	{
		Json::Value root;
		const char* tab[][2] = {
			{ "vehicleType", "VehicleType" },
			{ "vehicleNumber", "VehicleNumber" },
			{ "trainNumber", "TrainNumber" },
			{ "diameter1", "WheelDiameter1" },
			{ "diameter2", "WheelDiameter2" },
			{ "pulses1", "PulseEncode1" },
			{ "pulses2", "PulseEncode2" },
		};

#define Params_setValue(root, i) {\
	root[i[0]] = Json::Value(GetSignalString("Parameter Infomation Group", i[1])); \
		}
		for (auto& i : tab){
			Params_setValue(root, i);
		}
		return root.toStyledString();
	}

	//11:获取监控页的选择变量数据 pURL：page/getRealVariables (api/page/getRealVariables.json)
	std::string GetVariableArrayJson(const std::string& strParameter)
	{
		std::string strFilePath = FILE_LOCAL_VARIABLES;
		return GetFileJsonData(strFilePath);
	}

	//12:获取设置页面数据 page/getSetting (api/page/getSetting.json)
	std::string GetRoles(const std::string & strParameter)
	{
		std::string strFilePath = FILE_LOCAL_ROLES;
		return GetFileJsonData(strFilePath);
	}

	//14：获取版本信息  page/getVersion (api/page/getVersion.json)
	std::string  GetVersionJson(const std::string& strParameter)
	{
		Json::Value root;

		const char* tab[][3] = {
			{ "software", "systemVersion", "SystemSoftwareVersion" },
			{ "software", "appVersion", "AppSoftwareVersion" },
			{ "software", "firmwareVersion", "CommFirmwareVersion" },
			{ "software", "ioVersion", "IOBoardFirmwareVersion" },
			{ "software", "bootVersion", "BootloaderVersion" },
			{ "hardware", "boardVersion", "MainBoardHardwareVersion" },
			{ "hardware", "ioVersion", "IOBoardHardwareVersion" },
			{ "hardware", "commVersion", "CommBoardHardwareVersion" },
			{ "device", "productionDate", "ManufactureDataTime" },
		};

#define version_setValue(root, i) {\
	root[i[0]][i[1]] = Json::Value(GetSignalString("Product Infomation Group", i[2])); \
		}

		for (auto& i : tab){
			version_setValue(root, i);
		}

		std::ofstream ofs;
		ofs.open("d:\\test1.json");
		ofs << root.toStyledString();
		ofs.close();
		return root.toStyledString();
	}

	//16：设置权限 page/updatePermission (api/page/updatePermission.json)
	std::string  UpdateRoleRuleSettingJson(const std::string & strParameter)
	{
		std::string strJson;
		Json::Reader jsonReader;
		Json::Value jsonRoot;
		//check Parameter json formart
		if (!jsonReader.parse(strParameter, jsonRoot))
			return strJson;
		if (!jsonRoot.isMember("roleId") || !jsonRoot.isMember("menus"))
			return strJson;
#define SPL_FLAG ","
		std::string strRoleMenus = jsonRoot["menus"].asString();
		std::vector<std::string>vMenus = SpiltString(strRoleMenus, strRoleMenus.size(), SPL_FLAG);
		std::ifstream fin;
		fin.open(FILE_LOCAL_ROLES);
		Json::Reader reader;
		Json::Value  root;
		if (!fin)
		{
			strJson = InitRoleSetttingJson();
			reader.parse(strJson.c_str(), root);
		}
		else if (!reader.parse(fin, root, false))
		{
			fin.close();
			return strJson;
		}
		for (size_t i = 0; i < root.size(); i++)
		{
			if (root[i]["roleId"].asString() == jsonRoot["roleId"].asString())
			{
				const Json::Value arrayObj = root[i]["menus"];
				for (size_t j = 0; j < arrayObj.size(); j++)
				{
					//需要进行分割菜单的字符串 以逗号分割
					for (auto&menu : vMenus)
					{
						if (arrayObj[i]["menuId"].asString() == menu)
						{
							root[i]["menus"][j]["isChecked"] = "1";
							break;
						}
					}
				}
			}
		}
		strJson = root.toStyledString();
		std::ofstream ofs;
		ofs.open(FILE_LOCAL_ROLES);
		ofs << strJson;
		ofs.close();
		return strJson;
	}

	//17：更新车辆类型 page/updateVehicle (api/page/updateVehicle.json)
	std::string UpdateupdateVehicleJson(const std::string & strParameter)
	{
		std::string strJson;
		Json::Reader jsonReader;
		Json::Value jsonRoot;
		//check Parameter json formart
		if (!jsonReader.parse(strParameter, jsonRoot))
			return strJson;
		const char* tab[][2] = {
			{ "vehicleType", "VehicleType" },
			{ "vehicleNumber", "VehicleNumber" },
			{ "trainNumber", "TrainNumber" },
			{ "diameter1", "WheelDiameter1" },
			{ "diameter2", "WheelDiameter2" },
			{ "pulses1", "PulseEncode1" },
			{ "pulses2", "PulseEncode2" },
		};
		for (auto&i : tab)
		{
			if (jsonRoot.isMember(i[0]))
			{
				SetSignalString("Parameter Infomation Group", i[1], jsonRoot[i[0]].asString());
			}
		}
		return strJson;
	}

	//18：获取菜单 system/getMenus (api/system/getMenus.json)
	std::string GetMenus(const std::string & strParameter)
	{
		std::string strFilePath = FILE_LOCAL_MENUS;
		return GetFileJsonData(strFilePath);
	}

}


//获取维护页数据
std::string GetMaintainJson()
{
	Json::Value root;  // 表示整个 json 对象

	/*****************messageStat 消息总览*********************/
	//错误消息总数
	root["messageStat"]["totalErrorCount"] = Json::Value("2323233");
	//警告消息总数
	root["messageStat"]["totalWarnCount"] = Json::Value("2323233");
	//消息总数
	root["messageStat"]["totalCount"] = Json::Value("2323233");
	//最后清除消息操作时间
	root["messageStat"]["lastClearTime"] = Json::Value("2323233");

	/*****************deviceStatus 设备板卡工作状态*********************/
	//IO板卡
	root["deviceStatus"]["ioBoard"] = Json::Value("2323233");
	//通讯板卡
	root["deviceStatus"]["commBoard"] = Json::Value("2323233");


	return root.toStyledString();
}

//获取维护页的消息列表
std::string GetMessagesArrayJson()
{
	Json::Value root;  // 表示整个 json 对象
	/*****************deviceStatus 设备板卡工作状态*********************/
	Json::Value Message;
	//唯一标识符 
	Message["uniqueId"] = Json::Value("2323233");
	//错误等级
	Message["severity"] = Json::Value("2323233");
	//描述
	Message["description"] = Json::Value("2323233");
	//发生次数
	Message["count"] = Json::Value("2323233");
	//首次发生时间
	Message["firstTime"] = Json::Value("2323233");
	//最后发生时间
	Message["lastTime"] = Json::Value("2323233");
	root.append(Message);

	return root.toStyledString();
}

WebService::Signal* GetSignal(const std::string& groupName, const std::string& signalname)
{
	auto sm = WebService::SignalManager::instance();
	if (!sm)
		return NULL;
	WebService::SignalGroup*  group = sm->group(groupName);
	if (group){
		return group->signal(signalname);
	}
	return NULL;
}

std::string GetSignalString(const std::string& groupName, const std::string& signalname)
{
	std::string strSignal;
	WebService::Signal* pSignal = GetSignal(groupName, signalname);
	if (pSignal)
		pSignal->getValue(&strSignal);
	return strSignal;
}

bool SetSignalString(const std::string& groupName, const std::string& signalname, const std::string& strValue)
{
	WebService::Signal* pSignal = GetSignal(groupName, signalname);
	if (pSignal)
		pSignal->setValue(strValue);
	return true;
}

std::tm GetSignalTime(const std::string& groupName, const std::string& signalname)
{
	std::tm strSignal;
	WebService::Signal* pSignal = GetSignal(groupName, signalname);
	if (pSignal)
		pSignal->getValue(&strSignal);
	return strSignal;
}

//初始化信号测试数据
void InitTestSignalData()
{
	const char* tab[][3] = {
		{ "Product Infomation Group", "ProductName", "Test 001" },
		{ "Product Infomation Group", "ProductType", "XYZABC" },
		{ "Product Infomation Group", "VendorName", "上海道麒实业发展有限公司" },
		{ "Product Infomation Group", "SerialNumber", "SH0000000001" },
		{ "Product Infomation Group", "ManufactureDataTime", "2017/08/30 09:33:21" },
		{ "Product Infomation Group", "MainBoardHardwareVersion", "V 2.4.1" },
		{ "Product Infomation Group", "IOBoardHardwareVersion", "V 2.4.2" },
		{ "Product Infomation Group", "CommBoardHardwareVersion", "V 2.4.3" },
		{ "Product Infomation Group", "SystemSoftwareVersion", "V 2.4.4" },
		{ "Product Infomation Group", "AppSoftwareVersion", "V 2.4.5" },
		{ "Product Infomation Group", "CommFirmwareVersion", "V 2.4.6" },
		{ "Product Infomation Group", "IOBoardFirmwareVersion", "V 2.4.7" },
		{ "Product Infomation Group", "BootloaderVersion", "V 2.4.8" },
		{ "Parameter Infomation Group", "VehicleType", "东风21型" },
		{ "Parameter Infomation Group", "VehicleNumber", "DF2100000001" },
		{ "Parameter Infomation Group", "TrainNumber", "201502050001" },
		{ "Parameter Infomation Group", "WheelDiameter1", "2.21234" },
		{ "Parameter Infomation Group", "WheelDiameter2", "2.31245" },
		{ "Parameter Infomation Group", "PulseEncode1", "XYZ" },
		{ "Parameter Infomation Group", "PulseEncode2", "ABC" },
		{ "Pruduct State Group", "ConfigVersion", "V 2.4.9" },
		{ "Pruduct State Group", "TotalMileage", "12345678" },
		{ "Pruduct State Group", "CurrentMileage", "123456" },
		{ "Pruduct State Group", "TotalRunTime", "123" },
		{ "Pruduct State Group", "CurrentSystemTime", "2017/08/30 09:33:21" }
	};
		for(auto& i : tab){
			SetSignalString(i[0], i[1], i[2]);
		}
}


//初始化菜单
std::string InitMenusJson()
{
	Json::Value  root;
	Json::Value menu;
	const char* tab[][3] = {
		{"1","首页" ,"http://localhost/homepage"},
		{ "2", "参数页", "http://localhost/homepage" },
		{ "3", "监控", "http://localhost/homepage" },
		{ "4", "维护页", "http://localhost/homepage" },
		{ "5", "版本信息", "http://localhost/homepage" },
		{ "6", "数据下载", "http://localhost/homepage" }
	};
	for (auto& i : tab){
		menu["menuId"] = i[0];
		menu["menuName"] = i[1];
		menu["menuLink"] = i[2];
		root.append(menu);
	}
	std::string strJson = root.toStyledString();
	std::ofstream ofs;
	ofs.open(FILE_LOCAL_MENUS);
	ofs << strJson;
	ofs.close();

	return strJson;
}


//初始化角色
std::string InitRoleSetttingJson()
{
	std::string strJson;
	Json::Value  root;
	Json::Value menu;
	Json::Value role;
	const char* tab[][3] = {
		{ "1", "首页", "1" },
		{ "2", "参数页", "1" },
		{ "3", "监控", "1" },
		{ "4", "维护页", "1" },
		{ "5", "版本信息", "1" },
		{ "6", "数据下载", "1" }
	};
	role["roleId"] = "1";
	role["roleName"] = "测试";
	for (auto&i:tab)
	{
		Json::Value menus;
		menus["menuId"] = i[0];
		menus["menuName"] = i[1];
		menus["isChecked"] = i[2];
		role["menus"].append(menus);
	}
	root.append(role);
	const char* tabsys[][3] = {
		{ "1", "首页", "1" },
		{ "2", "参数页", "1" },
		{ "3", "监控", "0" },
		{ "4", "维护页", "0" },
		{ "5", "版本信息", "1" },
		{ "6", "数据下载", "1" }
	};
	role.clear();
	role["roleId"] = "2";
	role["roleName"] = "管理员";
	for (auto&i : tabsys)
	{
		Json::Value menus;
		menus["menuId"] = i[0];
		menus["menuName"] = i[1];
		menus["isChecked"] = i[2];
		role["menus"].append(menus);
	}
	root.append(role);
	strJson = root.toStyledString();
	std::ofstream ofs;
	ofs.open(FILE_LOCAL_ROLES);
	ofs << strJson;
	ofs.close();
	return strJson;
}


std::vector<std::string>SpiltString(std::string strSrc, int nLen, std::string strFlag)
{
	std::vector<std::string>rest;
	size_t iEnBegin = 0, iSize = 0;
	do
	{
		int iOffset = strSrc.find(strFlag, iSize);
		if (iOffset == std::string::npos)
		{
			if (iSize)
			{
				strSrc = strSrc.substr(iSize, strSrc.length() - iSize);
				rest.push_back(strSrc);
			}
			break;
		}
		std::string strSP = strSrc.substr(iSize, iOffset - iSize);
		iSize = iOffset;
		iSize += strFlag.length();
		rest.push_back(strSP);
	} while (iSize < strSrc.length());
	return rest;
}


//获取文件内容的json
std::string GetFileJsonData(const std::string& strFilePath)
{
	std::ifstream fin;
	std::string strJson;
	fin.open(strFilePath);
	Json::Reader reader;
	Json::Value  root;
	if (!fin)
	{
		return strJson;// strJson = InitRoleSetttingJson();
	}
	else
	{
		if (!reader.parse(fin, root, false))
		{
			fin.close();
			return strJson;
		}
		strJson = root.toStyledString();
	}

	return strJson;

}
