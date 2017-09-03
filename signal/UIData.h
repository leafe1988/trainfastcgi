#pragma once
#include "signal.h"
#include <vector>

//本地保存的用户名密码路径
#define FILE_LOCAL_USERINFO "d:\\userinfo.dat"

//本地保存的用户名密码路径
#define FILE_LOCAL_VARIABLES "d:\\Variables.dat"

//本地保存的角色设置数据
#define FILE_LOCAL_ROLES "d:\\roles.dat"

//本地保存的菜单路径
#define FILE_LOCAL_MENUS "d:\\menus.dat"
WebService::Signal* GetSignal(const std::string& groupName, const std::string& signalname);

std::string GetSignalString(const std::string& groupName, const std::string& signalname);

std::tm GetSignalTime(const std::string& groupName, const std::string& signalname);

bool SetSignalString(const std::string& groupName, const std::string& signalname, const std::string& strValue);

std::vector<std::string>SpiltString(std::string strSrc, int nLen, std::string strFlag);
//初始化信号数据
void InitTestSignalData();
//初始化菜单
std::string InitMenusJson();
//初始化菜单
std::string InitRoleSetttingJson();

//获取文件内容的json
std::string GetFileJsonData(const std::string& strFilePath);

namespace UiService{
	//1：忘记密码 URL：account/forget (api/account/forget.json)
	std::string ForgetPasswd(const std::string& strParameter);
	//2：登录 URL：account/login (api/account/login.json)
	std::string LoginSystem(const std::string& strParameter);
	//3:更改变量 URL：page/changeVariable (api/page/changeVariable.json)
	std::string ChangeVariable(const std::string& strParameter);
	//7:获取首页数据 /api/page/getHome.json
	std::string GetHomePageJson(const std::string& strParameter);
	//10:获取参数页数据 page/getParams (api/page/getParams.json)
	std::string GetParamsJson(const std::string& strParameter);
	//11:获取监控页的选择变量数据 pURL：page/getRealVariables (api/page/getRealVariables.json)
	std::string GetVariableArrayJson(const std::string& strParameter);
	//12:获取设置页面数据 page/getSetting (api/page/getSetting.json)
	std::string GetRoles(const std::string & strParameter);
	//14：获取版本信息  page/getVersion (api/page/getVersion.json)
	std::string  GetVersionJson(const std::string& strParameter);
	//16：设置权限 page/updatePermission (api/page/updatePermission.json)
	std::string UpdateRoleRuleSettingJson(const std::string & strParameter);
	//17：更新车辆类型 page/updateVehicle (api/page/updateVehicle.json)
	std::string UpdateupdateVehicleJson(const std::string & strParameter);
	//18：获取菜单 system/getMenus (api/system/getMenus.json)
	std::string GetMenus(const std::string & strParameter);
}
;