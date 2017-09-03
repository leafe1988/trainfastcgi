#include "stdafx.h"
#include "FastCgiAction.h"
#include "UIData.h"

#define addMsgProc(table,proc,url) {\
	table.insert(std::make_pair(url, proc)); \
}

CFastCgiAction::CFastCgiAction()
{
}


CFastCgiAction::~CFastCgiAction()
{
}





void CFastCgiAction::InitMsgProcMap()
{
	addMsgProc(mMsgProcTable, UiService::ForgetPasswd, "api/account/forget.json")
	addMsgProc(mMsgProcTable, UiService::LoginSystem, "api/account/login.json")
	addMsgProc(mMsgProcTable, UiService::ChangeVariable, "api/page/changeVariable.json")
	addMsgProc(mMsgProcTable, UiService::GetHomePageJson, "api/page/getHome.json")
	addMsgProc(mMsgProcTable, UiService::GetParamsJson, "api/page/getParams.json")
	addMsgProc(mMsgProcTable, UiService::GetVariableArrayJson, "api/page/getRealVariables.json")
	addMsgProc(mMsgProcTable, UiService::GetRoles, "api/page/getSetting.json")
	addMsgProc(mMsgProcTable, UiService::GetRoles, "api/page/getVersion.json")
	addMsgProc(mMsgProcTable, UiService::UpdateRoleRuleSettingJson, "api/page/updatePermission.json")
	addMsgProc(mMsgProcTable, UiService::UpdateupdateVehicleJson, "api/page/updateVehicle.json")
	addMsgProc(mMsgProcTable, UiService::GetMenus, "api/system/getMenus.json")
}

std::string CFastCgiAction::DisPatchFastCgiMsg(const std::string& strMsg, const std::string& strParameter)
{
	std::string sRet;
	auto it = mMsgProcTable.find(strMsg);
	_MSGPROC Proc;
	if (it != mMsgProcTable.end()){
		Proc = it->second;
		sRet = Proc(strParameter);
	}
	return sRet;
}