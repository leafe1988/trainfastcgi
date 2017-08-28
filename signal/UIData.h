#pragma once
#include "signal.h"
class CUIData
{
public:
	CUIData();
	~CUIData();
};

WebService::Signal* GetSignal(const std::string& groupName, const std::string& signalname);

std::string GetSignalString(const std::string& groupName, const std::string& signalname);

std::tm GetSignalTime(const std::string& groupName, const std::string& signalname);

//获取版本信息 page/getVersion (api/page/getVersion.json)
std::string  GetVersionJson();
void InitTestSignalData();