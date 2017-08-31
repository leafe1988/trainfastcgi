#pragma once
#include "signal.h"
class CUIData
{
public:
	CUIData();
	~CUIData();
};


//本地保存的用户名密码路径
#define FILE_LOCAL_VARIABLES "d:\\Variables.dat"

WebService::Signal* GetSignal(const std::string& groupName, const std::string& signalname);

std::string GetSignalString(const std::string& groupName, const std::string& signalname);

std::tm GetSignalTime(const std::string& groupName, const std::string& signalname);

//获取版本信息 page/getVersion (api/page/getVersion.json)
std::string  GetVersionJson();
void InitTestSignalData();

std::string ForgetPasswd(std::string& strParameter);

std::string ChangeVariable(std::string& strParameter);

std::string InitMenusJson();

std::string GetMenus(std::string & strParameter);

//初始化菜单
std::string InitRoleSetttingJson();

std::string UpdateRoleRuleSettingJson(std::string & strParameter);

//获取文件内容的json
std::string GetFileJsonData(std::string& strFilePath);

std::string GetParamsJson(std::string& strParameter);

std::string GetHomePageJson(std::string& strParameter);


