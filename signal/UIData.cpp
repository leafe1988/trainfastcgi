#include "UIData.h"
#include "string"
#include "json\json.h"

#include <iostream>
#include <fstream>
CUIData::CUIData()
{
}


CUIData::~CUIData()
{
}


std::string GetHomePageJson()
{
	Json::Value root;  // 表示整个 json 对象

	/*****************common 通用信息 *********************/
	//设备序列号 
	root["common"]["deviseNumber"] = Json::Value("2323233");
	//软件版本号 
	root["common"]["softVersion"] = Json::Value("2323233");
	//设备型号
	root["common"]["deviceModel"] = Json::Value("2323233");
	//配置版本号
	root["common"]["configVersion"] = Json::Value("2323233");

	/*****************record 记录器状态 *********************/
	//工作状态
	root["record"]["workStatus"] = Json::Value("2323233");
	//系统时间
	root["record"]["systemTime"] = Json::Value("2323233");
	//单日总里程
	root["record"]["dayMileage"] = Json::Value("2323233");
	//总里程
	root["record"]["totalMileage"] = Json::Value("2323233");
	//工作时间
	root["record"]["workDuration"] = Json::Value(22222);

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

//获取参数页数据
std::string GetParamsJson()
{
	Json::Value root;  // 表示整个 json 对象
	//车辆类型
	root["vehicleType"] = Json::Value("2323233");
	//车辆编号
	root["vehicleNumber"] = Json::Value("2323233");
	//车次
	root["trainNumber"] = Json::Value("2323233");
	//轮径1，单位mm 
	root["diameter1"] = Json::Value("2323233");
	//轮径2，单位mm 
	root["diameter2"] = Json::Value("2323233");
	//脉冲数1
	root["pulses1"] = Json::Value("2323233");
	//脉冲数2
	root["pulses2"] = Json::Value("2323233");

	return root.toStyledString();
}

//获取实时变量数据 page/getRealVariables (api/page/getRealVariables.json)
std::string GetRealVariableArrayJson()
{
	Json::Value root;  // 表示整个 json 对象
	Json::Value Variable;
	//变量ID  
	Variable["id"] = Json::Value("2323233");
	//变量名称
	Variable["name"] = Json::Value("2323233");
	root.append(Variable);

	return root.toStyledString();
}

//获取设置页面数据 page/getSetting (api/page/getSetting.json)
std::string GetSettingJson()
{
	Json::Value root;  // 表示整个 json 对象
	//菜单的数组
	Json::Value MenusArray;

	//角色ID 
	root["roleId"] = Json::Value("2323233");
	//角色名称  
	root["roleName"] = Json::Value("2323233");

	//菜单ID
	MenusArray["menuId"] = Json::Value("2323233");
	MenusArray["menuName"] = Json::Value("2323233");
	MenusArray["isChecked"] = Json::Value("2323233");


	root["roleName"] = MenusArray;

	return root.toStyledString();
}

//获取监控页的选择变量数据 page/getVariables (api/page/getVariables.json)
std::string GetVariableArrayJson()
{
	//选择变量的数组
	Json::Value VariableArray;

	//变量ID 
	VariableArray["id"] = Json::Value("2323233");
	//变量名称
	VariableArray["name"] = Json::Value("2323233");


	return VariableArray.toStyledString();
}


#define ProductGroupSignalValue(name) {\
	Json::Value(GetSignalString("Product Infomation Group", name)) \
}

//获取版本信息 page/getVersion (api/page/getVersion.json)
std::string  GetVersionJson()
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

//获取菜单 system/getMenus (api/system/getMenus.json)
std::string GetMenus()
{
	Json::Value root;  // 表示整个 json 对象
	Json::Value MenusArray;  // 表示整个 json 对象
	//菜单ID
	MenusArray["menuId"] = Json::Value("2323233");
	//菜单名称
	MenusArray["menuName"] = Json::Value("2323233");
	//菜单地址
	MenusArray["menuLink"] = Json::Value("2323233");
	root.append(MenusArray);


	return MenusArray.toStyledString();
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

/*
---------------------------------------------------------------
信号名称                    |  信号名称解释
---------------------------------------------------------------
Product Infomation Group
---------------------------------------------------------------
ProductName                 |  设备名称
ProductType                 |  设备型号
VendorName                  |  设备产商
SerialNumber                |  设备序列号
ManufactureDataTime         |  生产日期
MainBoardHardwareVersion    |  主板硬件版本号
IOBoardHardwareVersion      |  IO板硬件版本号
CommBoardHardwareVersion    |  通讯板硬件版本号
SystemSoftwareVersion       |  系统版本号
AppSoftwareVersion          |  应用软件版本号
CommFirmwareVersion         |  通讯固件版本号
IOBoardFirmwareVersion      |  IO板固件版本号
BootloaderVersion           |  Bootloader版本号

---------------------------------------------------------------
Parameter Infomation Group
---------------------------------------------------------------
VehicleType                 |  车辆类型
VehicleNumber               |  车辆编号
TrainNumber                 |  车次
WheelDiameter1              |  轮径1
WheelDiameter2              |  轮径2
PulseEncode1                |  脉冲编码1
PulseEncode2                |  脉冲编号2

---------------------------------------------------------------
Pruduct State Group
---------------------------------------------------------------
ConfigVersion               |  配置版本号
TotalMileage                |  总里程
CurrentMileage              |  当前运行里程
TotalRunTime                |  总工作时间
CurrentSystemTime           |  当前系统时间
---------------------------------------------------------------
*/
//初始化信号测试数据
void InitTestSignalData()
{
	const char* tab[][3] = {
		{ "Product Infomation Group", "ProductName", "火车记录仪" },
		{ "Product Infomation Group", "ProductType", "testtype" },
		{ "Product Infomation Group", "VendorName", "道" },
		{ "Product Infomation Group", "SerialNumber", "2222939392-3" },
		{ "Product Infomation Group", "ManufactureDataTime", "2018-08-08" },
		{ "Product Infomation Group", "MainBoardHardwareVersion", "1.0.0.1" },
		{ "Product Infomation Group", "IOBoardHardwareVersion", "1.0.0.2" },
		{ "Product Infomation Group", "CommBoardHardwareVersion", "1.0.0.3" },
		{ "Product Infomation Group", "SystemSoftwareVersion", "1.0.0.4" },
		{ "Product Infomation Group", "AppSoftwareVersion", "1.0.0.5" },
		{ "Product Infomation Group", "CommFirmwareVersion", "1.0.0.6" },
		{ "Product Infomation Group", "IOBoardFirmwareVersion", "1.0.0.7" },
		{ "Product Infomation Group", "BootloaderVersion", "1.0.0.8" },
		{ "Parameter Infomation Group", "VehicleType", "0013" },
		{ "Parameter Infomation Group", "VehicleNumber", "1101" },
		{ "Parameter Infomation Group", "TrainNumber", "K52" },
		{ "Parameter Infomation Group", "WheelDiameter1", "1.5" },
		{ "Parameter Infomation Group", "WheelDiameter2", "1.8" },
		{ "Parameter Infomation Group", "PulseEncode1", "100008" },
		{ "Parameter Infomation Group", "PulseEncode2", "100009" },
		{ "Pruduct State Group", "ConfigVersion", "1.1.1.5" },
		{ "Pruduct State Group", "TotalMileage", "1.5" },
		{ "Pruduct State Group", "CurrentMileage", "5478" },
		{ "Pruduct State Group", "TotalRunTime", "8988" },
		{ "Pruduct State Group", "CurrentSystemTime", "2017-08-28 12:00:00" }
	};
		for(auto& i : tab){
			SetSignalString(i[0], i[1], i[2]);
		}
}